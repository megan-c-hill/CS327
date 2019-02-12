#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "heap.h"

struct heap_node {
	heap_node_t *next;
	heap_node_t *prev;
	heap_node_t *parent;
	heap_node_t *child;
	void *data; //I don't care it's grammatically incorrect
	uint32_t degree;
	uint32_t mark;
};

void swap(heap_node_t *a, heap_node_t *b){
	heap_node_t *temp = a;
	a = b;
	b = temp;
}

void splice_heap(heap_node_t *n1, heap_node_t *n2) {
	if (n1 && n2) {
		n1->next->prev = n2->prev; //Don't really get this line
		n2->prev->next = n1->next; //or this line
		n1->next = n2;
		n2->prev = n1;
	}
}

void insert_node_in_heap(heap_node_t *new, heap_node_t *old) {
	new->next = old;
	new->prev = old->prev;
	new->prev->next = new;
	old->prev = new;
}

void remove_node(heap_node_t *node){
	node -> next -> prev = node -> prev;
	node -> prev -> next = node -> next;
}

void heap_init(heap_t *h, int32_t (*compare)(const void *key, const void *with)) {
	h->min = NULL;
	h->size = 0;
	h->compare = compare;
}

void delete_heap_node(heap_t *h, heap_node_t *hn) {
	heap_node_t *next;
	hn->prev->next = NULL;
	while (hn) {
		if (hn->child) {
			delete_heap_node(h, hn->child);
		}
		next = hn->next;
		hn->data = NULL;
		free(hn);
		hn = next;
	}
}

void heap_delete(heap_t *h) {
	if (h->min) {
		delete_heap_node(h, h->min);
	}

	h->min = NULL;
	h->size = 0;
	h->compare = NULL;
}

heap_node_t *insert_value(heap_t *h, void *value) {
	heap_node_t *n;
	n = calloc(1, sizeof(*n));
	n->data = value;

	if (h->min) {
		insert_node_in_heap(n, h->min);
	} else {
		n->next = n->prev = n;
	}

	if (!h->min || h->compare(value, h->min->data) < 0) {
		h->min = n;
	}

	h->size++;

	return n;
}
//
void *heap_peek(heap_t *h) {
	return h->min ? h->min->data : NULL;
}

void link_heap(heap_t *h, heap_node_t *node, heap_node_t *root){
	if(root -> child){
		insert_node_in_heap(node, root ->child);
	} else {
		root ->child = node;
		node -> next = node -> prev = node;
	}

	node -> parent = root;
	node -> degree ++;
	node -> mark = 0;
}
//
static void heap_consolidate(heap_t *h) //not modified
{
    uint32_t i;
    heap_node_t *x, *y, *n;
    heap_node_t *a[64]; /* Need ceil(lg(h->size)), so this is good  *
                       * to the limit of a 64-bit address space,  *
                       * and much faster than any lg calculation. */

    memset(a, 0, sizeof (a));

    h->min->prev->next = NULL;

    for (x = n = h->min; n; x = n) {
        n = n->next;

        while (a[x->degree]) {
            y = a[x->degree];
            if (h->compare(x->data, y->data) > 0) {
                swap(x, y);
            }
            a[x->degree] = NULL;
            link_heap(h, y, x);
        }
        a[x->degree] = x;
    }

    for (h->min = NULL, i = 0; i < 64; i++) {
        if (a[i]) {
            if (h->min) {
                insert_node_in_heap(a[i], h->min);
                if (h->compare(a[i]->data, h->min->data) < 0) {
                    h->min = a[i];
                }
            } else {
                h->min = a[i];
                a[i]->next = a[i]->prev = a[i];
            }
        }
    }
}

void *heap_remove(heap_t *h) {
	void *value;
	heap_node_t *node;
	value = NULL;

	if (h->min) {
		value = h->min->data;
		if (h->size == 1) {
			free(h->min);
			h->min = NULL;
		} else {
			if (h->min->child) {
				for (node = h->min->child; node->parent; node = node->next) {
					node->parent = NULL;
				}
			}
			splice_heap(h->min, h->min->child);

			node = h->min;
			remove_node(node);
			h->min = node->next;
			free(node);

            heap_consolidate(h);

		}
		h->size--;
	}
	return value;
}

int heap_combine(heap_t *h, heap_t *h1, heap_t *h2) //barely modified
{
    if (h1->compare != h2->compare) {
        return 1;
    }

    h->compare = h1->compare;

    if (!h1->min) {
        h->min = h2->min;
        h->size = h2->size;
    } else if (!h2->min) {
        h->min = h1->min;
        h->size = h1->size;
    } else {
        h->min = ((h->compare(h1->min->data, h2->min->data) < 0) ?
                  h1->min                                          :
                  h2->min);
        splice_heap(h1->min, h2->min);
    }

    memset(h1, 0, sizeof (*h1));
    memset(h2, 0, sizeof (*h2));

    return 0;
}

static void heap_cut(heap_t *h, heap_node_t *n, heap_node_t *p)
{
    if (!--p->degree) {
        p->child = NULL;
    }
    if (p->child == n) {
        p->child = p->child->next;
    }
    remove_node(n);
    n->parent = NULL;
    n->mark = 0;
    insert_node_in_heap(n, h->min);
}

static void heap_cascading_cut(heap_t *h, heap_node_t *n)
{
    heap_node_t *p;

    if ((p = n->parent)) {
        if (!n->mark) {
            n->mark = 1;
        } else {
            heap_cut(h, n, p);
            heap_cascading_cut(h, n);
        }
    }
}

int heap_decrease_key(heap_t *h, heap_node_t *n, void *v)
{
    if (h->compare(n->data, v) <= 0) {
        return 1;
    }

    n->data = v;

    return heap_decrease_key_no_replace(h, n);
}

int heap_decrease_key_no_replace(heap_t *h, heap_node_t *n)
{
    /* No tests that the value hasn't actually increased.  Change *
     * occurs in place, so the check is not possible here.  The   *
     * user is completely responsible for ensuring that they      *
     * don't fubar the queue.                                     */

    heap_node_t *p;

    p = n->parent;

    if (p && (h->compare(n->data, p->data) < 0)) {
        heap_cut(h, n, p);
        heap_cascading_cut(h, p);
    }
    if (h->compare(n->data, h->min->data) < 0) {
        h->min = n;
    }

    return 0;
}
