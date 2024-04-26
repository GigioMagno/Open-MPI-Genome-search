/////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//////////////////////// Main Body \\\\\\\\\\\\\\\\\\\\\\\
//////////////// Vito Giacalone  (546646) \\\\\\\\\\\\\\\\
/////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <unistd.h>
#include <time.h>
#include <stddef.h>
#include "./Libraries/utilities.h"
#include "./Libraries/hashfun.h"
#include "./Libraries/rabinkarp.h"

///////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
/////////////////////////// Main function \\\\\\\\\\\\\\\\\\\\\\\\\\\\
///////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

int main(int argc, char *argv[])
{
	
//////////////////////// Variables definition \\\\\\\\\\\\\\\\\\\\\\\\

int rank;
int size;
int isActive = 0;
int executors;
char *txt;
char *pattern;
char *chunk;
size_t txtlen;
size_t patlen;
size_t chunklen;
size_t offset = 0;
long long int occurrences = 0;
long long int total = 0;

////////////////////// MPI layer initializzation \\\\\\\\\\\\\\\\\\\\\

MPI_Init(&argc, &argv);
MPI_Comm_rank(MPI_COMM_WORLD, &rank); 								//Get rank
MPI_Comm_size(MPI_COMM_WORLD, &size); 								//Get size of the communicator

int flag[size]; //Vector of active cores

if (rank == 0)
{
	txt = readFile(argv[1], &txtlen);							//Read text
	pattern = readFile(argv[2], &patlen);							//Read pattern
	null_check(txt);									//Check if the pointer to the text is not null
	null_check(pattern);									//Check if the pointer to the pattern is not null		
	executors = who_is_active(flag, txtlen, patlen, size); 					//Compute the number of active cores
}
	clock_t begin = clock(); //start the execution time measurement
	MPI_Bcast(&executors, 1, MPI_INT, 0, MPI_COMM_WORLD);					//Send to each core the number of cores that will perform the search
	MPI_Scatter(flag, 1, MPI_INT, &isActive, 1, MPI_INT, 0, MPI_COMM_WORLD);		//Send to each core a value that specify if the core will be and executor or not
	MPI_Bcast(&txtlen, 1, MPI_LONG_LONG, 0, MPI_COMM_WORLD);				//Send to each core the length of the text
	MPI_Bcast(&patlen, 1, MPI_LONG_LONG, 0, MPI_COMM_WORLD);				//Send to each core the length of the pattern

if (isActive) {
	offset = txtlen/executors;								//Compute the portion of text to analyze
	if (rank == 0) {
		chunk = split_dataset(txt, &chunklen, txtlen, patlen, offset, executors); 	//Sending a chunk of text to each core
		null_check(chunk);
		free(txt);
		for (int i = 1; i < executors; ++i){
			MPI_Send(pattern, patlen, MPI_CHAR, i, 105, MPI_COMM_WORLD); 		//Sending the pattern to all the cores
		}	
	} else {
		pattern = (char *)malloc(sizeof(char)*(patlen+1));
		null_check(pattern);
		pattern[patlen]='\0';
		chunk = receive_dataset(offset, txtlen, patlen, &chunklen, rank, executors); 	//The slaves receive the corresponding chunk of text
		null_check(chunk);
		MPI_Recv(pattern, patlen, MPI_CHAR, 0, 105, MPI_COMM_WORLD, MPI_STATUS_IGNORE); //The slaves receive the pattern
		}

		////////////////////// Rabin Karp algorithm with different hash functions \\\\\\\\\\\\\\\\\\\\\

		//occurrences = rabin_karp_polyHash(chunk, pattern, chunklen, patlen);
		//occurrences = rabin_karp_loselose(chunk, pattern, chunklen, patlen);
		//occurrences = rabin_karp_djb2(chunk, pattern, chunklen, patlen);
		//occurrences = rabin_karp_sdbm(chunk, pattern, chunklen, patlen);
		rabin_karp2(chunk, pattern, chunklen, patlen, &occurrences);

		////////////////////// Free the memory \\\\\\\\\\\\\\\\\\\\\
	
		free(pattern); //free the pattern pointer
		free(chunk); //free the pointer to the chunk
	}

printf("OCCURRENCES rank %d: %lld\n",rank, occurrences);
	
////////////////////// Gather the results from other processes \\\\\\\\\\\\\\\\\\\\\

MPI_Reduce(&occurrences, &total, 1, MPI_LONG_LONG_INT, MPI_SUM, 0, MPI_COMM_WORLD);		//The master process collects all the occurrences found by the slaves
clock_t end = clock(); 										//Stop the execution time measurement

if (rank == 0) {
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Total occurrences %lld\n", total);
	printf("Time required %lf\n", time_spent);
	printf("Program executed by %d cores over %d\n", executors, size);
}

////////////////////// MPI layer Finalization \\\\\\\\\\\\\\\\\\\\\
	
MPI_Finalize();	

return 0;
}

//References
//https://www.codingninjas.com/studio/library/rabin-karp-algorithm
