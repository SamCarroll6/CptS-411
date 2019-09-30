#include <stdio.h>
#include <mpi.h> 
#include <assert.h>
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>

const int arrtest[10] = {1, 1, 2, 3, 4, 5, 6, 7, 8, 9};

void printarray(int *arr, int n);
int *generatearray(int n, int rank);
int mpilibraryreduce(int *arr, int n);
int sumarray(int *arr, int n);
int naivereduce(int *arr, int n, int rank, int p);

int main(int argc, char *argv[])
{
    int rank,p;
    struct timeval t1,t2;
    int n, *arr, sumAR, sumN, sumMR, overflow;

    // Init and setup calls
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&p);
    printf("my rank=%d\n",rank);
    if(rank == 0)
    {
        printf("Rank=%d: number of processes =%d\n",rank,p);
    }

    assert((p & (p - 1)) == 0 && (p != 0));

    n = atoi(argv[1]);

    assert(n > p);

    overflow = n % p;
    if(rank == 0)
    {
        arr = generatearray(n/p + overflow, rank);
        printarray(arr, n/p + overflow);
        sumAR = mpilibraryreduce(arr, n/p + overflow);
        sumN = naivereduce(arr, n/p + overflow, rank, p);
        printf("SumAR = %d\n", sumAR);
        printf("SumN = %d\n", sumN);
    }
    else
    {
        arr = generatearray(n/p, rank);
        printarray(arr, n/p);
        mpilibraryreduce(arr, n/p);
        naivereduce(arr, n/p, rank, p);
    }
    //mpilibraryreduce(arrtest);
    //printf("Sum = %d\n", sum);
    MPI_Finalize();
}

int *generatearray(int n, int rank)
{
    int *arr = (int *)malloc(sizeof(int) * n);
    int i;
    assert(arr != NULL);

    srand((rank + 1) * time(NULL));
    for(i = 0; i < n; i++)
    {
        arr[i] = (rand() % 100) + 1;
    }
    return arr;
}

void printarray(int* arr, int n)
{
    int i = 0;
    printf("Array:");
    for(i; i < n; i++)
    {
        printf(" %d", arr[i]);
        if(i % 15 == 14)
            printf("\n      ");
    }
    printf("\n");
}

int myreduce(int *arr)
{

}

int naivereduce(int *arr, int n, int rank, int p)
{
    int sum = 0, recv;
    MPI_Status status;
    sum = sumarray(arr, n);

    if(rank == 0)
    {
        MPI_Recv(&recv, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD, &status);
        sum += recv;
    }
    else if(rank == (p - 1))
    {
        MPI_Send(&sum,1,MPI_INT,(rank-1),0,MPI_COMM_WORLD);
    }
    else
    {
        MPI_Recv(&recv,1,MPI_INT,(rank + 1),MPI_ANY_TAG,MPI_COMM_WORLD,&status);
        sum += recv;
        MPI_Send(&sum,1,MPI_INT,(rank-1),0,MPI_COMM_WORLD);
    }
    return sum;
}

int sumarray(int *arr, int n)
{
    int i = 0;
    int sum = 0;
    for(i; i < n; i++)
    {
        sum += arr[i];
    }
    return sum;
}

int mpilibraryreduce(int *arr, int n)
{
    int sum, val;
    val = sumarray(arr, n);
    MPI_Allreduce(&val, &sum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
    return sum;
}