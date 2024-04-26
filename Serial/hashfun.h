#ifndef HASHFUN_H
#define HASHFUN_H

unsigned long polyHash(char *pattern);
unsigned long djb2(char *pattern);
unsigned long sdbm(char *pattern);
unsigned long loselose(char *pattern);
unsigned long quickHash(char *pattern);
unsigned long shiftHash(int hash, int lenpat, int idx, char *txt);

#endif