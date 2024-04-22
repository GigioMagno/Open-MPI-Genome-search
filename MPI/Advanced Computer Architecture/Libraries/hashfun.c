#include "hashfun.h"
#include <string.h>
#include <math.h>
#include <limits.h>
#define P 5
#define M 101


// COMPUTES A POLYNOMIAL HASH AND REDUCE IT MODULO UINT_MAX	
long long int polyHash(char *pattern){

	long long int hash = 0;
	long long int len = strlen(pattern);
	if (len!=0)
	{
		for (long long int i = 0; i < len; i++)
		{
			hash+=pattern[i]*pow(P,i);
		}
		hash = hash%UINT_MAX;
	}
return hash;

}


//SOME DIFFERENT HASH FUNCTIONS FOR A COMPARISON...
long long int djb2(char *pattern){

	long long int hash = 5381;
	long long int c;
	//versione con while più efficiente perchè non calcolo strlen
	while ((c = *pattern++))
	{
		hash = ((hash << 5) + hash) + c;
	}

	return hash;
}

long long int sdbm(char *pattern){

	long long int hash = 0;
	long long int c;
	while((c = *pattern++)){
		hash = c + (hash << 6) + (hash << 16) - hash;
	}

	return hash;
}

long long int loselose(char *pattern){

	long long int hash = 0;
	long long int c;
	while((c = *pattern++))
		hash += c;

	return hash;
}