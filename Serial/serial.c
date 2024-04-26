/////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//////////////////////// Main Body \\\\\\\\\\\\\\\\\\\\\\\
//////////////// Vito Giacalone  (546646) \\\\\\\\\\\\\\\\
/////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

#include <stdio.h>		
#include <stdlib.h>
#include "hashfun.h"
#include <time.h>
#include <stddef.h>

/*****PROTOTYPES*****/
char *readFile(char *filename, size_t *len);
void rabin_karp2(char *txt, char *pattern, const size_t lentxt, const size_t lenpat, long long int *occurrences);

///////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//This is a function defined as a macro. This function has parametric
//name, according to the hash function that is used.
//The hashes of the pattern and of a portion of the text are computed
//and iff the two hashes coincide, the check character by character 
//is performed.
///////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

#define RABIN_KARP_WITH_HASH(f) \
long long int rabin_karp_##f(char *txt, char *pattern, const size_t lentxt, const size_t lenpat){\
  long long int hashpat = f(pattern);\
  char *chunk = (char*)malloc(sizeof(char)*(lenpat+1));\
  long long int idxs = 0;\
	for(size_t i = 0; i <= lentxt-lenpat; i++)\
	{\
		chunk = strncpy(chunk, txt+i, sizeof(char)*lenpat);\
		chunk[lenpat]='\0';\
		if (hashpat == f(chunk))\
		{\
			if (strcmp(pattern, chunk)==0)\
			{\
				idxs++;\
			}\
		}\
	}\
	return idxs;\
  free(chunk);\
}
RABIN_KARP_WITH_HASH(polyHash)
RABIN_KARP_WITH_HASH(djb2)
RABIN_KARP_WITH_HASH(sdbm)
RABIN_KARP_WITH_HASH(loselose)

///////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//This function computes the length of the file and read it.
///////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

char *readFile(char *filename, size_t *len) {
    
    FILE *f = fopen(filename, "r");
    fseeko(f, 0, SEEK_END);
    *len = ftello(f);
    rewind(f);
    char *txt = (char *)malloc(*len + 1);
    //null_check(txt);

    if (fread(txt, 1, *len, f) != *len) {
        fprintf(stderr, "Input reading error\n");
        free(txt);
        fclose(f);
        return NULL;
    }

    txt[*len] = '\0';
    fclose(f);
    return txt;
}

///////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//The hashes of the pattern and of a portion of the text are computed
//and iff the two hashes coincide, the check character by character 
//is performed.
//The total number of occurrences is returned
///////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

void rabin_karp2(char *txt, char *pattern, const size_t lentxt, const size_t lenpat, long long int *occurrences){

	//SOME VARIABLES...
  size_t i,j;                      
  long long int pat_hash = 0;           
  long long int txt_hash = 0;
  long long int h = 1;
  *occurrences = 0;


	//COMPUTES H = P^(LENPAT -1) MODULO M 
  for (i = 0; i < lenpat - 1; i++)
  		h = (h * P) % M;

  //COMPUTE THE HASHES FOR PATTERN AND FIRST WINDOW OF THE TEXT
  for(i = 0; i < lenpat; i++){
    	pat_hash = (P * pat_hash + *(pattern + i)) % M;
      txt_hash = (P * txt_hash + *(txt + i)) % M;
    }

  //FOR EACH SLIDING WINDOW OF THE TEXT OF THE DIMENSION OF THE PATTERN
  for(i = 0; i <= lentxt - lenpat; i++){

  	 //CHECK IF THE HASHES ARE THE SAME
     if(pat_hash == txt_hash){

     		//IF THE HASHES ARE THE SAME THEN 
      	for(j = 0; j < lenpat; j++){

      		//CHECK CHARACTER BY CHARACTER
          if(*(txt + i + j) != *(pattern + j)){

            //IF THE PATTERN AND THE WINDOW ARE DIFFERENT THEN EXIT THE LOOP
            break;

          }


        }

        //IF THE PATTERN AND THE WINDOW ARE THE SAME
        if(j == lenpat){
   	       
   	      //printf("Pattern found at index %d\n", rank == 0 ? i : i+(txt_len-(pat_len-1)+rest)-pat_len+1+((rank-1)*(txt_len-pat_len+1)));
          
          //INCREMENT THE NUMBER OF OCCURRENCES
          (*occurrences)++;
        }
      }

    
      //UPDATE THE HASH
      if(i < lentxt - lenpat){
        
        //UPDATE THE HASH REMOVING THE FIRST ONE CHARACTER AND ADDING THE FIRST NEXT CHARACTER OF THE TEXT
        txt_hash = (P * (txt_hash - *(txt + i) * h) + *(txt + i + lenpat)) % M;

        //IF THE HASH IS NEGATIVE
        if(txt_hash < 0)
        	
        	//NORMALIZE IT
          txt_hash = txt_hash + M;
      }
    }
}

///////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
/////////////////////////// Main function \\\\\\\\\\\\\\\\\\\\\\\\\\\\
///////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

int main(int argc, char const *argv[])
{
	clock_t begin = clock();
	size_t txtlen;
	size_t patlen;
	if (argc != 3)
	{
		printf("Errore, inserire nome file\n");
		exit(1);
	}
	long long int occurrences = 0;
	char *pattern = readFile((char*)argv[2], &patlen);
	char *txt = readFile((char*)argv[1], &txtlen);
	//occurrences = rabin_karp_loselose(txt, pattern, txtlen, patlen);
	//occurrences = rabin_karp_djb2(txt, pattern, txtlen, patlen);
	//occurrences = rabin_karp_polyHash(txt, pattern, txtlen, patlen);
	//occurrences = rabin_karp_sdbm(txt, pattern, txtlen, patlen);
	rabin_karp2(txt, pattern, txtlen, patlen, &occurrences);
	printf("OCCORRENZE TROVATE:%lld\n", occurrences);


	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("%.5f\n", time_spent);


	return 0;
}
//END

// http://www.cse.yorku.ca/~oz/hash.html funzioni di hashing semplici per stringhe
// https://stackoverflow.com/questions/1579721/why-are-5381-and-33-so-important-in-the-djb2-algorithm
//https://cp-algorithms.com/string/string-hashing.html	For simple (but not useful) hash function
