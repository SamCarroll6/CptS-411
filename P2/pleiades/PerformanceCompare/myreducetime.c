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

void printarray(int *arr, int n);
int *generatearray(int n, int rank);
int mpilibraryreduce(int *arr, int n, int flag);
int sumarray(int *arr, int n);
int naivereduce(int *arr, int n, int rank, int p, int flag);
int numreceives(int rank);
int senditto(int rank);
int myreduce(int *arr, int n, int rank, int p, int flag);

int main(int argc, char *argv[])
{
    int rank,p,i;
    struct timeval t1,t2;
    double tsend, total = 0;
    int n, *arr, binaryAR, binaryN, binaryMR, overflow, flag;
    char printval[4];
    // Init and setup calls
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&p);
    printf("my rank=%d\n",rank);
    if(rank == 0)
    {
        printf("Rank=%d: number of processes =%d, overall array size = %d\n",rank,p,n);
    }

    assert((p & (p - 1)) == 0 && (p != 0));

    n = atoi(argv[1]);
    flag = atoi(argv[2]);

    assert(n > p);
    assert(flag >= 0);

    if(flag > 1)
        flag = 1;

    strcpy(printval, flag ? "Max" : "Sum");

    overflow = n % p;
    for(i = 0; i < 10; i++)
    {
        if(rank == 0)
        {
            arr = generatearray(n/p + overflow, rank);
            gettimeofday(&t1,NULL);
            binaryMR = myreduce(arr, n/p + overflow, rank, p, flag);
            gettimeofday(&t2,NULL);
            tsend = (t2.tv_sec-t1.tv_sec)*1000000 + (double)(t2.tv_usec-t1.tv_usec)/1000;
            if(p == 1)
            {
                //printf("%s = %d\n", printval, binaryMR);
                total += tsend;
            }
        }
        else
        {
            arr = generatearray(n/p, rank);
            gettimeofday(&t1,NULL);
            binaryMR = myreduce(arr, n/p, rank, p, flag);
            gettimeofday(&t2,NULL);
            tsend = (t2.tv_sec-t1.tv_sec)*1000000 + (double)(t2.tv_usec-t1.tv_usec)/1000;
            if(rank == p - 1)
            {
                total += tsend;
                //printf("%s = %lf\n", printval, total);
                
            }
        }
    }
    if(rank == p-1 || p == 1)
        printf("My Reduce Rank=%d: Send time %lf millisec\n",rank,(total / 10));
    MPI_Finalize();
}

/*
 * Inputs: int n, int rank
 * Output: integer array
 * Function: The first input is an n value, this value is used to set the size 
 *           of the array. We malloc an integer pointer the size n to dynamically
 *           create an integer array. The rank input is used for a random seed value
 *           I multiply my rank by the current time value in order to set a seed that is
 *           unique to each processor to keep the arrays truly random. In the end the 
 *           function returns the created array of random integers.
 */
int *generatearray(int n, int rank)
{
    int *arr = (int *)malloc(sizeof(int) * n);
    int i;
    assert(arr != NULL);

    srand((rank + 1) * time(NULL));
    for(i = 0; i < n; i++)
    {
        arr[i] = (rand() % 100000) + 1;
    }
    return arr;
}

/*
 * Inputs: int* arr, int n
 * Output: N/A
 * Function: This is a simple print function so I know the values in my random 
 *           arrays. It uses the n value to know how many values it will be printing.
 */
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

/*
 * Inputs: int *arr, int n, int rank, int p
 * Output: integer
 * Function: My reduce function, using hyperbolic reduction to reduce the given array. 
 *           Starts by getting the (sum or max) value of your local array that was
 *           passed in as an argument. From there it either receives additional values or just 
 *           sends off the bat depending on it's rank. 
 */
