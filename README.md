# Open-MPI-Genome-search
Advanced computer architecture project

# How to compile and run the program
* ```cd MPI/Advanced Computer Architecture/Libraries/```
* ```gcc -c \*.c```
* ```cd ..```
* ```mpicc -o parallel parallel2.c -L./Libraries -lhashfun.o -lrabinkarp.o -lutilities.o```
* ```mpirun parallel TestGenome.txt pattern.txt```

# Structure of the code
The files are organized as follow:
* Comment (above the function body) -> brief description on how the function works
* Body of the function

# Future implementation
A possible future implementation can be the implementation of a swap algorithm to handle files that are bigger than the size of the RAM.
The actual version handle file of size $\leq$ RAM_SIZE
