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
void matrixOutput(int seed, int A, int B, int P, int n);
void matrixMul(int Left[2][2], int Right[2][2], int Prime);

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
        matrixOutput(seed, A, B, Prime, n);
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


void matrixOutput(int seed, int A, int B, int P, int n)
{
    int M[2][2], **ret, M_next[2][2];
    int x_i, x_iM1 = seed;
    int i = 1;
    M[0][0] = A;
    M[0][1] = B;
    M[1][0] = 0;
    M[1][1] = 1;
    M_next[0][0] = A;
    M_next[0][1] = B;
    M_next[1][0] = 0;
    M_next[1][1] = 1;
    for(i = 1; i < n; i++)
    {
        matrixMul(M, M_next, P);
        printf("%d %d\n", M_next[0][0], M_next[0][1]);
    }
}


void matrixMul(int Left[2][2], int Right[2][2], int Prime)
{
    int g = 0, j = 0, k = 0, sum = 0;
    int ret[2][2];
    for(g = 0; g < 2; g++)
    {
        for(j = 0; j < 2; j++)
        {
            for(k = 0; k < 2; k++)
            {
               // printf("%d\n", Right[g][k]);
                sum = sum + Left[g][k] * Right[k][j];
            }
           ret[g][j] = sum % Prime;
           sum = 0;
        }
    }
    for(g = 0; g < 2; g++)
    {
        for(j = 0; j < 2; j++)
        {
            Right[g][j] = ret[g][j];
        }
    }
   // return ret;
}