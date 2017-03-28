#ifndef LIST_H_
#define LIST_H_

#include "Error.h"
#include "Utils.h"

/*
 *	Header for list data structure
 *
 *	Observations:
 * 		-->	most of the functions return an error code (ERRCD) defined in Error.h
 * 		--> if the error code is different from SUCCES a problem occured and
 *				the returned value cannot be used
 *		--> on any function that has a return parameter, if the NULL value is passed
 *				than the value is considered to be ignored
 */

 /*
 *	Data type structure for a node of the list
 *	Contains the information (info) and pointer to the previous and next NODE
 */
typedef struct _NODE {
	struct _NODE* prev;
	struct _NODE* next;
	int info;
}NODE;

/*
*	Data type structure for the dummy node of the list
*	Contains only pointers to the previous and next node
*/
typedef struct _DNODE {
	struct _NODE* prev;
	struct _NODE* next;
	size_t size;
}DNODE;

/*
 *	Data type structure for the list
 *	Contains the pointer to the dummy node
 */
typedef struct _LIST {
	struct _NODE* dummy;
}LIST;

/*
 *	Data structure for iterating the list
 */
typedef struct _ITER {
	LIST* list;
	struct _NODE* current;
}ITER;

/*
 *	Constructs a list
 * 	Returns:
 *		NULL	-	if the list could not be created
 *		list	-	the newly created empty list otherwise
 */
LIST* constrList();

/*
 *	Copies a list
 *	Params:
 *		list	-	the list to be copied
 *	Returns:
 *		NULL	-	if the list could not be copied
 *		lst		-	the copied list otherwise
 */
LIST* copyList(
	const LIST* list
);

/*
 *	Gets the size of the list
 *	Params:
 *		list	-	the list
 *	Returns:
 *		size	-	the size of the list
 */
size_t sizeList(
	const LIST* list
);

/*
 *	Adds an element at the begining of the list
 *	Params:
 *		list	-	the list
 *		elem	-	the element
 *	Returns:
 *		SUCCESS, NDTERR, ALLOCERR
 */
ERRCD addFirstList(
	LIST* list,
	int elem
);

/*
 *	Adds an element at the end of the list
 *	Params:
 *		list	-	the list
 *		elem	-	the element
 *	Returns:
 *		SUCCESS, NDTERR, ALLOCERR
 */
ERRCD addLastList(
	LIST* list,
	int elem
);

/*
 *	Removes the element at the begining of the list
 *	Params:
 *		list	-	the list
 *		elem	-	the element OUTPUT
 *	Returns:
 *		SUCCESS, INVRET, NDTERR, EMPTYCOL
 */
ERRCD pollFirstList(
	LIST* list,
	int* elem
);

/*
 *	Removes the element at the end of the list
 *	Params:
 *		list	-	the list
 *		elem	-	the element OUTPUT
 *	Returns:
 *		SUCCESS, INVRET, NDTERR, EMPTYCOL
 */
ERRCD pollLastList(
	LIST* list,
	int* elem
);

/*
 *	Gets the element at the begining of the list
 *	Params:
 *		list	-	the list
 *		elem	-	the element OUTPUT
 *	Returns:
 *		SUCCESS, INVRET, NDTERR, EMPTYCOL
 */
ERRCD getFirstList(
	LIST* list,
	int* elem
);

/*
 *	Gets the element at the end of the list
 *	Params:
 *		list	-	the list
 *		elem	-	the element OUTPUT
 *	Returns:
 *		SUCCESS, INVRET, NDTERR, EMPTYCOL
 */
ERRCD getLastList(
	LIST* list,
	int* elem
);

/*
 *	Merges the elements of two sorted lists in a new list
 *	Params:
 *		llist	-	the first list
 *		rlist	-	the second list
 *		list	-	the resulted list OUTPUT
 *	Returns:
 *		SUCCESS, NDTERR, ALLOCERR
 */
ERRCD mergeCList(
	LIST* llist,
	LIST* rlist,
	LIST** list
);

/*
 *	Sorts the elements of the list
 *	Params:
 *		list	-	the list
 *	Returns:
 *		SUCCESS, NDTERR, ALLOCERR
 */
ERRCD sortList(
	LIST* list
);

/*
 *	Destroys a list
 *	Params:
 *		list	-	the list
 *	Returns:
 *		SUCCESS, NDTERR
 */
ERRCD destrList(
	LIST** list
);

/*
 *	Makes an new iterator for the list
 *	Params:
 *		list	-	the list
 * 	Returns:
 *		iter	-	the newly created iterator otherwise
 */
ITER iterator(
	LIST* list
);

/*
 *	Goes the iterator to the next element
 *	Params:
 *		iter	-	the iterator
 */
void next(
	ITER* iter
);

/*
 *	Verifies if iterator is at the end
 *	Params:
 *		iter	-	the iterator
 * 	Returns:
 *		True	-	if not at the end
 *		False	-	otherwise
 */
BOOL notEnd(
	ITER* iter
);


/*
 *	Gets the element pointed by the iterator
 *	Params:
 *		iter	-	the iterator
 *		elem	-	pointer to the element
 * 	Returns:
 *		SUCCESS, NDTERR
 */
ERRCD get(
	ITER* iter,
	int* elem
);

#endif // !LIST_H_

