/////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
///////////////////// Hashfun Header \\\\\\\\\\\\\\\\\\\\\
//////////////// Vito Giacalone  (546646) \\\\\\\\\\\\\\\\
/////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

#ifndef HASHFUN_H
#define HASHFUN_H

#include "hashfun.h"
#include <string.h>
#include <math.h>
#include <limits.h>
#include "utilities.h"
#define P 5
#define M 101

long long int polyHash(char *pattern);
long long int djb2(char *pattern);
long long int sdbm(char *pattern);
long long int loselose(char *pattern);

#endif