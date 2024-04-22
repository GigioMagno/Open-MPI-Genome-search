# Open-MPI-Genome-search
Advanced computer architecture project
## How to compile
 > cd MPI/Advanced Computer Architecture/Libraries/ \n
 > gcc -c *.c \
 > cd .. \n
 > mpicc -o parallel parallel2.c -L./Libraries -lhashfun.o -lrabinkarp.o -lutilities.o \n
 > mpirun parallel TestGenome.txt pattern.txt \n
