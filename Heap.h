#ifndef HEAP_H_
#define HEAP_H_

#include "Error.h"
#include "Utils.h"

/*
 *	Header for heap data structure
 *	
 *	Observations:
 *		-->	most of the functions return an error code (ERRCD) defined in Error.h
 *		--> if the error code is different from SUCCES a problem occured and
 *				the returned value cannot be used
 *		--> on any function that has a return parameter, if the NULL value is passed
 *				than the value is considered to be ignored
 */

/*
 *	Data type structure for the heap
 *	Contains all the informations needed managing for the heap
 */
typedef struct _HEAP{
	size_t capacity;
	size_t size;
	int* elements;
}HEAP;

/*
 *	Constructs a heap
 *	Returns:
 *		NULL	-	if the heap could not be created
 *		heap	-	the newly created empty heap otherwise
 */
HEAP* constrHeap();

/*
 *	Copies a heap
 *	Params:
 *		heap	-	the heap to be copied
 *	Returns:
 *		NULL	-	if the heap could not be copied
 *		hp		-	the copied heap otherwise
 */
HEAP* copyHeap(
	const HEAP* heap
);

/*
 *	Gets the size of the heap
 *	Params:
 *		heap	-	the heap
 *	Returns:
 *		size	-	the size of the heap
 */
size_t sizeHeap(
	const HEAP* heap
);

/*
 *	Gets the capacity of the heap
 *	Params:
 *		heap	-	the heap
 *	Returns:
 *		cap		-	the capacity of the heap
 */
size_t capHeap(
	const HEAP* heap
);

/*
 *	Pushes an element on the heap
 *	Params:
 *		heap	-	the heap
 *		elem	-	the element
 *	Returns:
 *		SUCCESS, NDTERR, ALLOCERR
 */
ERRCD pushHeap(
	HEAP* heap,
	int elem
);

/*
 *	Pops the smallest element of the heap
 *	Params:
 *		heap	-	the heap
 *		elem	-	the element OUTPUT
 *	Returns:
 *		SUCCESS, INVRET, NDTERR, EMPTYCOL
 */
ERRCD popHeap(
	HEAP* heap,
	int* elem
);

/*
 *	Peek at the smallest element of the heap without poping it
 *	Params:
 *		heap	-	the heap
 *		elem	-	the element OUTPUT
 *	Returns:
 *		SUCCESS, INVRET, NDTERR, EMPTYCOL
 */
ERRCD peekHeap(
	const HEAP* heap,
	int* elem
);


/*
 *	Destroys a heap
 *	Params:
 *		heap	-	the heap
 *	Returns:
 *		SUCCESS, NDTERR
 */
ERRCD destrHeap(
	HEAP** heap
);

#endif // !HEAP_H_

