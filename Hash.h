#ifndef HASH_H_
#define HASH_H_

#include "Error.h"
#include "Utils.h"

/*
 *	Header for hash data structure
 *
 *	Observations:
 *		-->	most of the functions return an error code (ERRCD) defined in Error.h
 * 		--> if the error code is different from SUCCES a problem occured and
 *				the returned value cannot be used
 *		--> on any function that has a return parameter, if the NULL value is passed
 *				than the value is considered to be ignored
 */

/*
 *	Data type structure for the hash table with open addresing
 *	Contains all the informations needed for managing the hash
 *	The info part is a bit set containing the cells which have information in them
 *	The full part is a bit set containing the cells which are full there for 
 *		they have to be accounted for in the process of searching ( on deletion a cell 
 *		is only marked as free, but the information is not removed)
 */
typedef struct _HASH {
	size_t capacity;
	size_t size;
	char* info;
	char* full;
	int* elements;
}HASH;

size_t setDim(size_t size);
size_t nextPrime(size_t size);
void mark(char* set, size_t pos);
void unmark(char* set, size_t pos);
BOOL occ(
	char* set,
	size_t pos
);

/*
 *	Constructs a hash table
 *	Returns:
 *		NULL	-	if the hash table could not be created
 *		hash	-	the newly created empty hash table otherwise
 */
HASH* constrHash();

/*
 *	Copies a hash
 *	Params:
 *		hash	-	the hash table to be copied
 *	Returns:
 *		NULL	-	if the hash table could not be copied
 *		hh		-	the copied hash table otherwise
 */
HASH* copyHash(
	 HASH* hash
);

/*
 *	Gets the size of the hash table
 *	Params:
 *		hash	-	the hash table
 *	Returns:
 *		size	-	the size of the hash table
 */
size_t sizeHash(
	const HASH* hash
);

/*
 *	Gets the capacity of the hash table
 *	Params:
 *		hash	-	the hash table
 *	Returns:
 *		cap		-	the capacity of the hash table
 */
size_t capHash(
	const HASH* hash
);

/*
 *	Inserts an element into the hash table
 *	Params:
 *		hash	-	the hash table
 *		elem	-	the element
 *	Returns:
 *		SUCCESS, DUPLCT, NDTERR, ALLOCERR
 */
ERRCD insertHash(
	HASH* hash,
	int elem
);

/*
 *	Erases an element from the hash table
 *	Params:
 *		hash	-	the hash table
 *		elem	-	the element
 *	Returns:
 *		SUCCESS, NOTFND, NDTERR
 */
ERRCD eraseHash(
	HASH* hash,
	int elem
);

/*
 *	Finds an element into the hash table
 *  Params:
 *		hash	-	the hash table
 *		elem	-	the element 
 *		found	-	True if found, False otherwise OUTPUT
 *	Returns:
 *		NDTERR
 *		FOUND	-	element was found
 *		NFOUND	-	element was not found
 */
ERRCD findHash(
	HASH* hash,
	int elem,
	BOOL* found
);

/*
 *	Destroys a hash table
 *	Params:
 *		hash	-	the hash table
 *	Returns:
 *		SUCCESS, NDTERR
 */
ERRCD destrHash(
	HASH** hash
);

#endif // !HASH_H_
