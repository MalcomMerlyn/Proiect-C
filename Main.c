#include <Error.h>
#include <Hash.h>
#include <Heap.h>
#include <List.h>
#include <Tree.h>
#include <Vector.h>

#include <stdio.h>
#include <stdlib.h>

#include "TestUtils.h"

#define BFSZ 10000
#define NR	12

const char* invinp = "INVALID_INPUT\n";
const char* invcomm = "INVALID_COMMAND\n";
const char* idxoobnd = "INDEX_OUT_OF_BOUNDS\n";
const char* notfound = "NOT_FOUND\n";
const char* found = "FOUND\n";
const char* csundef = "CURRENT_STRUCTURE_UNDEFINED\n";
const char* psundef = "PREVIOUS_STRUCTURE_UNDEFINED\n";
const char* nrstrex = "NUMBER_OF_STRUCTURES_EXCEEDED\n";
const char* caplim = "CAPACITY_LIMIT_REACHED\n";


int test(
	const char* input, 
	const char* output
)
{
	FILE* in; FILE* out;
	if (fopen_s(&in, input, "r+") 
			!= EXIT_SUCCESS)
		return -1;
	if (fopen_s(&out, output, "w+") 
			!= EXIT_SUCCESS) 
		return -1;
	HASH* hash[10]; int chash = 0; int fhash = 0;
	HEAP* heap[10]; int cheap = 0; int fheap = 0;
	LIST* list[10]; int clist = 0; int flist = 0;
	TREE* tree[10]; int ctree = 0; int ftree = 0;
	VECTOR* vec[10]; int cvec = 0; int fvec = 0;
	for (int i = 0; i < 10; i++)
	{
		hash[i] = NULL;
		heap[i] = NULL;
		list[i] = NULL;
		tree[i] = NULL;
		vec[i] = NULL;
	}
	char comm[500]; int n, code, elem; size_t pos;
 	while (!feof(in))
	{
		fgets(comm, BFSZ, in);
		if (command(comm, "VectorGoTo"))
		{
			readNumber(in, &n); 
			if (n < 0 || n > 10)
				fprintf(out, "%s", idxoobnd);
			else
				cvec = n;
		}
		else if (command(comm, "VectorRead"))
		{
			if (fvec == 10)
			{
				fprintf(out, "%s", nrstrex);
				fgets(comm, BFSZ, in);
				continue;
			}
			cvec = fvec; fvec++;
			vec[cvec] = constrVec();
			while ((code = readNumber(in, &n)) == True)
				appendVec(vec[cvec], n);
			if (code == STOP)
			{
				appendVec(vec[cvec], n);
				continue;
			}
			if (code == INVCOMM)
				fprintf(out, "%s", invinp);
			if (code == NOTNUMBER)
			{
				fprintf(out, "%s", invinp);
				fgets(comm, BFSZ, in);
			}
		}
		else if (command(comm, "VectorAdd"))
		{
			if (sizeVec(vec[cvec]) == MAXSIZE)
			{
				fprintf(out, "%s", caplim);
				fgets(comm, BFSZ, in);
				continue;
			}
			code = readNumber(in, &n);
			if (code == NOTNUMBER)
			{
				fprintf(out, "%s", invinp);
				fgets(comm, BFSZ, in);
			}
			else if (code == STOP)
			{
				if (appendVec(vec[cvec], n) == NDTERR)
					fprintf(out, "%s", csundef);
			}
			else
			{
				if (readNumber(in, &elem) == False)
				{
					if (appendVec(vec[cvec], n) == NDTERR)
						fprintf(out, "%s", csundef);
					continue;
				}
				fprintf(out, "%s", invinp);
				fgets(comm, BFSZ, in);
			}
		}
		else if (command(comm, "VectorLength"))
		{
			if (vec[cvec] == NULL)
				fprintf(out, "%s", csundef);
			else
				fprintf(out, "%d\n", sizeVec(vec[cvec]));
		}
		else if (command(comm, "VectorRemovePosition"))
		{
			code = readNumber(in, &n);
			if (code == NOTNUMBER)
			{
				fprintf(out, "%s", invinp);
				fgets(comm, BFSZ, in);
			}
			else if (code == STOP)
			{
				code = deleteVec(vec[cvec], n);
				if (code == NDTERR)
					fprintf(out, "%s", csundef);
				if (code == IDXOBND)
					fprintf(out, "%s", idxoobnd);
			}
			else
			{
				if (readNumber(in, &elem) == False)
				{
					code = deleteVec(vec[cvec], n);
					if (code == NDTERR)
						fprintf(out, "%s", csundef);
					if (code == IDXOBND)
						fprintf(out, "%s", idxoobnd);
					continue;
				}
				fprintf(out, "%s", invinp);
				fgets(comm, BFSZ, in);
			}
		}
		else if (command(comm, "VectorRemoveValue"))
		{
			if (readNumber(in, &n) == NOTNUMBER)
			{
				fprintf(out, "%s", invinp);
				fgets(comm, BFSZ, in);
			}
			else
			{
				code = elimVec(vec[cvec], n);
				if (code == NDTERR)
					fprintf(out, "%s", csundef);
				if (code == NOTFND)
					fprintf(out, "%s", notfound);
			}
		}
		else if (command(comm, "VectorSearch"))
		{
			if (readNumber(in, &n) == NOTNUMBER)
			{
				fprintf(out, "%s", invinp);
				fgets(comm, BFSZ, in);
			}
			else
			{
				code = findVec(vec[cvec], n, &pos);
				if (code == NDTERR)
					fprintf(out, "%s", csundef);
				else if (code == NFOUND)
					fprintf(out, "%s", notfound);
				else if (code == FOUND)
					fprintf(out, "%d\n", pos);
			}
		}
		else if (command(comm, "VectorPrint"))
		{
			if (vec[cvec] == NULL)
				fprintf(out, "%s", csundef);
			else
			{
				size_t i;
				for (i = 0; i < sizeVec(vec[cvec]); i++)
				{
					getVec(vec[cvec], i, &n);
					fprintf(out, "%d ", n);
				}
				fprintf(out, "\n");
			}
		}
		else if (command(comm, "ListGoTo"))
		{
			readNumber(in, &n); 
			if (n < 0 || n > 10)
				fprintf(out, "%s", idxoobnd);
			else
				clist = n;
		}
		else if (command(comm, "ListRead"))
		{
			if (flist == 10)
			{
				fprintf(out, "%s", nrstrex);
				fgets(comm, BFSZ, in);
				continue;
			}
			int c = clist; clist = flist; flist++;
			list[clist] = constrList();
			while ((code = readNumber(in, &n)) == True)
				addLastList(list[clist], n);
			if (code == STOP) 
				addLastList(list[clist], n);
			if (code == NOTNUMBER)
			{
				fprintf(out, "%s", invinp);
				fgets(comm, BFSZ, in);
			}
			if (code == False && sizeList(list[clist]) == 0)
			{
				fprintf(out, "%s", invinp);
				destrList(&list[clist]);
				flist -= 1; clist = c;
			}
		}
		else if (command(comm, "ListAdd"))
		{
			if (sizeList(list[clist]) == MAXSIZE)
			{
				fprintf(out, "%s", caplim);
			}
			code = readNumber(in, &n);
			if (code == NOTNUMBER)
			{
				fprintf(out, "%s", invinp);
				fgets(comm, BFSZ, in);
			}
			else if (code == STOP)
			{
				if (addLastList(list[clist], n) == NDTERR)
					fprintf(out, "%s", csundef);
			}
			else
			{
				code = readNumber(in, &elem);
				if (code == False)
				{
					if (addLastList(list[clist], n) == NDTERR)
						fprintf(out, "%s", csundef);
					continue;
				}
				fprintf(out, "%s", invinp);
				if (code != STOP)
					fgets(comm, BFSZ, in);
			}
		}
		else if (command(comm, "ListPrint"))
		{
			if (list[clist] == NULL)
				fprintf(out, "%s", csundef);
			else
			{
				for (ITER iter = iterator(list[clist]); notEnd(&iter); next(&iter))
				{
					get(&iter, &n);
					fprintf(out, "%d ", n);
				}
				fprintf(out, "\n");
			}
		}
		else if (command(comm, "ListMerge"))
		{
			if (list[clist] == NULL)
				fprintf(out, "%s", csundef);
			else if (list[clist - 1] == NULL || clist == 0)
				fprintf(out, "%s", psundef);
			else
			{
				mergeCList(list[clist - 1], list[clist], &list[flist]);
				if (sizeList(list[flist]) > MAXSIZE)
					destrList(&list[flist]);
				else
				{
					clist = flist;
					flist++;
				}
			}
		}
		else if (command(comm, "ListSort"))
		{
			if (list[clist] == NULL)
				fprintf(out, "%s", csundef);
			else
				sortList(list[clist]);
		}
		else if (command(comm, "HashTableGoTo"))
		{
			readNumber(in, &n);
			if (n < 0 || n > 10)
				fprintf(out, "%s", idxoobnd);
			else
				chash = n;
		}
		else if (command(comm, "HashTableRead"))
		{
			if (fhash == 10)
			{
				fprintf(out, "%s", nrstrex);
				fgets(comm, BFSZ, in);
				continue;
			}
			chash = fhash; fhash++;
			hash[chash] = constrHash();
			while ((code = readNumber(in, &n)) == True)
				insertHash(hash[chash], n);
			if (code == STOP)
				insertHash(hash[chash], n);
			if (code == NOTNUMBER)
			{
				fprintf(out, "%s", invinp);
				fgets(comm, BFSZ, in);
			}
		}
		else if (command(comm, "HashTableSearch"))
		{
			int cd = readNumber(in, &n);
			if (cd == NOTNUMBER)
			{
				fprintf(out, "%s", invinp);
				fgets(comm, BFSZ, in);
			}
			else
			{
				code = findHash(hash[chash], n, NULL);
				if (code == NDTERR)
					fprintf(out, "%s", csundef);
				else if (code == NFOUND)
					fprintf(out, "%s", notfound);
				else if (code == FOUND)
					fprintf(out, "%s", found);
				if (cd != STOP)
					fgets(comm, BFSZ, in);
			}
		}
		else if (command(comm, "TreeGoTo"))
		{
			readNumber(in, &n);	
			if (n < 0 || n > 10)
				fprintf(out, "%s", idxoobnd);
			else
				ctree = n;
		}
		else if (command(comm, "TreeRead"))
		{
			if (ftree == 10)
			{
				fprintf(out, "%s", nrstrex);
				fgets(comm, BFSZ, in);
				continue;
			}
			ctree = ftree; ftree++;
			tree[ctree] = constrTree();
			while ((code = readNumber(in, &n)) == True)
				insertTree(tree[ctree], n);
			if (code == STOP)
				insertTree(tree[ctree], n);
			if (code == NOTNUMBER)
			{
				fprintf(out, "%s", invinp);
				fgets(comm, BFSZ, in);
			}
		}
		else if (command(comm, "TreeInsert"))
		{
			if (sizeTree(tree[ctree]) == MAXSIZE)
			{
				fprintf(out, "%s", caplim);
			}
			if (readNumber(in, &n) == NOTNUMBER)
			{
				fprintf(out, "%s", invinp);
				fgets(comm, BFSZ, in);
			}
			else
			{
				if (insertTree(tree[ctree], n) == NDTERR)
					fprintf(out, "%s", csundef);
			}
		}
		else if (command(comm, "TreeRemove"))
		{
			if (readNumber(in, &n) == NOTNUMBER)
			{
				fprintf(out, "%s", invinp);
				fgets(comm, BFSZ, in);
			}
			else
			{
				code = deleteTree(tree[ctree], n);
				if (code == NDTERR)
					fprintf(out, "%s", csundef);
				if (code == NOTFND)
					fprintf(out, "%s", notfound);
			}
		}
		else if (command(comm, "TreeSearch"))
		{
			if (readNumber(in, &n) == NOTNUMBER)
			{
				fprintf(out, "%s", invinp);
				fgets(comm, BFSZ, in);
			}
			else
			{
				code = findTree(tree[ctree], n, NULL);
				if (code == NDTERR)
					fprintf(out, "%s", csundef);
				else if (code == NFOUND)
					fprintf(out, "%s", notfound);
				else if (code == FOUND)
					fprintf(out, "%s", found);
			}
		}
		else if (command(comm, "HeapGoTo"))
		{
			readNumber(in, &n);
			if (n < 0 || n > 10)
				fprintf(out, "%s", idxoobnd);
			else
				cheap = n;
		}
		else if (command(comm, "HeapRead"))
		{
			if (fheap == 10)
			{
				fprintf(out, "%s", nrstrex);
				fgets(comm, BFSZ, in);
				continue;
			}
			cheap = fheap; fheap++;
			heap[cheap] = constrHeap();
			while ((code = readNumber(in, &n)) == True)
				pushHeap(heap[cheap], n);
			if (code == STOP)
				pushHeap(heap[cheap], n);
			if (code == NOTNUMBER)
			{
				fprintf(out, "%s", invinp);
				fgets(comm, BFSZ, in);
			}
		}
		else if (command(comm, "HeapInsert"))
		{
			if (sizeHeap(heap[cheap]) == MAXSIZE)
			{
				fprintf(out, "%s", caplim);
			}
			if (readNumber(in, &n) == NOTNUMBER)
			{
				fprintf(out, "%s", invinp);
				fgets(comm, BFSZ, in);
			}
			else
			{
				if (pushHeap(heap[cheap], n) == NDTERR)
					fprintf(out, "%s", csundef);
			}
		}
		else if (command(comm, "HeapRemove"))
		{
			code = popHeap(heap[cheap], &n);
			if (code == NDTERR)
				fprintf(out, "%s", csundef);
			else if (code == EMPTYCOL)
				fprintf(out, "%s", notfound);
			else
				fprintf(out, "%d\n", n);
		}
		else
		{
			fprintf(out, "%s", invcomm);
		}
	}
	for (int i = 0; i < 10; i++)
	{
		destrHash(&hash[i]);
		destrHeap(&heap[i]);
		destrList(&list[i]);
		destrTree(&tree[i]);
		destrVec(&vec[i]);
	}
	fclose(in);	fclose(out);
	return SUCCESS;
}

