/*	Cpt S 411, Introduction to Parallel Computing
 *	School of Electrical Engineering and Computer Science
 *	
 *	Example code
 *	Send receive test:
 *   	rank 1 sends to rank 0 (all other ranks sit idle)
 *   	For timing use of C gettimeofday() is recommended.
 * */


#include <stdio.h>
#include <mpi.h> 
#include <assert.h>
#include <sys/time.h>

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
		char *x = "Avoiejnvnervmfklvneriovaenrvklcnoifaedklmfnejrkvndflkfmo;ifnfeirfnewkeroqpfjndsvj4ofjfngweofnfdkfneklfjffnewfnfvewopfndfvdjsofkndfvfjenjkffopfjmwenakfnaropfnajfvaoprfnewfvfopnfasdfvnisdfjvdfnodpaiv";
		int dest = 0;
		gettimeofday(&t1,NULL);
		MPI_Send(&x,200,MPI_BYTE,dest,0,MPI_COMM_WORLD);
		gettimeofday(&t2,NULL);
		int tSend = (t2.tv_sec-t1.tv_sec)*1000 + (t2.tv_usec-t1.tv_usec)/1000;

		printf("Rank=%d: sent message %s to rank %d; Send time %d millisec\n", rank,x,dest,tSend);
   } 
   else if (rank==0) {
   		char *y="\0";
		MPI_Status status;
		gettimeofday(&t1,NULL);
   		MPI_Recv(&y,200,MPI_BYTE,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
		gettimeofday(&t2,NULL);
		int tRecv = (t2.tv_sec-t1.tv_sec)*1000 + (t2.tv_usec-t1.tv_usec)/1000;
		printf("Rank=%d: received message %s from rank %d; Recv time %d millisec\n",rank,y,status.MPI_SOURCE,tRecv);
   }
   MPI_Finalize();
}