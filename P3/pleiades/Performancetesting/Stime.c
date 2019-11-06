/*
 * Samuel Carroll
 * CPTS 411
 * HW 3
 * November 5th, 2019
 * (Updated Due date, November 7th, 2019)
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

int logfunc(int log);
void matrixOutputPar(int seed, int A, int B, int Aoff, int Boff, int P, int n, int rank);
void parallelPrefix(int M_loc[2][2], int p, int rank, int Prime, int A, int B);
void serialOutput(int seed, int A, int B, int P, int n);
void matrixOutput(int seed, int A, int B, int P, int n);
void matrixMul(int Left[2][2], int Right[2][2], int PB[2][2], int P);
void copymatrix(int src[2][2], int dest[2][2]);
void ParallelOutput(int seed, int A, int B, int P, int nstart, int nsize, int rank, int p);

int main(int argc, char *argv[])
{
    int rank,p;
    int seed, A, B, n, Prime, i = 0;
    double sum = 0, average = 0, tRun = 0;
    struct timeval t1,t2;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&p);

    assert(argc == 6);

    seed = atoi(argv[1]);
    A = atoi(argv[2]);
    B = atoi(argv[3]);
    Prime = atoi(argv[4]);
    n = atoi(argv[5]);

    // assert(n > (2 * p));
    // assert(n%p == 0);

    if(rank == 0)
    {
        printf("Number of processes =%d\n", p);
        for(i = 0; i < 10; i++)
        {
            gettimeofday(&t1,NULL);
            serialOutput(seed, A, B, Prime, n);
            gettimeofday(&t2,NULL);
            tRun = (t2.tv_sec-t1.tv_sec)*1000000 + (double)(t2.tv_usec-t1.tv_usec)/1000;
            sum += tRun;
        }
        average = sum/10;
        printf("Process %d Time = %lf milliseconds\n", rank, average);
    }    
    MPI_Finalize();
}

void ParallelOutput(int seed, int A, int B, int P, int nstart, int nsize, int rank, int p)
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
    parallelPrefix(M_loc, p, rank, P, A, B);
    matrixOutputPar(seed, A, B, M_loc[0][0], M_loc[0][1], P, nsize, rank);
}

void parallelPrefix(int M_loc[2][2], int p, int rank, int Prime, int A, int B)
{
    int l[2][2], g[2][2], g_remote[2][2], hold[2][2];
    MPI_Status status;
    int i = 0, mate;
    int log2p = logfunc(p);
    l[0][0] = A;
    l[0][1] = B;
    l[1][0] = 0;
    l[1][1] = 1;
    g_remote[1][0] = 0;
    g_remote[1][1] = 1;
    copymatrix(M_loc, g);
    for(i = 0; i < log2p; i++)
    {
        mate = rank ^ (1 << (i));
        MPI_Sendrecv(&g[0][0],2,MPI_INT,mate,0,&g_remote,2,MPI_INT,mate,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
        if(mate < rank)
        {
            matrixMul(l, g_remote, l, Prime);
        }
        matrixMul(g, g_remote, g, Prime);
    }
    copymatrix(l, M_loc);
}

void matrixOutputPar(int seed, int A, int B, int Aoff, int Boff, int P, int n, int rank)
{
    int M[2][2], M_next[2][2], x_iMat[2][2];
    int x_0Mat[2][2];
    int i = 1;
    M[0][0] = A;
    M[0][1] = B;
    M[1][0] = 0;
    M[1][1] = 1;
    M_next[0][0] = Aoff;
    M_next[0][1] = Boff;
    M_next[1][0] = 0;
    M_next[1][1] = 1;
    x_0Mat[0][0] = seed;
    x_0Mat[1][0] = 1;
    x_0Mat[0][1] = 0;
    x_0Mat[1][1] = 0;
    for(i = 0; i < n; i++)
    {
        matrixMul(x_0Mat, M_next, x_iMat, P);
        printf("x_%d = %d\n", (rank*(n)) + i + 1, x_iMat[0][0]);
        matrixMul(M_next, M, M_next, P);
    }
}

void serialOutput(int seed, int A, int B, int P, int n)
{
    int i = 0, x_i, x_iM1 = seed;
    for(i = 1; i <= n; i++)
    {
        x_i = (A * x_iM1 + B) % P;
       // printf("x_%d = %d\n", i, x_i);
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
    for(i = 1; i <= n; i++)
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
}

int logfunc(int log)
{
    int i = 0;
    while(log = log >> 1)
    {
        i++;
    }
    return i;
}