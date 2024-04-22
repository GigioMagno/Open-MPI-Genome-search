#ifndef HASHFUN_H
#define HASHFUN_H

long long int polyHash(char *pattern);
long long int djb2(char *pattern);
long long int sdbm(char *pattern);
long long int loselose(char *pattern);

#endif