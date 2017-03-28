#include "Tree.h"

#include <stdlib.h>

void balance(
	TNODE** node
)
{
	if ((*node)->balance == -2)							// left inbalance
	{
		TNODE* parent = *node;
		TNODE* leftChild = (*node)->left;
		TNODE* leftDown = (*node)->left->right;
		if (leftChild->balance == -1)					// left left case
		{
			parent->left = leftChild->right;
			leftChild->right = parent;
			leftChild->balance = 0;
			parent->balance = 0;
			*node = leftChild;
			return;
		}
		if (leftChild->balance == 0)					// left 0 delition case
		{
			parent->left = leftChild->right;
			leftChild->right = parent;
			leftChild->balance = 1;
			parent->balance = -1;
			*node = leftChild;
			return;
		}
		if (leftChild->balance == 1)					// left right case
		{
			leftChild->right = leftDown->left;
			parent->left = leftDown->right;
			leftDown->left = leftChild;
			leftDown->right = parent;
			leftChild->balance =
				0 - more(leftDown->balance, 0);
			parent->balance = 
				0 - less(leftDown->balance, 0);
			leftDown->balance = 0;
			*node = leftDown;
			return;
		}
	}
	if ((*node)->balance == 2)							// right right case
	{
		TNODE* parent = *node;
		TNODE* rightChild = (*node)->right;
		TNODE* rightDown = (*node)->right->left;
		if (rightChild->balance == 1)
		{
			parent->right = rightChild->left;
			rightChild->left = parent;
			rightChild->balance = 0;
			parent->balance = 0;
			*node = rightChild;
			return;
		}
		if (rightChild->balance == 0)					// right 0 delition case
		{
			parent->right = rightChild->left;
			rightChild->left = parent;
			rightChild->balance = -1;
			parent->balance = 1;
			*node = rightChild;
			return;
		}
		if (rightChild->balance == -1)					// right left case
		{
			rightChild->left = rightDown->right;
			parent->right = rightDown->left;
			rightDown->left = parent;
			rightDown->right = rightChild;
			parent->balance =
				0 - more(rightDown->balance, 0);
			rightChild->balance =
				0 - less(rightDown->balance, 0);
			rightDown->balance = 0;
			*node = rightDown;
			return;
		}
	}
}

TREE* constrTree()
{
	TREE* tree = (TREE*)malloc(sizeof(TREE));
	if (tree == NULL)
		return NULL;
	tree->top = NULL;
	tree->size = 0;
	return tree;
}

size_t sizeTree(
	const TREE* tree
)
{
	if (tree == NULL)
		return 0;
	return tree->size;
}

ERRCD insertTree(
	TREE* tree,
	int elem
)
{
	if (tree == NULL)
		return NDTERR;
	TNODE* node = (TNODE*)malloc(sizeof(TNODE));
	if (node == NULL)
		return ALLOCERR;
	node->balance = 0;
	node->info = elem;
	node->left = NULL;
	node->right = NULL;
	TNODE** nodes[50];  int c = 0;
	nodes[0] = &tree->top;
	while (
		*nodes[c] != NULL &&				// not at the end  
		(*nodes[c])->info != elem			// not at the element
	)
	{
		if (elem < (*nodes[c])->info)
			nodes[c + 1] = &(*nodes[c])->left;
		else
			nodes[c + 1] = &(*nodes[c])->right;
		c += 1;
	}
	if (*nodes[c] != NULL)
	{
		free(node);
		return DUPLCT;
	}
	*nodes[c] = node;
	tree->size += 1;
	while (--c >= 0)
	{
		if ((*nodes[c])->left == *nodes[c + 1])
			(*nodes[c])->balance -= 1;
		else 
			(*nodes[c])->balance += 1;
		if ((*nodes[c])->balance == 0)
			return SUCCESS;
		if (module((*nodes[c])->balance) == 2)
		{
			balance(nodes[c]);
			return SUCCESS;
		}
	}
	return SUCCESS;
}

ERRCD deleteTree(
	TREE* tree,
	int elem
)
{
	if (tree == NULL)
		return NDTERR;
	TNODE** nodes[50];  int c = 0;
	nodes[0] = &tree->top;
	while (
		*nodes[c] != NULL &&				// not at the end  
		(*nodes[c])->info != elem			// not at the element
		)
	{
		if (elem < (*nodes[c])->info)
			nodes[c + 1] = &(*nodes[c])->left;
		else
			nodes[c + 1] = &(*nodes[c])->right;
		c += 1;
	}
	if (*nodes[c] == NULL)
		return NOTFND;
	tree->size -= 1;
	TNODE* found = *nodes[c];
	if ((*nodes[c])->left != NULL &&
		(*nodes[c])->right != NULL
		)
	{
		nodes[++c] = &(*nodes[c - 1])->right;
		while ((*nodes[c])->left != NULL)
		{
			nodes[c + 1] = &(*nodes[c])->left;
			c += 1;
		}
		found->info = (*nodes[c])->info;
	}
	TNODE* elim = *nodes[c];
	if ((*nodes[c])->left == NULL &&
		(*nodes[c])->right == NULL
		)
	{
		if (c > 0)
		{
			(*nodes[c - 1])->balance +=
				((*nodes[c - 1])->left == *nodes[c])
					? 1 : -1;
			if (module((*nodes[c - 1])->balance) == 2)
				balance(nodes[c - 1]);
		}
		free(*nodes[c]);
		*nodes[c] = NULL;
		c -= 1;
		if (c > 0 &&
			module((*nodes[c])->balance) == 1
			)
			return SUCCESS;
	}
	else if ((*nodes[c])->left == NULL)
	{                     
		*nodes[c] = elim->right;
		free(elim);
	}
	else if ((*nodes[c])->right == NULL)
	{            
		*nodes[c] = elim->left;
		free(elim);
	}
	while (--c >= 0)
	{
		if ((*nodes[c])->left == *nodes[c + 1])
			(*nodes[c])->balance += 1;
		else 
			(*nodes[c])->balance -= 1;
		if (module((*nodes[c])->balance) == 2)
			balance(nodes[c]);
		if (module((*nodes[c])->balance) == 1)
			return SUCCESS;
	}
	return SUCCESS;
}

ERRCD findTree(
	TREE* tree,
	int elem,
	BOOL* found
)
{
	if (tree == NULL)
		return NDTERR;
	TNODE* node = tree->top;
	while (
		node != NULL &&
		node->info != elem
		)
	{
		if (elem < node->info)
			node = node->left;
		else if (elem > node->info)
			node = node->right;
	}
	if (node == NULL)
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

ERRCD destrTree(
	TREE** tree
)
{
	if (*tree == NULL)
		return NDTERR;
	TNODE** node[50]; int c = 0;
	node[0] = &(*tree)->top;
	if ((*tree)->top != NULL)
		while (c >= 0)
		{
			if ((*node[c])->left != NULL)
			{
				node[++c] = &((*node[c - 1])->left);
				continue;
			}
			if ((*node[c])->right != NULL)
			{
				node[++c] = &((*node[c - 1])->right);
				continue;
			}
			free(*node[c]);
			*node[c] = NULL;
			c -= 1;
		}
	free(*tree);
	*tree = NULL;
	return SUCCESS;
}
