#include "List.h"

#include <stdlib.h>

// Pair of pointers to the begining and to the end of the list
typedef struct _PAIR {
	NODE* first;
	NODE* last;
}PAIR;
//*/

// Merges two lists
PAIR merge(
	NODE* lfirst,
	NODE* llast,
	NODE* rfirst,
	NODE* rlast
)
{
	NODE dummy; PAIR pair;// = { .first = lfirst,.last = llast };
	NODE* first = &dummy;
	//if (rfirst == NULL) return pair;
	while (lfirst != llast && rfirst != rlast)
	{
		NODE** less = (lfirst->info < rfirst->info)
			? &lfirst : &rfirst;
		(*less)->prev = first;
		first->next = *less;
		first = first->next;
		(*less) = (*less)->next;
	}
	while (lfirst != llast)
	{
		lfirst->prev = first;
		first->next = lfirst;
		lfirst = lfirst->next;
		first = first->next;
	}
	while (rfirst != rlast)
	{
		rfirst->prev = first;
		first->next = rfirst;
		rfirst = rfirst->next;
		first = first->next;
	}
	first->next = lfirst;
	lfirst->prev = first;
	pair.first = dummy.next;
	pair.last = lfirst;
	return pair;
}

LIST* constrList()
{
	LIST* list = (LIST*)malloc(sizeof(LIST));
	if (list == NULL)
		return NULL;
	NODE* dummy = (NODE*)malloc(sizeof(DNODE));
	if (dummy == NULL)
	{
		free(list);
		return NULL;
	}
	((DNODE*)dummy)->size = 0;
	dummy->prev = dummy;
	dummy->next = dummy;
	list->dummy = dummy;
	return list;
}

LIST* copyList(
	const LIST* list
)
{
	LIST* lst = (LIST*)malloc(sizeof(LIST));
	if (lst == NULL)
		return NULL;
	NODE* dummy = (NODE*)malloc(sizeof(DNODE));
	if (dummy == NULL)
	{
		free(lst);
		return NULL;
	}
	((DNODE*)dummy)->size = ((DNODE*)list->dummy)->size;
	dummy->prev = dummy;
	dummy->next = dummy;
	lst->dummy = dummy;
	NODE* ptr = list->dummy;
	while ((ptr = ptr->next) != list->dummy)
	{
		NODE* node = (NODE*)malloc(sizeof(NODE));
		if (node == NULL)
		{
			destrList(&lst);
			return NULL;
		}
		node->info = ptr->info;
		node->next = dummy;
		node->prev = dummy->prev;
		dummy->prev->next = node;
		dummy->prev = node;
	}
	return lst;
}

size_t sizeList(
	const LIST* list
)
{
	if (list == NULL)
		return 0;
	return ((DNODE*)list->dummy)->size;
}

ERRCD addFirstList(
	LIST* list,
	int elem
)
{
	if (list == NULL)
		return NDTERR;
	NODE* node = (NODE*)malloc(sizeof(NODE));
	if (node == NULL)
		return ALLOCERR;
	node->info = elem;
	((DNODE*)list->dummy)->size++;
	node->next = list->dummy->next;
	node->prev = list->dummy;
	list->dummy->next->prev = node;
	list->dummy->next = node;
	return SUCCESS;
}

ERRCD addLastList(
	LIST* list,
	int elem
)
{
	if (list == NULL)
		return NDTERR;
	NODE* node = (NODE*)malloc(sizeof(NODE));
	if (node == NULL)
		return ALLOCERR;
	node->info = elem;
	((DNODE*)list->dummy)->size++;
	node->prev = list->dummy->prev;
	node->next = list->dummy;
	list->dummy->prev->next = node;
	list->dummy->prev = node;
	return SUCCESS;
}

ERRCD pollFirstList(
	LIST* list, 
	int* elem
)
{
	if (list == NULL)
		return NDTERR;
	NODE* first = list->dummy->next;
	if (first == list->dummy)
		return EMPTYCOL;
	((DNODE*)list->dummy)->size--;
	list->dummy->next = first->next;
	first->next->prev = list->dummy;
	if (elem != NULL)
		*elem = first->info;
	free(first);
	if (elem == NULL)
		return INVRETV;
	return SUCCESS;
}

