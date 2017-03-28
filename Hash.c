#include "Hash.h"

#include <math.h>
#include <stdlib.h>

#define FAILRSZ		0		// failed resize
#define INITCAP		7		// initial heap capacity
#define FF			255		// 11111111 on binary
#define LDF			0.7		// the load factor

// The hash function
size_t f(
	int elem,
	size_t max,
	size_t try
)
{
	return ((size_t)elem + try) % max;
}

// Returns the dimension for a set big enough to hold all cells
size_t setDim(
	size_t size
) { 
	return (size / 8) + 1; 
}

// Returns the next prime afther a given number
size_t nextPrime(
	size_t size
)
{	
	while (!prime(++size)) {} 
	return size; 
}

// Verifies if a cell is occupied
BOOL occ(
	char* set,
	size_t pos
)
{
	return set[pos / 8] & (1 << (pos % 8));
}

// Marks a cell
void mark(
	char* set, 
	size_t pos
) 
{ 
	set[pos / 8] |= 1 << (pos % 8); 
}

// Unmark cell
void unmark(
	char* set, 
	size_t pos
) 
{ 
	set[pos / 8] &= FF - (1 << (pos % 8)); 
}

// Finds an element
int* find(
	HASH* hash,
	int elem
)
{
	size_t t = 0;
	while (t < hash->capacity)
	{
		size_t h = f(elem, hash->capacity, t++);
		if (occ(hash->info, h) &&
			hash->elements[h] == elem
			)
			return hash->elements + h;
		if (!occ(hash->full, h))
			return NULL;
	}
	return NULL;
}

// Inserts an element
void insert(
	HASH* hash,
	int elem
)
{
	size_t t = 0;
	while (t < hash->capacity)
	{
		size_t h = f(elem, hash->capacity, t++);
		if (!occ(hash->info, h))
		{
			hash->elements[h] = elem;
			mark(hash->info, h);
			mark(hash->full, h);
			hash->size++;
			break;
		}
	}
}

// Resizes the heap
inline static size_t resize(
	HASH* hash
)
{
	size_t cap = nextPrime(3 * hash->capacity / 2);
	int* elem = (int*)malloc(cap * sizeof(int));
	if (elem == NULL) 
		return FAILRSZ;
	char* info = (char*)malloc(setDim(cap) * sizeof(char));
	if (info == NULL)
	{
		free(elem);
		return FAILRSZ;
	}
	char* full = (char*)malloc(setDim(cap) * sizeof(char));
	if (full == NULL)
	{
		free(elem);
		free(info);
		return FAILRSZ;
	}
	void* ptr = hash->elements; hash->elements = elem; elem = ptr;
	ptr = hash->info; hash->info = info; info = ptr;
	ptr = hash->full; hash->full = full; full = ptr;
	size_t cp = hash->capacity; hash->capacity = cap;
	hash->size = 0;
	for (size_t i = 0; i < setDim(cap); i++)
		hash->full[i] = hash->info[i] = 0;
	for (size_t p = 0; p < cp; p++)
		if (occ(info, p))
			insert(hash, elem[p]);
	free(elem);
	free(info);
	free(full);
	return cap;
}

HASH* constrHash()
{
	HASH* hash = (HASH*)malloc(sizeof(HASH));
	if (hash == NULL)
		return NULL;
	hash->capacity = INITCAP;
	hash->size = 0;
	hash->elements = (int*)malloc(INITCAP * sizeof(int));
	if (hash->elements == NULL)
	{
		free(hash);
		return NULL;
	}
	hash->info = (char*)malloc(setDim(INITCAP) * sizeof(char));
	if (hash->info == NULL)
	{
		free(hash->elements);
		free(hash);
		return NULL;
	}
	hash->full = (char*)malloc(setDim(INITCAP) * sizeof(char));
	if (hash->full == NULL)
	{
		free(hash->elements);
		free(hash->info);
		free(hash);
		return NULL;
	}
	for (size_t i = 0; i < setDim(INITCAP); i++)
		hash->full[i] = hash->info[i] = 0;
	return hash;
}

HASH* copyHash(
	HASH* hash
)
{
	if (hash == NULL)
		return NULL;
	HASH* hh = (HASH*)malloc(sizeof(HASH));
	hh->elements = (int*)malloc(hash->capacity * sizeof(int));
	if (hh->elements == NULL)
	{
		free(hh);
		return NULL;
	}
	hh->info = (char*)malloc(setDim(hash->capacity) * sizeof(char));
	if (hh->info == NULL)
	{
		free(hh->elements);
		free(hh);
		return NULL;
	}
	hh->full = (char*)malloc(setDim(hash->capacity) * sizeof(char));
	if (hh->full == NULL)
	{
		free(hh->elements);
		free(hh->info);
		free(hh);
		return NULL;
	}
	memcopy(hh->elements, hash->elements, hash->capacity);
	memcopy(hh->info, hash->info, setDim(hash->capacity));
	memcopy(hh->full, hash->full, setDim(hash->capacity));
	hh->capacity = hash->capacity;
	hh->size = hash->size;
	return hh;
}

size_t sizeHash(
	const HASH* hash
)
{
	if (hash == NULL)
		return 0;
	return hash->size;
}

size_t capHash(
	const HASH* hash
)
{
	if (hash == NULL)
		return 0;
	return hash->capacity;
}

ERRCD insertHash(
	HASH* hash, 
	int elem
)
{
	if (hash == NULL)
		return NDTERR;
	if ((float)hash->size / hash->capacity > LDF &&
		resize(hash) == FAILRSZ
		)
		return ALLOCERR;
	if (find(hash, elem) != NULL)
		return DUPLCT;
	insert(hash, elem);
	return SUCCESS;
}

ERRCD eraseHash(
	HASH* hash, 
	int elem
)
{
	if (hash == NULL)
		return NDTERR;
	int* pelem = find(hash, elem);
	if (pelem != NULL)
		unmark(hash->info, pelem - hash->elements);
	else
		return NOTFND;
	return SUCCESS;
}

ERRCD findHash(HASH* hash, int elem, BOOL* found)
{
	if (hash == NULL)
		return NDTERR;
	if (find(hash, elem) == NULL)
	{
		if (found != NULL)
			*found = False;
		return NFOUND;
	}
	else
	{
		if (found != NULL)
			*found = True;
		return FOUND;
	}
}

ERRCD destrHash(
	HASH** hash
)
{
	if (*hash == NULL)
		return NDTERR;
	if ((*hash)->elements != NULL)
		free((*hash)->elements);
	if ((*hash)->info != NULL)
		free((*hash)->info);
	if ((*hash)->full != NULL)
		free((*hash)->full);
	free(*hash);
	*hash = NULL;
	return SUCCESS;
}