int myreduce(int *arr, int n, int rank, int p, int flag)
{
    int binary = 0, recv;
    int i = 0, recvnum, sendloc;
    MPI_Status status;
    // if(flag == SUM)
    // {
    //    binary = sumarray(arr, n); 
    // }
    // else if(flag == MAX)
    // {
    //     binary = findmax(arr, n);
    // }
    binary = flag ? findmax(arr, n) : sumarray(arr, n);
    recvnum = numreceives(rank);
    if(p == 1)
    {
        return binary;
    }
    for(i; i < recvnum; i++)
    {
        MPI_Recv(&recv, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
        if(flag == SUM)
        {
            binary += recv;
        }
        else if(flag == MAX)
        {
            binary = recv > binary ? recv : binary;
        }
    }
    if(rank != (p-1))
    {
        sendloc = senditto(rank);
        if(sendloc < p)
        {   
            MPI_Send(&binary,1,MPI_INT,sendloc,0,MPI_COMM_WORLD);
        }
    }
    return binary;
}

/*
 * Inputs: int rank
 * Output: integer
 * Function: This function is a helper function for the myreduce function above. 
 *           It "counts" the number of 1's that occur in a binary value before the 
 *           first 0 appears. It then returns that count value. This count is used
 *           in a while loop in myreduce() in order to know how many times each process
 *           needs to receive values before it's able to send it's value.
 */
int numreceives(int rank)
{
    int i = 0; 
    int hold = rank;
    while(hold % 2 == 1)
    {
        i++;
        hold = hold >> 1;
    }
    return i;
}

/*
 * Inputs: int rank
 * Output: integer
 * Function: Similar to the above function this one is used to find which
 *           rank the current process is sending it's values to next. For this
 *           one it is finding the first zero to occur in the ranks binary representation.
 *           it then returns the process rank with the first 0 bit flipped to a 1. 
 *           This return value will be the same as the rank of the process you will send to.
 */
int senditto(int rank)
{
    int i = 0;
    int hold = rank;
    while(hold % 2 == 1)
    {
        i++;
        hold = hold >> 1;
    }
    return rank + (1 << i);
}

/*
 * Inputs: int *arr, int n, int rank, int p
 * Output: integer
 * Function: Simple reduce function using bus/array reduction.
 *           It will simply calculate it's local arrays (sum or max)
 *           and then send it's local value to the next rank. If it's not 
 *           rank 0 it needs to receive and combine the received result to its local
 *           result before sending. If it's the processor p-1 it will only receive and not
 *           send, this processor returns its final value as the result.
 */
int naivereduce(int *arr, int n, int rank, int p, int flag)
{
    int binary = 0, recv;
    MPI_Status status;
    binary = flag ? findmax(arr, n) : sumarray(arr, n);
    if(p == 1)
    {
        return binary;
    }
    if(rank == 0)
    {
        MPI_Recv(&recv, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD, &status);
        if(flag == SUM)
        {
            binary += recv;
        }
        else if(flag == MAX)
        {
            binary = recv > binary ? recv : binary;
        }
    }
    else if(rank == (p - 1))
    {
        MPI_Send(&binary,1,MPI_INT,(rank-1),0,MPI_COMM_WORLD);
    }
    else
    {
        MPI_Recv(&recv,1,MPI_INT,(rank + 1),MPI_ANY_TAG,MPI_COMM_WORLD,&status);
        if(flag == SUM)
        {
            binary += recv;
        }
        else if(flag == MAX)
        {
            binary = recv > binary ? recv : binary;
        }
        MPI_Send(&binary,1,MPI_INT,(rank-1),0,MPI_COMM_WORLD);
    }
    return binary;
}

/*
 * Inputs: int *arr, int n
 * Output: integer
 * Function: Simply sums all of the values in an array.
 */
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

int findmax(int *arr, int n)
{
    int i = 0, max = arr[0];
    for(i; i < n; i++)
    {
        if(arr[i] > max)
            max = arr[i];
    }
    return max;
}

/*
 * Inputs: int *arr, int n
 * Output: integer
 * Function: The MPI libraries reduce implementation. I tried passing a whole array
 *           but it only worked when a single value was sent so I get the (sum or max)
 *           locally before I put it into the function. Returns the final calculated value.
 */
int mpilibraryreduce(int *arr, int n, int flag)
{
    int binary, val;
    val = flag ? findmax(arr, n) : sumarray(arr, n);
    if(flag == SUM)
        MPI_Allreduce(&val, &binary, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
    else if(flag == MAX)
        MPI_Allreduce(&val, &binary, 1, MPI_INT, MPI_MAX, MPI_COMM_WORLD);
    return binary;
}