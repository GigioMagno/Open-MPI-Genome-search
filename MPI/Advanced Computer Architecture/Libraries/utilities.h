/////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//////////////////// Utilities Header \\\\\\\\\\\\\\\\\\\\
//////////////// Vito Giacalone  (546646) \\\\\\\\\\\\\\\\
/////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

#ifndef UTIL_RABINKARP
#define UTIL_RABINKARP

#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>

size_t who_is_active(int *flag, size_t txtlen, size_t patlen, int cores);
char *readFile(char *argv, size_t *len);
char *split_dataset(char *txt, size_t *chunklen, size_t txtlen, size_t patlen, size_t offset, int executors);
char *receive_dataset(size_t offset, size_t txtlen, size_t patlen, size_t *chunklen, int rank, int executors);
void null_check(void *ptr);

#endif
