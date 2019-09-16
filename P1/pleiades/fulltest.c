/*	
 * Samuel Carroll
 * CPTS 411
 * HW 1
 * September 17, 2019
 *
 * The first two if statements represent the nonblocking test section. It will be relevant on 
 * ranks 1 and 0. Rank 1 will do a regular send of the message, which will increment in size each
 * iteration up until it hits one megabyte. Rank 0 will be receiving the message
 * from rank 1 using the MPI_Irecv command which is non blocking. It uses the MPI_Wait()
 * command after to wait until the message has arrived and then read it. This isn't that
 * far off from a blocking call since I call wait immediately after the receive call, however
 * it does use this alternative, and since I'm not actually doing anything else there's no reason
 * to use MPI_Test to do other things while waiting for the message. Thus MPI_Wait was the choice.
 *
 * This next two if statements are for the blocking call, it simply uses MPI_Send in rank 3, 
 * and MPI_Recv in rank 2. It prints out the time taken to process the send and receive in
 * milliseconds. Just like the non blocking test it iterates it's bytes sent/received until it
 * gets to one MB at which point it exits and finalizes.
 */


#include <stdio.h>
#include <mpi.h> 
#include <assert.h>
#include <sys/time.h>

// First value over 1 mb that is hit from doubling each iteration (since it doesn't come out to exactly 1MB)
#define MB 1048576

int main(int argc,char *argv[])
{

   int rank,p;
   struct timeval t1,t2;

   MPI_Init(&argc,&argv);
   MPI_Comm_rank(MPI_COMM_WORLD,&rank);
   MPI_Comm_size(MPI_COMM_WORLD,&p);

   printf("my rank=%d\n",rank);
   printf("Rank=%d: number of processes =%d\n",rank,p);

   assert(p>=2);

    if(rank==1) {
        
        // Initialize send buffer
		char x[MB] = {'a'};
		int dest = 0;
        int i = 0;
        MPI_Send(&x,1,MPI_CHAR,dest,0,MPI_COMM_WORLD);
        for(i = 1; i < (MB + 1); i *= 2)
        {
            //memset(x,'a',sizeof(char)*(i-1));
            gettimeofday(&t1,NULL);
            MPI_Send(&x,i,MPI_CHAR,dest,0,MPI_COMM_WORLD);
            gettimeofday(&t2,NULL);
            // Returns time in milliseconds. 
            double tSend = (t2.tv_sec-t1.tv_sec)*1000000 + (double)(t2.tv_usec-t1.tv_usec)/1000;
            printf("Rank=%d: sent of %d bytes to rank %d; Send time %lf millisec\n",rank,i,dest,tSend);
        }
   } 
   else if (rank==0) {
   		char y[MB]={'a'};
		MPI_Status status;
        MPI_Request request;
        int i;
        MPI_Irecv(&y,1,MPI_CHAR,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&request);
        MPI_Wait(&request, &status);
        for(i = 1; i < (MB + 1); i *=2)
        {
            gettimeofday(&t1,NULL);
            MPI_Irecv(&y,i,MPI_CHAR,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&request);
            // Use MPI_Wait to stop everything until message is received. 
            MPI_Wait(&request, &status);
            gettimeofday(&t2,NULL);
            double tRecv = (t2.tv_sec-t1.tv_sec)*1000000 + (double)(t2.tv_usec-t1.tv_usec)/1000;
            printf("Rank=%d: received message %s of %d bytes from rank %d; Recv time %lf millisec\n",rank,y,i,status.MPI_SOURCE,tRecv);
        }
   }
   else if(rank==3) {
        char x[MB] = {'a'};
		int dest = 2;
        int i;
        MPI_Send(&x,1,MPI_CHAR,dest,0,MPI_COMM_WORLD);
        for(i = 1; i < (MB + 1); i *=2)
        {
            //memset(x,'a',sizeof(char)*(i-1));
            gettimeofday(&t1,NULL);
            MPI_Send(&x,i,MPI_BYTE,dest,0,MPI_COMM_WORLD);
            gettimeofday(&t2,NULL);
            double tSend = (t2.tv_sec-t1.tv_sec)*1000000 + (double)(t2.tv_usec-t1.tv_usec)/1000;
            printf("Rank=%d: sent %d bytes to rank %d; Send time %lf millisec\n", rank,i,dest,tSend);
        }
   } 
   else if (rank==2) {
   		char y[MB]={'a'};
		MPI_Status status;
        int i;
        MPI_Recv(&y,1,MPI_BYTE,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
        for(i = 1; i < (MB + 1); i *=2)
        {
            gettimeofday(&t1,NULL);
            MPI_Recv(&y,i,MPI_BYTE,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
            gettimeofday(&t2,NULL);
            double tRecv = (t2.tv_sec-t1.tv_sec)*1000000 + (double)(t2.tv_usec-t1.tv_usec)/1000;
            printf("Rank=%d: received message %s of %d bytes from rank %d; Recv time %lf millisec\n",rank,y,i,status.MPI_SOURCE,tRecv);
        }
   }

   MPI_Finalize();
}