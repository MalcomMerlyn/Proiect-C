#include "Heap.h"

#include <stdlib.h>

#define FAILRSZ 0		// failed resize
#define INITCAP 2		// initial heap capacity

// Resizes the heap
inline static size_t resize(
	HEAP* heap
)
{
	size_t cap = (heap->capacity * 3) / 2;
	int* elem = (int*)malloc(cap * sizeof(int));
	if (elem == NULL)
		return FAILRSZ;
	memcopy(elem, heap->elements, heap->size * sizeof(int));
	free(heap->elements);
	heap->elements = elem;
	heap->capacity = cap;
	return cap;
}

HEAP* constrHeap()
{
	HEAP* heap = (HEAP*)malloc(sizeof(HEAP));
	if (heap == NULL)
		return NULL;
	heap->capacity = INITCAP;
	heap->size = 0;
	heap->elements = (int*)malloc(INITCAP * sizeof(int));
	if (heap->elements == NULL)
	{
		free(heap);
		return NULL;
	}
	return heap;
}

HEAP* copyHeap(
	const HEAP* heap
)
{
	if (heap == NULL)
		return NULL;
	HEAP* hp = (HEAP*)malloc(sizeof(HEAP));
	if (hp == NULL)
		return NULL;
	hp->elements = (int*)malloc(heap->capacity * sizeof(int));
	if (hp->elements == NULL)
	{
		free(hp);
		return NULL;
	}
	memcopy(hp->elements, heap->elements, heap->size * sizeof(int));
	hp->capacity = heap->capacity;
	hp->size = heap->size;
	return hp;
}

size_t sizeHeap(
	const HEAP* heap
)
{
	if (heap == NULL)
		return 0;
	return heap->size;
}

size_t capHeap(
	const HEAP* heap
)
{
	if (heap == NULL)
		return 0;
	return heap->capacity;
}

ERRCD pushHeap(
	HEAP* heap,
	int elem
)
{
	if (heap == NULL)
		return NDTERR;
	if (heap->size == heap->capacity &&
		resize(heap) == FAILRSZ
		)
		return ALLOCERR;
	heap->elements[heap->size++] = elem;
	size_t pos = heap->size - 1;
	while (pos != 0 &&
		heap->elements[(pos - 1) / 2] > heap->elements[pos]			// current element is smaller than it's parent 
	)
	{
		swap(heap->elements + (pos - 1) / 2, heap->elements + pos);
		pos = (pos - 1) / 2;
	}
	return SUCCESS;
}

ERRCD popHeap(
	HEAP* heap,
	int* elem
)
{
	if (heap == NULL)
		return NDTERR;
	if (heap->size == 0)
		return EMPTYCOL;
	int* min;
	size_t pos = 0;
	heap->size--;
	if (elem != NULL)
		*elem = *heap->elements;
	swap(heap->elements, heap->elements + heap->size);
	while (
		2 * pos + 1 < heap->size &&
		heap->elements[pos] >									// current is bigger than
		*(min = minim(											// minimum of it's children
			heap->elements + 2 * pos + 1,			
			heap->elements + 2 * pos + 2,
			heap->elements + heap->size - 1
			)
		)
	)
	{
		swap(heap->elements + pos, min);
		pos = min - heap->elements;
	}
	if (elem == NULL)
		return INVRETV;
	return SUCCESS;
}

ERRCD peekHeap(
	const HEAP* heap,
	int* elem
)
{
	if (heap == NULL)
		return NDTERR;
	if (heap->size == 0)
		return EMPTYCOL;
	if (elem == NULL)
		return INVRETV;
	*elem = *heap->elements;
	return SUCCESS;
}

ERRCD destrHeap(
	HEAP** heap
)
{
	if (*heap == NULL)
		return NDTERR;
	if ((*heap)->elements != NULL)
		free((*heap)->elements);
	free(*heap);
	*heap = NULL;
	return SUCCESS;
}
