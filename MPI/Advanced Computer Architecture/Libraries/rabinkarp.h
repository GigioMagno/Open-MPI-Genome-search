/////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//////////////////// Rabinkarp Header \\\\\\\\\\\\\\\\\\\\
//////////////// Vito Giacalone  (546646) \\\\\\\\\\\\\\\\
/////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

#ifndef RABIN_K
#define RABIN_K

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>
#include "hashfun.h"
#include <stddef.h>
#include "utilities.h"
#define P 5
#define M 101

void rabin_karp2(char *txt, char *pattern, size_t lentxt, size_t lenpat, long long int *occurrences);
long long int rabin_karp_polyHash(char *txt, char *pattern, size_t lentxt, size_t lenpat);
long long int rabin_karp_loselose(char *txt, char *pattern, size_t lentxt, size_t lenpat);
long long int rabin_karp_djb2(char *txt, char *pattern, size_t lentxt, size_t lenpat);
long long int rabin_karp_sdbm(char *txt, char *pattern, size_t lentxt, size_t lenpat);

#endif