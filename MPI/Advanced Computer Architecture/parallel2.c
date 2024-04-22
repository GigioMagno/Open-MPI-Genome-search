#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <mpi.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include "./Libraries/utilities.h"
#include "./Libraries/hashfun.h"
#include "./Libraries/rabinkarp.h"


int main(int argc, char *argv[])
{
	
	int rank;
	int size;
	char *txt;
	char *pattern;
	MPI_Offset txtlen;
	MPI_Offset patlen;
	int isActive = 0;
	int executors;
	char *chunk;
	MPI_Offset chunklen;
	MPI_Offset offset = 0;
	MPI_Offset occurrences = 0;
	MPI_Offset total = 0;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	int flag[size];


	//If I'm the master process, then open and read the file:

	if (rank == 0)
	{

		txt = readFile(argv[1], &txtlen);
		pattern = readFile(argv[2], &patlen);
		printf("LUNGHEZZE: file: %lld ----- pattern: %lld\n", txtlen, patlen);
		//knowing the length of the text and the length of the pattern, 
		//compute the recommended number of cores that can operate on the dataset

		executors = who_is_active(flag, txtlen, patlen, size);
	}
	clock_t begin = clock();
	//Send information to the cores to let them know who can be active or not
	MPI_Bcast(&executors, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Scatter(flag, 1, MPI_INT, &isActive, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(&txtlen, 1, MPI_LONG_LONG, 0, MPI_COMM_WORLD);
	MPI_Bcast(&patlen, 1, MPI_LONG_LONG, 0, MPI_COMM_WORLD);


	if (isActive)
	{
		offset = txtlen/executors;
		//printf("rank----executors----active------offset----pattern: %d------%d-----%d------%lld------%d\n", rank, executors, isActive, offset, patlen);
		if (rank > 0)
		{
			pattern = (char *)malloc(sizeof(char)*(patlen+1));
			pattern[patlen]='\0';
		}

		//Sending data...
		if (rank == 0)
		{
			chunk = split_dataset(txt, &chunklen, txtlen, patlen, offset, executors);
			free(txt);
			//printf("%lld----%lu\n",txtlen, strlen(chunk));
			for (int i = 1; i < executors; ++i){
				MPI_Send(pattern, patlen, MPI_CHAR, i, 105, MPI_COMM_WORLD);
			}	
		} else {	//Receiving data...
			chunk = receive_dataset(offset, txtlen, patlen, &chunklen, rank, executors);
			MPI_Recv(pattern, patlen, MPI_CHAR, 0, 105, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		}
			//rabin_karp_polyHash(chunk, pattern, chunklen, patlen, &occurrences);
			//rabin_karp_loselose(chunk, pattern, chunklen, patlen, &occurrences);
			//rabin_karp_djb2(chunk, pattern, chunklen, patlen, &occurrences);
			//rabin_karp_sdbm(chunk, pattern, chunklen, patlen, &occurrences);
		//printf("My rank is %d these are my chars %c, %c, %c\n",rank, chunk[0] ,chunk[(chunklen-1)/2], chunk[chunklen-1]);
			rabin_karp2(chunk, pattern, chunklen, patlen, &occurrences);
			free(pattern);
			free(chunk);
	}

	MPI_Reduce(&occurrences, &total, 1, MPI_LONG_LONG_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	clock_t end = clock();
	
	printf("OCCURRENCES rank %d: %lld\n",rank, occurrences);


	//MPI_Finalize(); se compaiono problemi scommentare questo



	if (rank == 0)
	{
		double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
		printf("Total occurrences %lld\n", total);

		printf("time required %lf\n", time_spent);
		printf("Program executed by %d cores over %d\n", executors, size);
	}

	MPI_Finalize();

	return 0;
}

//References
//https://www.codingninjas.com/studio/library/rabin-karp-algorithm