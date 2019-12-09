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
#include <iterator>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>

std::map<long long int, std::list<long long int>> myGraph;

std::vector<std::string> split(std::string line, char delim);
void Pi_Est(long long int n);
void generateGraph(std::string fName);

int main(int argc, char *argv[])
{

	unsigned long long int K = 0; // Length of Walk
	int damping = 0; // Damping value 0 - 100	

	// mymap[15].push_back(10000);
	// for(auto hold : mymap[15])
	// {
	// 	std::cout << hold << '\n';
	// }

	if(argc<3) {
		printf("Usage: loop [Length of Walk] [Damping value {0-100}] {Optional: Number of Threads} {Optional: Filename}\n");
		exit(1);
	}
	
	K = atoll(argv[1]);
	damping = atoi(argv[2]);

	assert(damping <= 100 && damping >= 0);

	int p=1;
	if(argc==4) {
		p = atoi(argv[3]);
		assert(p>=1);
		printf("Debug: number of requested threads = %d\n",p);
	}

	std::string fName = "../Paths/Facebook.txt";
	if(argc==5){
		fName.assign(argv[4]);
	}

	std::cout << fName << std::endl;

	omp_set_num_threads(p);
	omp_set_dynamic(0);

	#pragma omp parallel
	{
		assert(p==omp_get_num_threads());

		int rank = omp_get_thread_num();
	}

	generateGraph(fName);

	//Pi_Est(loops);


	return 0;
}

std::vector<std::string> split(std::string line, char delim)
{
	std::vector<std::string> ret; 
	// .push_back();
	std::istringstream iss(line);
	std::string hold; 
	while(std::getline(iss, hold, ' '))
	{
		ret.push_back(hold);
	}
	return ret;
}

void generateGraph(std::string fName)
{
	std::string curLine;
	long long int Vertex = 0, Edge = 0;
	std::ifstream inputFile(fName);
	if(inputFile.is_open())
	{
		while(getline(inputFile,curLine))
		{
			if(curLine[0] == '#')
			{
				std::cout << "Comment\n";
			}
			else
			{
				std::vector<std::string> hold;
				hold = split(curLine, ' ');
				Vertex = stoll(hold[0]);
				Edge = stoll(hold[1]);
				if(myGraph.count(Vertex) != 0)
					myGraph[Vertex].push_back(Edge);
				else
				{
					std::list<long long int> EdgeHold;
					EdgeHold.push_back(Edge);
					myGraph.insert({Vertex,EdgeHold});
				}
			}
		}
		inputFile.close();
	}
	else{
		std::cout << "Could not open file\n";
		return;
	}
	for(auto vertex : myGraph)
	{
		std::cout << vertex.first << std::endl; 
		for(auto edge : vertex.second){
			std::cout << '\t' << edge << std::endl;
		}
	}
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
