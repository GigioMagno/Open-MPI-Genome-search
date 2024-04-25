#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>
#include "hashfun.h"
#define P 5
#define M 101


#define RABIN_KARP_WITH_HASH(f) \
void rabin_karp_##f(char *txt, char *pattern, const long long int lentxt, const long long int lenpat, long long int *occurrences){\
  long long int hashpat = f(pattern);\
	char *chunk = (char*)malloc(sizeof(char)*(lenpat+1));\
  long long int idxs = 0;\
	for(long long int i = 0; i <= lentxt-lenpat; i++)\
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
	*occurrences = idxs;\
  free(chunk);\
} 

RABIN_KARP_WITH_HASH(polyHash)
RABIN_KARP_WITH_HASH(djb2)
RABIN_KARP_WITH_HASH(sdbm)
RABIN_KARP_WITH_HASH(loselose)


void rabin_karp2(char *txt, char *pattern, const long long int lentxt, const long long int lenpat, long long int *occurrences){

	//SOME VARIABLES...
  long long int i,j;                      
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
