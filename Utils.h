#ifndef UTILS_H_
#define UTILS_H_

#include <limits.h>

/*
 *	Define boolean values
 */
#define FALSE 0
#define TRUE 1

typedef unsigned char BOOL;

enum __boolean{
	False	= 0, 
	True	= 1
};

/*
 *	Function to swap two integers
 *	Params:
 *		lint	-	left int
 *		rint	-	right int
 */
inline void swap(
	int* lint, 
	int* rint
)
{
	*lint ^= *rint;
	*rint ^= *lint;
	*lint ^= *rint;
}

/*
 *	Function to verify if a pozitive number is prime
 *	Params:
 *		size	-	the number 
 *	Returns:
 *		True	-	the number is prime
 *		False	-	the number is composed
 */
inline BOOL prime(
	size_t size
)
{
	for (size_t c = 2; c < size / 2; c++)
		if (size % 2 == 0)
			return False;
	return True;
}

/*
 *	Function to compute module of an integer
 *	Params:
 *		number	-	the integer
 *	Returns:
 *		nr		-	the module of number
 */
inline int module(
	int number
)
{
	if (number >= 0)
		return number;
	else
		return -number;
}

/*
 *	Function to find the minimum of two integer numbers
 *	Params:
 *		lnr		-	the first integer
 *		rnr		-	the second integer
 *	Returns:
 *		lnr		-	if lnr < rnr
 *		rnr		-	if lnr > rnr
 */
inline int less(
	int lnr,
	int rnr
)
{
	if (lnr < rnr)
		return lnr;
	else
		return rnr;
}

/*
 *	Function to find the maximum of two integer numbers
 *	Params:
 *		lnr		-	the first integer
 *		rnr		-	the second integer
 *	Returns:
 *		lnr		-	if lnr > rnr
 *		rnr		-	if lnr < rnr
 */
inline int more(
	int lnr,
	int rnr
)
{
	if (lnr < rnr)
		return rnr;
	else
		return lnr;
}

/*
 *	Function to compare two integers given as pointers
 *	Both pointers have to belong to the same space, to be less thn maxp
 *	Params:
 *		lint	-	left int
 *		rint	-	right int
 *		maxp	-	maximum pointer
 *	Returns:
 *		lint	-	if rint > maxp or *lint < *rint
 *		rint	-	if *rint < *lint
 */
inline int* minim(
	int* lint,
	int* rint,
	int* maxp
)
{
	if (rint > maxp || *lint < *rint)
		return lint;
	else
		return rint;
}

/*
 *	Function of the type memcpy from string.h
 *	Copies count bytes of data from source to destination
 *	Params:
 *		dest	-	generic pointer to destination
 *		source	-	generic pointer to source
 *		count	-	number of bytes to be copied
 *	Returns:
 *		source	-	generic pointer to the source
 */
inline void* memcopy(
	void* dest,
	void* source,
	size_t count
)
{
	for (size_t c = 0; c < count; c++)
		((char*)dest)[c] = ((char*)source)[c];
	return source;
}

#endif // !UTILS_H_
