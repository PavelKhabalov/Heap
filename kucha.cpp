#include <stdio.h>
#include <stdlib.h>

#define Data heap->data
#define Size heap->size
#define Cap  heap->cap
#define Comp heap->compare

#define Left(pos)  (2*pos + 1)
#define Right(pos) (2*pos + 2)
//1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111

typedef int elem_t;

typedef struct {
	elem_t *data;
	int size;
	int cap;
	int (*compare) (elem_t, elem_t);
} heap_t;




int comp_int(int a, int b);

heap_t *new_heap(int capacity, int (*compare) (elem_t, elem_t) = comp_int, elem_t *array = NULL, int size = 0); // compare - функция возвращающая число > 0 если первый элемент больше второго, < 0 если меньше, 0 если оба равны

heap_t *change_cap(heap_t *heap, int new_cap);

int set_comp(heap_t *heap, int (*compare) (elem_t, elem_t));

int heap_push(heap_t *heap, elem_t elem);

int sift_up(heap_t *heap, int pos);

int sift_down(heap_t *heap, int pos);

elem_t get_root(heap_t *heap);

heap_t *arr_to_heap(heap_t *heap, elem_t *arr, int size);

int comp(elem_t a, elem_t b) {
	return b - a;
}



int main() {
    int arr[7] = {10, 4, 7, 8, 2, 1, 3};
	heap_t *heap = new_heap(7, comp, arr, 7);



	for (int i = 0; i < Size; i++) {
		printf("%d\n", Data[i]);
	}

	printf("root: %d\n", get_root(heap));

	for (int i = 0; i < Size; i++) {
		printf("%d\n", Data[i]);
	}

	return 0;
}








heap_t *new_heap(int capacity, int (*compare) (elem_t, elem_t), elem_t *array, int size) {
	heap_t *heap = (heap_t*) calloc (1, sizeof(heap_t));
	Data = (elem_t*) calloc (capacity, sizeof(elem_t));
	Size = 0;
	Cap = capacity;
	Comp = compare;

	if (array) {
		arr_to_heap(heap, array, size);
	}

	return heap;
}

int clear_heap(heap_t *heap) {
	free(Data);
	Data = NULL;
	Size = 0;
	Cap = 0;

	return 0;
}

int delete_heap(heap_t *heap) {
	clear_heap(heap);
	free(heap);

	return 0;
}

heap_t *change_cap(heap_t *heap, int new_cap) {
	Data = (elem_t*) realloc(Data, new_cap);
	Cap = new_cap;
	if (Size < new_cap) {
		Size = new_cap;
	}

	return heap;
}

int heap_push(heap_t *heap, elem_t elem) {
	if (Size == Cap) {
		change_cap(heap, (Cap + 1) * 2);
	}

	Data[Size] = elem;

	sift_up(heap, Size);
	Size++;

	if (Size == Cap) {
		change_cap(heap, Cap * 2);
	}

	return 0;
}

int sift_up(heap_t *heap, int pos) {
	if (Comp(Data[pos],  Data[pos / 2]) > 0) {
		elem_t temp = Data[pos];
		Data[pos] = Data[pos / 2];
		Data[pos / 2] = temp;

		return sift_up(heap, pos / 2);
	}

	return 0;
}

int sift_down(heap_t *heap, int pos) {
	int largest = pos;

	if (Left(pos) < Size && (Comp(Data[Left(pos)],  Data[largest]) > 0)) {
		largest = Left(pos);
	}

	if (Right(pos) < Size && (Comp(Data[Right(pos)],  Data[largest]) > 0)) {
		largest = Right(pos);
	}

	if (largest == pos) {
		return 0;
	}

	elem_t temp = Data[largest];
	Data[largest] = Data[pos];
	Data[pos] = temp;

	sift_down(heap, largest);
}

heap_t *arr_to_heap(heap_t *heap, elem_t *arr, int size) {
	if (Cap < size) {
		change_cap(heap, size + 1);
	}
	Size = size;

	for (int i = 0; i < size; i++) {
		Data[i] = arr[i];
	}

	for (int i = size / 2; i >= 0; i--) {
		sift_down(heap, i);
	}

	return heap;
}

int set_comp(heap_t *heap, int (*compare) (elem_t, elem_t)) {
	Comp = compare;

	return 0;
}

elem_t get_root(heap_t *heap) {
	elem_t root = Data[0];
	Data[0] = Data[--Size];

	sift_down(heap, 0);

	return root;
}




int comp_int(int a, int b) {
	return a - b;
}
