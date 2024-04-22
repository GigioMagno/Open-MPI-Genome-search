#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utilities.h"

int who_is_active(int *flag, long long int txtlen, long long int patlen, int cores){
	
	long long int actives = txtlen/patlen;

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


char *readFile(char *argv, long long int *len){

	//stesso codice seriale
		FILE *f = fopen(&argv[0], "r");
		fseek(f, 0L, SEEK_END);
		*len = ftell(f);
		rewind(f);
		char *txt = (char *)malloc(sizeof(char)*(*len +1));
		fgets(txt, *len +1, f);
		txt[*len] = '\0';
		fclose(f);
		return txt;
}



char *split_dataset(char *txt, long long int *chunklen, long long int txtlen, long long int patlen, MPI_Offset offset, int executors){

	char *chunk = (char *)malloc(sizeof(char) * (offset +1));

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


char *receive_dataset(MPI_Offset offset, long long int txtlen, long long int patlen, long long int *chunklen, int rank, int executors){

	if (rank < executors-1)
	{
		*chunklen = offset + patlen -1;
		char *chunk = (char *)malloc(sizeof(char)*(*chunklen +1));
		chunk[*chunklen]='\0';
		MPI_Recv(chunk, *chunklen, MPI_CHAR, 0, 100, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		return chunk;
	}

	if (rank == executors-1)
	{
		//printf("da ricevere ultimo %llu\n", txtlen-rank*offset +1);
		*chunklen = txtlen - rank*offset + patlen -1;
		char *chunk = (char *)malloc(sizeof(char)*(*chunklen + 1));
		chunk[*chunklen] = '\0';
		MPI_Recv(chunk, *chunklen, MPI_CHAR, 0, 101, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		return chunk;
	}
	return NULL;
}