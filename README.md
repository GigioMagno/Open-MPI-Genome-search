# Open-MPI-Genome-search
Advanced computer architecture project
## How to compile and run the program
 * **cd MPI/Advanced Computer Architecture/Libraries/**
 * **gcc -c *.c**
 * **cd ..**
 * **mpicc -o parallel parallel2.c -L./Libraries -lhashfun.o -lrabinkarp.o -lutilities.o**
 * **mpirun parallel TestGenome.txt pattern.txt**
