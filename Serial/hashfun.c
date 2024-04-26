#include "hashfun.h"
#include <string.h>
#include <math.h>
#include <limits.h>
#define p 5
#define m 197488152910387043

unsigned long polyHash(char *pattern){

	int hash = 0;
	int len = strlen(pattern);
	if (len!=0)
	{
		for (int i = 0; i < len; i++)
		{
			hash+=pattern[i]*pow(p,i);
		}
		hash = hash%UINT_MAX;
	}
return hash;

}


unsigned long quickHash(char *pattern){

	int hash = 0;
	int len = strlen(pattern);
	if (len!=0)
	{
		for (int i = 0; i < len; i++)
		{
			hash+=pattern[i]*pow(p,len - i - 1);
		}
		hash = hash%m;
	}
return hash;

}


unsigned long shiftHash(int hash, int lenpat, int idx, char *txt){

	return ((hash - (txt[idx]*(int)pow(p,lenpat -1))%m)*p + txt[idx+lenpat]);

}


unsigned long djb2(char *pattern){

	unsigned long hash = 5381;
	int c;
	//versione con while più efficiente perchè non calcolo strlen
	while ((c = *pattern++))
	{
		hash = ((hash << 5) + hash) + c;
	}

	return hash;
}

unsigned long sdbm(char *pattern){

	unsigned long hash = 0;
	int c;
	while((c = *pattern++)){
		hash = c + (hash << 6) + (hash << 16) - hash;
	}

	return hash;
}

unsigned long loselose(char *pattern){

	unsigned long hash = 0;
	int c;
	while((c = *pattern++))
		hash += c;

	return hash;
}

