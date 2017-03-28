#ifndef TREE_H_
#define TREE_H_

#include "Error.h"
#include "Utils.h"

#include <stdio.h>

/*
 *	Header for tree data structure 
 *
 *	Observations:
 * 		-->	most of the functions return an error code (ERRCD) defined in Error.h
 * 		--> if the error code is different from SUCCES a problem occured and
 *				the returned value cannot be used
 *		--> on any function that has a return parameter, if the NULL value is passed
 *				than the value is considered to be ignored
 */

 /*
 *	Data type structure for a node of the tree
 *	Contains the information (info), the balance of the node
 *		and pointer to the left child and to the right child
 */
typedef struct _TNODE {
	struct _TNODE* left;
	struct _TNODE* right;
	int balance;
	int info;
}TNODE;

/*
 *	Data type structure for the tree
 *	Contains the pointer to the dummy node
 */
typedef struct _TREE {
	struct _TNODE* top;
	size_t size;
}TREE;

/*
*	Constructs a tree
* 	Returns:
*		NULL	-	if the tree could not be created
*		tree	-	the newly created empty tree otherwise
*/
TREE* constrTree();

/*
*	Copies a tree
*	Params:
*		tree	-	the tree to be copied
*	Returns:
*		NULL	-	if the tree could not be copied
*		tr		-	the copied tree otherwise

TREE* copyTree(
	const TREE* tree
);*/

/*
 *	Gets the size of the tree
 *	Params:
 *		tree	-	the tree
 *  	Returns:
 *		size	-	the size of the tree
 */
size_t sizeTree(
	const TREE* tree
);

/*
 *	Inserts an element into the tree
 *	Params:
 *		tree	-	the tree
 *		elem	-	the element
 *	Returns:
 *		SUCCESS, DUPLCT, NDTERR, ALLOCERR
 */
ERRCD insertTree(
	TREE* tree,
	int elem
);

/*
 *	Deletes an element from the tree
 *	Params:
 *		tree	-	the tree
 *		elem	-	the element
 *	Returns:
 *		SUCCESS, NOTFND, NDTERR
 */
ERRCD deleteTree(
	TREE* tree,
	int elem
);

/*
 *	Finds an element into the tree
 *  Params:
 *		tree	-	the tree
 *		elem	-	the element
 *		found	-	True if found, False otherwise OUTPUT
 *	Returns:
 *		NDTERR
 *		FOUND	-	element was found
 *		NFOUND	-	element was not found
 */
ERRCD findTree(
	TREE* tree,
	int elem,
	BOOL* found
);


/*
 *	Destroys a tree
 *	Params:
 *		tree	-	the tree
 *	Returns:
 *		SUCCESS, NDTERR
 */
ERRCD destrTree(
	TREE** tree
);

#ifdef DBGAPP

void printNode(
	TNODE* node
)
{
	printf("%6d b = %2d -> ", node->info, node->balance);
	if (node->left != NULL)
		printf("%6d | ", node->left->info);
	else
		printf("%6s | ", "NULL");
	if (node->right != NULL)
		printf("%6d ;\n", node->right->info);
	else
		printf("%6s ;\n", "NULL");
	if (node->left != NULL)
		printNode(node->left);
	if (node->right != NULL)
		printNode(node->right);
}

int height(
	TNODE* node
)
{
	if (node == NULL)
		return 0;
	return 1 + more(
		height(node->left),
		height(node->right)
	);
}

int sizet(
	TNODE* node
)
{
	if (node == NULL)
		return 0;
	return 1 +
		sizet(node->left) +
		sizet(node->right);
}

#endif // DBGAPP


#endif // !TREE_H_
