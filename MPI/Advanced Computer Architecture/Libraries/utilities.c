/////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
///////////////// Utilities Library Body \\\\\\\\\\\\\\\\\
//////////////// Vito Giacalone  (546646) \\\\\\\\\\\\\\\\
/////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

#include "utilities.h"

///////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//Check if a pointer is null. This function has been created to avoid 
//to repeat many times the check of the pointer inside the code.								 
///////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

void null_check(void *ptr){
	if (!ptr)
	{
		printf("Internal error. Please, try again\n");
		exit(1);
	}
}

///////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//Check how many cores can be active.
//The splitting of the text is done dividing the length of the text by 
//the length of the pattern. If this division is greater than the 
//available number of cores, the maximum number of available cores is 
//used (active cores); else the quotient of the previous division is 
//the number of active cores.
//The vector flag, is like a bitmap used to notify to the cores who 
//can be active or not.
///////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

size_t who_is_active(int *flag, size_t txtlen, size_t patlen, int cores){

	size_t actives = txtlen/patlen;
	if (actives > cores)
	{
		actives = cores;
	}

	for (int i = 0; i < cores; ++i)
	{
		if (i < actives)
		{
			flag[i] = 1;
		} else flag[i] = 0;
	}

	return actives;
}

///////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//This function computes the length of the file and read it.
//I used ftello because the return value is of type off_t (64 bit) -> 
//->it's possible to read file of size > 2GB.
//fseek and ftell are able to handle 32 bits values (at most 2GB)
///////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

char *readFile(char *filename, size_t *len) {
    
    FILE *f = fopen(filename, "r");
    null_check(f);
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
//This function split the text (received as input) into chunks among 
//the active cores.
//The cores with rank from 0 to n-2 receive a chunk of length offset
//and the core n-1 receive the remaining part of the text.
//The function takes into account also the overlapping occurrences
//of the pattern, simply copying also "patlen" extra characters in
//the chunk.
///////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

char *split_dataset(char *txt, size_t *chunklen, size_t txtlen, size_t patlen, size_t offset, int executors){

	char *chunk = (char *)malloc(sizeof(char) * (offset +1));
	null_check(chunk);
	strlcpy(chunk, txt, offset+1);
	chunk[offset] = '\0';
	*chunklen = offset;

		for (int i = 1; i < executors; ++i)
		{
			if (i <= executors-2)
			{
					MPI_Send(txt+(offset*i)-patlen+1, offset + patlen-1, MPI_CHAR, i, 100, MPI_COMM_WORLD);
			} else {
					MPI_Send(txt+(offset*i)-patlen+1, txtlen - offset*i + patlen -1, MPI_CHAR, i, 101, MPI_COMM_WORLD);
			}
		}
	return chunk;
}

///////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//This function allows to the core who invoke it, to receive its
//chunk of text to analyze.
///////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

char *receive_dataset(size_t offset, size_t txtlen, size_t patlen, size_t *chunklen, int rank, int executors){

	if (rank < executors-1)
	{
		*chunklen = offset + patlen -1;
		char *chunk = (char *)malloc(sizeof(char)*(*chunklen +1));
		null_check(chunk);
		chunk[*chunklen]='\0';
		MPI_Recv(chunk, *chunklen, MPI_CHAR, 0, 100, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		return chunk;
	}

	if (rank == executors-1)
	{
		*chunklen = txtlen - rank*offset + patlen -1;
		char *chunk = (char *)malloc(sizeof(char)*(*chunklen + 1));
		null_check(chunk);
		chunk[*chunklen] = '\0';
		MPI_Recv(chunk, *chunklen, MPI_CHAR, 0, 101, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		return chunk;
	}
	return NULL;
}