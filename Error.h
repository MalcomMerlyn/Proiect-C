#ifndef ERROR_H_
#define ERROR_H_

/*
 *	Define the errors
 */
/*
 * Codes :  0 - 15 
 * Informational codes
 * Execution sucessful
 * Execution can continue
 */
#define SUCCESS		0		// No error, executions was successfull 
#define FOUND		1		// Found element on findTree of findHash
#define NFOUND		2		// Not found element on findTree of findHash

/*
 * Codes : 16 - 31
 * Information data lost codes 
 * Execution sucessful 
 * Execution can continue
 */
#define INVRETV		16		// Invalid pointer for output parameter, no return
#define DUPLCT		17		// Duplicated element in tree or heap will not be inserted
#define NOTFND		18		// Elemen to be deleted does not exist in tree or hash

 /*
 * Codes : 32 - 63
 * Problem occured 
 * Execution failed 
 * Execution can continue
 */
#define NDTERR		32		// Received pointer or data structure was NULL 
#define ALLOCERR	33		// Data allocation failed 
#define EMPTYCOL	34		// Data structure (collection) has no element
#define IDXOBND		35		// Index out of bound in vector

// Error type
typedef char ERRCD;

#endif // !ERROR_H_
