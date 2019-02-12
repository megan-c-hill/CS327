#ifndef CS327_HEAP_H
#define CS327_HEAP_H

#include <stdint.h>

struct heap_node;
typedef struct heap_node heap_node_t;

typedef struct heap {
    heap_node_t *min;
    uint32_t size;
    int32_t (*compare)(const void *key, const void *with);
} heap_t;

void heap_init(heap_t *h, int32_t (*compare)(const void *key, const void *with)); //done
void heap_delete(heap_t *h); //done
heap_node_t *insert_value(heap_t *h, void *value); //done
void *heap_peek(heap_t *h); //done
void *heap_remove_min(heap_t *h); //done
int heap_combine(heap_t *h, heap_t *h1, heap_t *h2);
int heap_decrease_key(heap_t *h, heap_node_t *n, void *v);
int heap_decrease_key_no_replace(heap_t *h, heap_node_t *n);

#endif
