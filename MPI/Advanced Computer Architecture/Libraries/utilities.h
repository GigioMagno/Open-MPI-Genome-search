#ifndef UTIL_RABINKARP
#define UTIL_RABINKARP

int who_is_active(int *flag, long long int txtlen, long long int patlen, int cores);
char *readFile(char *argv, long long int *len);
char *split_dataset(char *txt, long long int *chunklen, long long int txtlen, long long int patlen, MPI_Offset offset, int executors);
char *receive_dataset(MPI_Offset offset, long long int txtlen, long long int patlen, long long int *chunklen, int rank, int executors);

#endif
