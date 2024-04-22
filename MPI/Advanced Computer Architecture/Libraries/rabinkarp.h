#ifndef RABIN_K
#define RABIN_K

void rabin_karp2(char *txt, char *pattern, const long long int lentxt, const long long int lenpat, long long int *occurrences);
void rabin_karp_polyHash(char *txt, char *pattern, const long long int lentxt, const long long int lenpat, long long int *occurrences);
void rabin_karp_loselose(char *txt, char *pattern, const long long int lentxt, const long long int lenpat, long long int *occurrences);
void rabin_karp_djb2(char *txt, char *pattern, const long long int lentxt, const long long int lenpat, long long int *occurrences);
void rabin_karp_sdbm(char *txt, char *pattern, const long long int lentxt, const long long int lenpat, long long int *occurrences);

#endif