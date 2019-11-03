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

typedef struct MatArray
{
    int M[2][2];
} MatArr;

void serialOutput(int seed, int A, int B, int P, int n);
void matrixOutput(int seed, int A, int B, int P, int n);
void matrixMul(int Left[2][2], int Right[2][2], int PB[2][2], int P);
void copymatrix(int src[2][2], int dest[2][2]);
void ParallelOutput(int seed, int A, int B, int P, int nstart, int nsize, int rank);

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

    // printf("seed = %d\n", seed);
    // printf("A = %d\n", A);
    // printf("B = %d\n", B);
    // printf("P = %d\n", Prime);
    // printf("n = %d\n", n);

    // printf("my rank=%d\n",rank);

    int offset = n % p;

    if(rank == 0)
    {
        printf("Number of processes =%d\n", p);
        ParallelOutput(seed, A, B, Prime, (rank * (n/p)), (n/p) + offset, rank);
        //serialOutput(seed, A, B, Prime, n);
        //matrixOutput(seed, A, B, Prime, n);
    }
    else
        ParallelOutput(seed, A, B, Prime, (rank * (n/p)) + offset, (n/p), rank);

    // assert((p & (p - 1)) == 0 && (p != 0));



    MPI_Finalize();
}

void ParallelOutput(int seed, int A, int B, int P, int nstart, int nsize, int rank)
{
    MatArr *x_loc = (MatArr*)malloc(sizeof(MatArr) * nsize);
    int M_naught[2][2], M_loc[2][2];
    int i = 0;
    M_naught[0][0] = 1;
    M_naught[0][1] = 0;
    M_naught[1][0] = 0;
    M_naught[1][1] = 1;
    copymatrix(M_naught, M_loc);
    for(i = 0; i < nsize; i++)
    {
        x_loc[i].M[0][0] = A;
        x_loc[i].M[0][1] = B;
        x_loc[i].M[1][0] = 0;
        x_loc[i].M[1][1] = 1;
        matrixMul(M_loc, x_loc[i].M, M_loc, P);
    }
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
    int M[2][2], **ret, M_next[2][2], x_iMat[2][2];
    int x_0Mat[2][2];
    int i = 1;
    M[0][0] = A;
    M[0][1] = B;
    M[1][0] = 0;
    M[1][1] = 1;
    x_0Mat[0][0] = seed;
    x_0Mat[1][0] = 1;
    x_0Mat[0][1] = 0;
    x_0Mat[1][1] = 0;
    copymatrix(M, M_next);
    printf("%d %d %d %d\n", M[0][0], M[0][1], M[1][0], M[1][1]);
    for(i = 1; i < n; i++)
    {
        matrixMul(x_0Mat, M_next, x_iMat, P);
        printf("x_%d = %d\n", i, x_iMat[0][0]);
        matrixMul(M_next, M, M_next, P);
    }
}

void copymatrix(int src[2][2], int dest[2][2])
{
    int i = 0, j = 0;
    for(i = 0; i < 2; i++)
    {
        for(j = 0; j < 2; j++)
        {
            dest[i][j] = src[i][j];
        }
    }
}

void matrixMul(int Left[2][2], int Right[2][2], int PB[2][2], int P)
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
               sum = sum + Left[k][g] * Right[j][k];
            }
            ret[j][g] = sum % P;
            sum = 0;
        }
    }
    for(g = 0; g < 2; g++)
    {
        for(j = 0; j < 2; j++)
        {
            PB[g][j] = ret[g][j];
        }
    }
   // return ret;
}