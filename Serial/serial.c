#include <stdio.h>		
#include <stdlib.h>		//MALLOC, REALLOC
#include <string.h>		//STRCMP, STRLEN
#include <math.h>		//POW
#include <limits.h>
#include "hashfun.h"
#include <time.h>
//https://cp-algorithms.com/string/string-hashing.html	For simple (but not useful) hash function


/*****PROTOTYPES*****/
//START
char* readFile(char *path);
int *rabin_karp(char *txt, char *pattern, int *occurrences, unsigned long (*hash)(char *str));
int *rabin_karp2(char *txt, char *pattern, int *occurrences, unsigned long (*hash)(char *str), unsigned long (*shiftHash)(int hash, int lenpat, int idx, char *txt));
//END


/*****READ FILE FUNCTION*****/
//START
char* readFile(char *path){

	//CREATE A FILE POINTER
	FILE *f = fopen(path, "r");

	//IF THE PATH IS WRONG OR ISN'T POSSIBLE READ THE FILE THROW AN ERROR AND STOP THE PROGRAM
	if (!f)
	{
		printf("Errore apertura file\n");
		exit(1);
	}

	//CREATE A CHAR POINTER WHICH WILL POINT TO THE MEMORY REGION THAT CONTAINS THE READ FILE
	char *txt = (char *) malloc(sizeof(char)*INT_MAX);

	//LET'S READ THE FILE AND STORE IT INTO A STRING
	fgets(txt, INT_MAX, f);

	//RESIZE THE ALLOCATED MEMORY
	txt = realloc(txt, strlen(txt)*sizeof(char));

	fclose(f);
	return txt;

}
//END


// http://www.cse.yorku.ca/~oz/hash.html funzioni di hashing semplici per stringhe



// https://stackoverflow.com/questions/1579721/why-are-5381-and-33-so-important-in-the-djb2-algorithm



// rabin karp with djb2 hash function
int *rabin_karp(char *txt, char *pattern, int *occurrences, unsigned long (*hash)(char *str)){

	int lentxt = strlen(txt);
	int lenpat = strlen(pattern);
	unsigned long hashpat = hash(pattern);
	//CREATE A CHUNK WITH THE DIMENSION OF THE PATTERN
	char *chunk = (char*)malloc(sizeof(char)*lenpat);
	int idxs = 0;
	int *idx = (int*)malloc(sizeof(int)*lentxt);

	for (int i = 0; i <= lentxt-lenpat; i++)
	{
		for (int j = 0; j < lenpat; j++)
		{
				chunk[j] = txt[i+j];
		}
		if (hashpat == hash(chunk))
		{
				
			if (strcmp(pattern, chunk)==0)
			{
				//SAVE THE INDEX OF THE OCCURRENCE AND INCREMENT THE NUMBER OF OCCURRENCES
				idx[idxs] = i;
				idxs++;
			}
		}
	}

	//RETURNS THE NUMBER OF OCCURRENCES
	*occurrences = idxs;
	//Returns the vector with the indexes of the first element of occurrences
	return realloc(idx, idxs*sizeof(int));
}


int *rabin_karp2(char *txt, char *pattern, int *occurrences, unsigned long (*hash)(char *str), unsigned long (*shiftHash)(int hash, int lenpat, int idx, char *txt)){

	int lentxt = strlen(txt);
	int lenpat = strlen(pattern);
	unsigned long hashpat = hash(pattern);
	//CREATE A CHUNK WITH THE DIMENSION OF THE PATTERN
	char *chunk = (char*)malloc(sizeof(char)*lenpat);
	int idxs = 0;
	int *idx = (int*)malloc(sizeof(int)*lentxt);

	int hashtxt = 0;
	int flag = 0;


	for (int j = 0; j < lenpat; j++)
	{
			chunk[j] = txt[j];
	}
	hashtxt = hash(chunk);

	for (int i = 0; i < lentxt-lenpat; i++)
	{
		flag = 0;

		if (hashpat == hashtxt)
		{
			
			for (int j = 0; j < lenpat; ++j)
				{
					if (txt[i+j] != pattern[j])
						{
							flag = 1;
							break;
						}
				}

			if (flag == 0)
			{
				//SAVE THE INDEX OF THE OCCURRENCE AND INCREMENT THE NUMBER OF OCCURRENCES
				idx[idxs] = i;
				idxs++;
			}
			
		} else {

			hashtxt = shiftHash(hashtxt, lenpat, i, txt);

		}



	}

	//RETURNS THE NUMBER OF OCCURRENCES
	*occurrences = idxs;
	//Returns the vector with the indexes of the first element of occurrences
	return realloc(idx, idxs*sizeof(int));
}


/*****START-MAIN*****/
int main(int argc, char const *argv[])
{

	clock_t begin = clock();

	if (argc == 1)
	{
		printf("Errore, inserire nome file\n");
		exit(1);
	}
	char *txt;
	int occurrences;
	char *pattern = readFile((char*)argv[2]);
	txt = readFile((char*)argv[1]);
	int *idxs = rabin_karp(txt, pattern, &occurrences,polyHash);
	//int *idxs = rabin_karp2(txt, pattern, &occurrences, quickHash, shiftHash);
	printf("OCCORRENZE TROVATE:%d\n", occurrences);
	for (int i = 0; i < occurrences; i++)
	{
		for (int j = 0; j < strlen(pattern); j++)
		{
			printf("%c", txt[idxs[i]+j]);
		}
		printf("\n");
	}


	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("%.5f\n", time_spent);


	return 0;
}
//END