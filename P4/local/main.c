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
void foo_locks(long long int);

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

	foo_locks(loops);


	return 0;
}


void foo_locks(long long int n) {
	long long int total = 0;
    long long int hits = 0;
    float x, y, distance;
	int i;
    srand(300);
	//omp_lock_t my_lock;

	//omp_init_lock(&my_lock);

	double time = omp_get_wtime();
	#pragma omp parallel for schedule(static) private(x,y,distance) shared(total) reduction(+:hits)
	for(i = 0; i < n; i++) 
	{	
		//omp_set_lock(&my_lock);
		x = (float)rand()/RAND_MAX;
        y = (float)rand()/RAND_MAX;
        distance = sqrt((pow((x - 0.5), 2)+pow((y-0.5),2)));
        if(distance <= 0.5)
            hits += 1;
		#pragma omp atomic
        	total += 1;
		//omp_unset_lock(&my_lock);
	}
	//omp_destroy_lock(&my_lock);
	
	time = omp_get_wtime() - time;
    printf("%lld %lld\n", hits, total);
    printf("Value of pi = %.20lf\n", 4*((float)hits/(float)n));
	printf("Locks: Total time = %f seconds \n ", time);
}
