/*
 * Samuel Carroll
 * CPTS 411
 * HW 4
 * November 14th, 2019
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <math.h>
#include <assert.h>

void foo_critical(long long int);
//void foo_atomic(long long int);
void foo_locks(long long int, int threads);

int main(int argc, char *argv[])
{
	long long int i, loops;

	if(argc<2) {
		printf("Usage: loop {number of iterations} [number of threads]\n");
		exit(1);
	}
	
	loops = atoll(argv[1]);
	printf("Info: number of iterations = %lld (%d)\n",loops, sizeof(long long int));

	int p=1;
	if(argc==3) {
		p = atoi(argv[2]);
		assert(p>=1);
		printf("Debug: number of requested threads = %d\n",p);
	}

	omp_set_num_threads(p);

	#pragma omp parallel
	{
		assert(p==omp_get_num_threads());

		int rank = omp_get_thread_num();
	}

	foo_locks(loops, p);


	return 0;
}


void foo_locks(long long int n, int threads) {
	long long int total = 0;
    long long int hits = 0;
    float *x, *y, distance;
	x = (float*)malloc(sizeof(float) * threads);
	y = (float*)malloc(sizeof(float) * threads);
	long long int i;
    srand(300);
	omp_lock_t *my_lock;
	my_lock = (omp_lock_t*)malloc(sizeof(omp_lock_t) * threads);
	for(i = 0; i < threads; i++)
	{
		omp_init_lock(&(my_lock[i]));
	}
	

	double time = omp_get_wtime();
	#pragma omp parallel for schedule(static) shared(x,y,my_lock)	
	for(i = 0; i < n; i++) 
	{	
		//int rank = omp_get_thread_num();
		//printf("%d %d\n", rank, omp_get_thread_num());
		omp_set_lock(&(my_lock[(i*49999)%threads]));
		x[(i*49999)%threads] = (float)rand()/RAND_MAX;
        y[(i*49999)%threads] = (float)rand()/RAND_MAX;
		//omp_set_lock(&my_lock);
      //  distance = sqrt((pow((x[omp_get_thread_num()] - 0.5), 2)+pow((y[omp_get_thread_num()]-0.5),2)));
		if(sqrt((pow((x[(i*49999)%threads] - 0.5), 2)+pow((y[(i*49999)%threads]-0.5),2))) <= 0.5)
		{
			#pragma omp atomic
            hits += 1;
		}
       // total += 1;
		omp_unset_lock(&(my_lock[(i*7)%threads]));
	}
	for(i = 0; i < threads; i++)
	{
		omp_destroy_lock(&(my_lock[i]));
	}
	//omp_destroy_lock(&my_lock);
	
	time = omp_get_wtime() - time;
    printf("%lld %lld\n", hits, total);
    printf("Value of pi = %.20lf\n", 4*((float)hits/(float)n));
	printf("Locks: Total time = %f seconds \n ", time);
}
