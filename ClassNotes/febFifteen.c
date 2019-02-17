#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

void generic_insertion_sort(void *data, int n, size_t s, int (*compare)(const void *, const void *)){
	int i, j;
	void *t;
	char *a; //used by char is only one byte

	a = data; // a can be dereferenced data cant
	t = malloc(s);


	for(i = 1; i<n; i++){
		for(memcpy(t, a + (i*s), s), j = i-1; j> -1 && compare(a + (j*s), t) > 0; j--){
			memcpy(a + ((j+1)*s), a + (j*s), s);
		}
		memcpy(a + (j*s), t, s);
	}

	free(t);
}

void insertion_sort(int *a, int n) {
	int i, j, t;
	for(i = 1; i<n; i++){
		for(t = a[i], j = i-1; j> -1 && a[j]>t; j--){
			a[j+1] = a[j];
		}
		a[j + 1] = t;
	}
}

int compare_ints(const void *v1, const void *v2){
	return *((const int *)v1) - *((const int *)v2);
}

int main(int argc, char *argv[]){
	int a[10] = {10, 9 , 8 , 7, 6, 5, 4, 3, 2, 1};
	int i;

//	insertion_sort(a, sizeof(a) / sizeof(a[0]));
	generic_insertion_sort(a, sizeof(a)/ sizeof(a[0]), sizeof(a[0]), compare_ints);
	for(i = 0; i<10; i++){
		printf("%d\n", a[i]);
	}
}
