#ifndef VECTOR_H_
#define VECTOR_H_

#include "Error.h"
#include "Utils.h"

/*
 *	Header for dynamic vector data structure
 *	
 *	Observations:
 *		-->	most of the functions return an error code (ERRCD) defined in Error.h
 *		--> if the error code is different from SUCCES a problem occured and
 *				the returned value cannot be used
 *		--> on any function that has a return parameter, if the NULL value is passed
 *				than the value is considered to be ignored
 */

/*
 *	Data type structure for the vector
 *	Contains all the information needed for managing the vector
 */
typedef struct _VECTOR{
	size_t capacity;
	size_t size;
	int* elements;
}VECTOR;

/*
 *	Constructs a vector
 *	Returns:
 *		NULL	-	if the vector could not be created
 *		vec		-	the newly created empty vector otherwise
 */
VECTOR* constrVec();

/*
 *	Copies a vector
 *	Params:
 *		vec		-	the vector to be copied
 *	Returns:
 *		NULL	-	if the vector could not be copied
 *		vect	-	the copied vector otherwise
 */
VECTOR* copyVec(
	const VECTOR* vec
);

/*
 *	Gets the size of the vector
 *	Params:
 *		vec		-	the vector
 *	Returns:
 *		size	-	the size of the vector
 */
size_t sizeVec(
	const VECTOR* vec
);

/*
 *	Gets the capacity of the vector
 *	Params:
 *		vec		-	the vector
 *	Returns:
 *		cap		-	the capacity of the vector
 */
size_t capVec(
	const VECTOR* vec
);

/*
 *	Appends an element on the back of the vector
 *	Params:
 *		vec		-	the vector
 *		elem	-	the element
 *	Returns:
 *		SUCCESS, NDTERR, ALLOCERR
 */
ERRCD appendVec(
	VECTOR* vec, 
	int elem
);

/*
 *	Retrives the last element of the vector
 *	Params:
 *		vec		-	the vector
 *		elem	-	the element OUTPUT
 *	Returns:
 *		SUCCESS, INVRETV, NDTERR, EMPTYCOL
 */
ERRCD retriveVec(
	VECTOR* vec,
	int* elem
);

/*
 *	Inserts an element on a position in the vector
 *	Params:
 *		vec		-	the vector
 *		pos		-	the position
 *		elem	-	the element 
 *	Returns:
 *		SUCCESS, NDTERR, ALLOCERR, IDXOBND
 */
ERRCD insertVec(
	VECTOR* vec, 
	size_t pos, 
	int elem
);

/*
 *	Deletes an element from a position in the vector
 *	Params:
 *		vec		-	the vector
 *		pos		-	the position
 *	Returns:
 *		SUCCESS, NDTERR, IDXOBND
 */
ERRCD deleteVec(
	VECTOR* vec,
	size_t pos
);

/*
 *	Eliminates all the occurences of an element from the vector
 *	Params:
 *		vec		-	the vector
 *		elem	-	the element
 *	Returns:
 *		SUCCESS, NOTFND, NDTERR
 */
ERRCD elimVec(
	VECTOR* vec,
	int elem
);	

/*
 *	Gets an element from a position in the vector
 *	Params:
 *		vec		-	the vector
 *		pos		-	the position
 *		elem	-	the element OUTPUT
 *	Returns:
 *		SUCCESS, INVRETV, NDTERR, IDXOBND
 */
ERRCD getVec(
	const VECTOR* vec,
	size_t pos,
	int* elem
);

/*
 *	Sets an element from a specified position in the vector
 *	Params: 
 *		vec		-	the vector
 *		pos		-	the position
 *		elem	-	the element
 *	Returns:
 *		SUCCESS, NDTERR, IDXOBND
 */
ERRCD setVec(
	const VECTOR* vec, 
	size_t position, 
	int element
);

/*
 *	Finds an element into the vector
 *  Params:
 *		vec		-	the vector
 *		elem	-	the element
 *		pos		-	the first position OUTPUT
 *	Returns:
 *		NDTERR
 *		FOUND	-	element was found
 *		NFOUND	-	element was not found
 */
ERRCD findVec(
	VECTOR* vec,
	int elem,
	size_t* pos
);

/*
 *	Destroys a vector
 *	Params:
 *		vec		-	the vector
 *	Returns :
 *		SUCCESS, NDTERR
 */
ERRCD destrVec(
	VECTOR** vec
);

#endif // VECTOR_H_