int main(int argc, char** argv)
{
	char in[100] = "..\\..\\..\\in\\013.in";
	char out[100] = "..\\..\\..\\res\\013.res";
	//test(in, out);
	if (argc == 2)
	{
		if (command(argv[1], "runall"))
		{
			int t = 1;
			do {
				int nr = t;
				in[NR + 2] = out[NR + 3] = (char)(t % 10) + '0';
				t = t / 10;
				in[NR + 1] = out[NR + 2] = (char)(t % 10) + '0';
				t = t / 10;
				in[NR] = out[NR + 1] = (char)(t % 10) + '0';
				t = nr; t++;
				printf("%s\n", in);
			} while (test(in, out) == SUCCESS);
		}
		else
		{
			int t = atoi(argv[1]);
			in[NR + 2] = out[NR + 3] = (char)(t % 10) + '0';
			t = t / 10;
			in[NR + 1] = out[NR + 2] = (char)(t % 10) + '0';
			t = t / 10;
			in[NR] = out[NR + 1] = (char)(t % 10) + '0';
			printf("%s\n", in);
			test(in, out);
		}
	}
	if (argc == 3)
	{
		int f = atoi(argv[1]);
		int l = atoi(argv[2]);
		for (int i = f; i <= l; i++)
		{
			int t = i;
			in[NR + 2] = out[NR + 3] = (char)(t % 10) + '0';
			t = t / 10;
			in[NR + 1] = out[NR + 2] = (char)(t % 10) + '0';
			t = t / 10;
			in[NR] = out[NR + 1] = (char)(t % 10) + '0';
			printf("%s\n", in);
			test(in, out);
		}
	}
	return 0;
}