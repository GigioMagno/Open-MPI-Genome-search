/////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
////////////////// Hashfun Library Body \\\\\\\\\\\\\\\\\\
//////////////// Vito Giacalone  (546646) \\\\\\\\\\\\\\\\
/////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

#include "hashfun.h"

///////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//The polyhash function computes the polynomial expansion of a string.
//Each character is weighted with its own decimal ASCII value and,
//according to its position inside the string, is multiplied by the 
//term P^(position).
///////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

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

///////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//The djb2 hashfunction computes the hash by adding the actual value
//of the hash multiplied by 33 and the decimal value of the ASCII
//representation of each character
///////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

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

///////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//The sdbm function computes the hash by adding the following elements
//64*hash + 65536*hash - hash + ASCII value of each character
///////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

long long int sdbm(char *pattern){

	long long int hash = 0;
	long long int c;
	while((c = *pattern++)){
		hash = c + (hash << 6) + (hash << 16) - hash;
	}

	return hash;
}

///////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//The loselose hash function it's very very simple and creates the 
//hash adding the ASCII value of each letter of the considered string
///////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

long long int loselose(char *pattern){

	long long int hash = 0;
	long long int c;
	while((c = *pattern++))
		hash += c;

	return hash;
}
