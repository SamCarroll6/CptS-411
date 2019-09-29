#include <stdio.h>
#include <mpi.h> 
#include <assert.h>
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>

int sum = 0;
const int arrtest[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

void printarray(int *arr, int n);
int *generatearray(int n, int rank);
int mpilibraryreduce(int *arr);

int main(int argc, char *argv[])
{
    int rank,p;
    struct timeval t1,t2;
    int n;

    // Init and setup calls
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&p);
    printf("my rank=%d\n",rank);
    printf("Rank=%d: number of processes =%d\n",rank,p);

    n = atoi(argv[1]);

    printf("argv[1] = %d\n", n);

    mpilibraryreduce(arrtest);
    printf("Sum = %d\n", sum);
    generatearray(n, rank);
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
    printarray(arr, n);
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

int naivereduce(int *arr)
{

}

int mpilibraryreduce(int *arr)
{
    MPI_Allreduce(arr, &sum, 10, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
}