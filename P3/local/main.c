/*
 * Samuel Carroll
 * CPTS 411
 * HW 2
 * October 3rd, 2019
 *
 * 
 */


#include <stdio.h>
#include <mpi.h> 
#include <assert.h>
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define SUM 0
#define MAX 1

void serialOutput(int seed, int A, int B, int P, int n);

int main(int argc, char *argv[])
{
    int rank,p;
    int seed, A, B, n, Prime;
    // Init and setup calls
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&p);

    assert(argc == 6);

    seed = atoi(argv[1]);
    A = atoi(argv[2]);
    B = atoi(argv[3]);
    Prime = atoi(argv[4]);
    n = atoi(argv[5]);

    assert(n > (2 * Prime));

    printf("seed = %d\n", seed);
    printf("A = %d\n", A);
    printf("B = %d\n", B);
    printf("P = %d\n", Prime);
    printf("n = %d\n", n);

    printf("my rank=%d\n",rank);
    if(rank == 0)
    {
        printf("Number of processes =%d\n", p);
        serialOutput(seed, A, B, Prime, n);
    }

    // assert((p & (p - 1)) == 0 && (p != 0));



    MPI_Finalize();
}

void serialOutput(int seed, int A, int B, int P, int n)
{
    int i = 0, x_i, x_iM1 = seed;
    for(i = 1; i < n; i++)
    {
        x_i = (A * x_iM1 + B) % P;
        printf("x_%d = %d\n", i, x_i);
        x_iM1 = x_i;
    }
}