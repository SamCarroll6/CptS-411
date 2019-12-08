/*
 * Samuel Carroll
 * CPTS 411
 * HW 4
 * November 14th, 2019
 * 
 */

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <math.h>
#include <assert.h>
#include <map>
#include <list>

void Pi_Est(long long int);

int main(int argc, char *argv[])
{
	
	std::map<int,std::list<int>> mymap;
	mymap[15].push_back(10000);
	for(auto hold : mymap[15])
	{
		std::cout << hold << '\n';
	}
	
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
	omp_set_dynamic(0);

	#pragma omp parallel
	{
		assert(p==omp_get_num_threads());

		int rank = omp_get_thread_num();
	}

	Pi_Est(loops);


	return 0;
}


void Pi_Est(long long int n) {

    long long int hits = 0;
	long long int i;

	double time = omp_get_wtime();
	#pragma omp parallel for schedule(static) reduction(+:hits)
	for(i = 0; i < n; i++) 
	{	
		int rank = omp_get_thread_num();
		unsigned long long int seed = rank+1;
		seed = seed*i;
		float x = (float)rand_r((unsigned int*)&seed)/RAND_MAX;
		seed = seed / 2;
        float y = (float)rand_r((unsigned int*)&seed)/RAND_MAX;
        float distance = sqrt((pow((x - 0.5), 2)+pow((y-0.5),2)));
        if(distance <= 0.5)
            hits += 1;
	}
	
	time = omp_get_wtime() - time;
    printf("%lld %lld\n", hits, n);
    printf("Value of pi = %.20lf\n", 4*((float)hits/(float)n));
	printf("Locks: Total time = %f seconds \n ", time);
}