ERRCD pollLastList(
	LIST* list,
	int* elem
)
{
	if (list == NULL)
		return NDTERR;
	NODE* last = list->dummy->prev;
	if (last == list->dummy)
		return EMPTYCOL;
	((DNODE*)list->dummy)->size--;
	list->dummy->prev = last->prev;
	last->prev->next = list->dummy;
	if (elem != NULL)
		*elem = last->info;
	free(last);
	if (elem == NULL)
		return INVRETV;
	return SUCCESS;
}

ERRCD getFirstList(
	LIST* list,
	int* elem
)
{
	if (list == NULL)
		return NDTERR;
	NODE* first = list->dummy->next;
	if (first == list->dummy)
		return EMPTYCOL;
	if (elem == NULL)
		return INVRETV;
	*elem = first->info;
	return SUCCESS;
}

ERRCD getLastList(
	LIST* list, 
	int* elem
)
{
	if (list == NULL)
		return NDTERR;
	NODE* last = list->dummy->prev;
	if (last == list->dummy)
		return EMPTYCOL;
	if (elem != NULL)
		return INVRETV;
	*elem = last->info;
	return SUCCESS;
}

ERRCD mergeCList(
	LIST* llist,
	LIST* rlist, 
	LIST** list
)
{
	*list = NULL;
	if (llist == NULL)
		return NDTERR;
	if (rlist == NULL)
		return NDTERR;
	LIST* flist = copyList(llist);
	if (flist == NULL)
		return ALLOCERR;
	LIST* slist = copyList(rlist);
	if (slist == NULL)
		return ALLOCERR;
	PAIR p = merge(flist->dummy->next, flist->dummy,
					slist->dummy->next, slist->dummy
				);
	p.first->prev = p.last;
	p.last->next = p.first;
	free(slist->dummy);
	*list = (LIST*)malloc(sizeof(LIST));
	if (*list == NULL)
		return ALLOCERR;
	(*list)->dummy = p.last;
	return SUCCESS;
}

ERRCD sortList(
	LIST* list
)
{
	if (list == NULL)
		return NDTERR;
	NODE** vec = (NODE**)malloc(((DNODE*)list->dummy)->size * sizeof(NODE*));
	if (vec == NULL)
		return ALLOCERR;
	int size = ((DNODE*)list->dummy)->size;
	NODE* ptr = list->dummy->next; int i = 0;
	while (ptr != list->dummy)
	{
		vec[i] = ptr;
		ptr = ptr->next;
		vec[i++]->next = list->dummy;
	}
	PAIR pair;
	while (size > 1)
	{
		for (i = 0; i < size / 2; i++)
		{
			pair = merge(vec[2 * i], list->dummy, 
						vec[2 * i + 1], list->dummy
					);
			vec[i] = pair.first;
		}
		if (2 * (size / 2) != size)
		{
			vec[size / 2] = vec[size - 1];
			size++;
		}
		size /= 2;
	}
	list->dummy->next = vec[0];
	vec[0]->prev = list->dummy;
	free(vec);
	return SUCCESS;
}

ERRCD destrList(
	LIST** list
)
{
	if (*list == NULL)
		return NDTERR;
	NODE* ptr = (*list)->dummy->next;
	NODE* next = (*list)->dummy->next->next;
	while (ptr != (*list)->dummy)
	{
		free(ptr);
		ptr = next;
		next = ptr->next;
	}
	free(((DNODE*)(*list)->dummy));
	free(*list);
	*list = NULL;
	return SUCCESS;
}

ITER iterator(
	LIST* list
)
{
	ITER iter; 
	iter.list = NULL;
	iter.current = NULL;
	if (list == NULL)
		return iter;
	iter.list = list;
	iter.current = list->dummy->next;
	return iter;
}

void next(
	ITER* iter
)
{
	if (iter->list == NULL ||
		iter->current == iter->list->dummy
		)
		return ;
	iter->current = iter->current->next;
}

BOOL notEnd(
	ITER* iter
)
{
	if (iter->list == NULL ||
		iter->current == iter->list->dummy
		)
		return False;
	return True;
}

ERRCD get(
	ITER* iter, 
	int* elem
)
{
	if (iter->list == NULL ||
		iter->current == iter->list->dummy
		)
		return NDTERR;
	if (elem != NULL)
		*elem = iter->current->info;
	else
		return NDTERR;
	return SUCCESS;
}
