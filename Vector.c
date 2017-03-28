#include "Vector.h"

#include <stdlib.h>

#define FAILRSZ 0		// failed resize
#define INITCAP 2		// initial vector capacity

// Resizes the vector
inline static size_t resize(
	VECTOR* vec
)
{
	size_t cap = (vec->capacity * 3) / 2;
	int* elem = (int*)malloc(cap * sizeof(int));
	if (elem == NULL)
		return FAILRSZ;
	memcopy(elem, vec->elements, vec->size * sizeof(int));
	free(vec->elements);
	vec->elements = elem;
	vec->capacity = cap;
	return cap;
}

VECTOR* constrVec()
{
	VECTOR* vec = (VECTOR*)malloc(sizeof(VECTOR));
	if (vec == NULL) 
		return NULL;
	vec->capacity = INITCAP;
	vec->size = 0;
	vec->elements = (int*)malloc(INITCAP * sizeof(int));
	if (vec->elements == NULL)
	{
		free(vec);
		return NULL;
	}
	return vec;
}

VECTOR* copyVec(
	const VECTOR* vec
)
{
	if (vec == NULL)
		return NULL;
	VECTOR* vect = (VECTOR*)malloc(sizeof(VECTOR));
	if (vect == NULL)
		return NULL;
	vect->elements = (int*)malloc(vec->capacity * sizeof(int));
	if (vect->elements == NULL)
	{
		free(vect);
		return NULL;
	}
	memcopy(vect->elements, vec->elements, vec->size * sizeof(int));
	vect->capacity = vec->capacity;
	vect->size = vec->size;
	return vect;
}

size_t sizeVec(
	const VECTOR* vec
)
{
	if (vec == NULL)
		return 0;
	return vec->size;
}

size_t capVec(
	const VECTOR* vec
)
{
	if (vec == NULL)
		return 0;
	return vec->capacity;
}

ERRCD appendVec(
	VECTOR* vec, 
	int element
)
{
	if (vec == NULL)
		return NDTERR;
	if (vec->size == vec->capacity && 
		resize(vec) == FAILRSZ
		)
		return ALLOCERR;
	vec->elements[vec->size++] = element;
	return SUCCESS;
}

ERRCD retriveVec(
	VECTOR* vec,
	int* elem
)
{
	if (vec == NULL)
		return NDTERR;
	if (vec->size == 0)
		return EMPTYCOL;
	if (elem == NULL)
		vec->size--;
	else 
		*elem = vec->elements[--vec->size];
	if (elem == NULL)
		return INVRETV;
	return SUCCESS;
}

ERRCD insertVec(
	VECTOR* vec,
	size_t pos,
	int elem
)
{
	if (vec == NULL)
		return NDTERR;
	if (pos > vec->size || pos < 0)
		return IDXOBND;
	if (vec->size == vec->capacity &&
		resize(vec) == FAILRSZ
		)
		return ALLOCERR;
	for (size_t i = vec->size; i > pos; i--)
		vec->elements[i] = vec->elements[i - 1];
	vec->elements[pos] = elem;
	vec->size++;
	return SUCCESS;
}

ERRCD deleteVec(
	VECTOR* vec,
	size_t pos
)
{
	if (vec == NULL)
		return NDTERR;
	if (pos >= vec->size || pos < 0)
		return IDXOBND;
	for (size_t i = pos; i < vec->size; i++)
		vec->elements[i] = vec->elements[i + 1];
	vec->size--;
	return SUCCESS;
}

ERRCD elimVec(
	VECTOR* vec,
	int elem
)
{
	if (vec == NULL)
		return NDTERR;
	size_t p = (unsigned int)-1;
	ERRCD ret = NOTFND;
	while (++p < vec->size)
		if (vec->elements[p] == elem)
		{
			deleteVec(vec, p);
			ret = SUCCESS;
			p -= 1;
		}
	return ret;
}

ERRCD getVec(
	const VECTOR* vec, 
	size_t pos,
	int* elem
)
{
	if (vec == NULL)
		return NDTERR;
	if (pos >= vec->size || pos < 0)
		return IDXOBND;
	if (elem == NULL)
		return INVRETV;
	*elem = vec->elements[pos];
	return SUCCESS;
}

ERRCD setVec(
	const VECTOR* vec,
	size_t pos,
	int elem
)
{
	if (vec == NULL)
		return NDTERR;
	if (pos >= vec->size || pos < 0)
		return IDXOBND;
	vec->elements[pos] = elem;
	return SUCCESS;
}

ERRCD findVec(
	VECTOR* vec,
	int elem,
	size_t* pos
)
{
	if (vec == NULL)
		return NDTERR;
	for (size_t p = 0; p < vec->size; p++)
	{
		if (vec->elements[p] == elem)
		{
			if (pos != NULL)
				*pos = p;
			return FOUND;
		}
	}
	if (pos != NULL)
		*pos = vec->size;
	return NFOUND;
}

ERRCD destrVec(
	VECTOR** vec
)
{
	if (*vec == NULL)
		return NDTERR;
	if ((*vec)->elements != NULL)
		free((*vec)->elements);
	free(*vec);
	*vec = NULL;
	return SUCCESS;
}
