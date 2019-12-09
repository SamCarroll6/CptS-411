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

std::vector<long long int> V; // V will hold the numbers of vertexes to make finding the values easier because I can't iterate a map in this version
				 // of Openmp

std::vector<std::string> split(std::string line, char delim);
void Walk(long long int Vertex, int damping, long long int walk);
long long int generateGraph(std::string fName);

int main(int argc, char *argv[])
{

	long long int K = 0; // Length of Walk
	long long int Vertices = 0, Edges = 0;
	int damping = 0; // Damping value 0 - 100	

	if(argc<3) {
		printf("Usage: loop [Length of Walk] [Damping value {0-100}] {Optional: Number of Threads} {Optional: Filename}\n");
		exit(1);
	}
	
	K = atoll(argv[1]);
	damping = atoi(argv[2]);

	assert(damping <= 100 && damping >= 0);

	int p=1;
	if(argc >= 4) {
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

	Edges = generateGraph(fName);

	Vertices = myGraph.size();
	long long int total = 0;
	std::cout << "Vertices: " << Vertices << std::endl;
	std::cout << "Edges: " << Edges << std::endl;

	double time = omp_get_wtime();
	//#pragma omp parallel for schedule(static) reduction(+:total)
	for(int i = 0; i < Vertices; i++)
	{
		Walk(V[i], damping, K);
		total++;
	}
	time = omp_get_wtime() - time;

    printf("Total = %lld\n", total);
	printf("Total time = %f seconds \n ", time);
	return 0;
}

std::vector<std::string> split(std::string line, char delim)
{
	std::vector<std::string> ret; 
	// .push_back();
	std::istringstream iss(line);
	std::string hold; 
	while(std::getline(iss, hold, delim))
	{
		ret.push_back(hold);
	}
	return ret;
}

long long int generateGraph(std::string fName)
{
	std::string curLine;
	long long int Vertex = 0, Edge = 0, count = 0;
	std::ifstream inputFile(fName);
	if(inputFile.is_open())
	{
		while(getline(inputFile,curLine))
		{
			if(curLine[0] == '#')
			{
				std::cout << curLine;
			}
			else
			{
				std::vector<std::string> hold;
				hold = split(curLine, ' ');
				Vertex = stoll(hold[0]);
				Edge = stoll(hold[1]);
				if(myGraph.count(Vertex) != 0)
				{
					myGraph[Vertex].push_back(Edge);
					count++;
				}
				else
				{
					std::list<long long int> EdgeHold;
					EdgeHold.push_back(0);
					EdgeHold.push_back(Edge);
					myGraph.insert({Vertex,EdgeHold});
					V.push_back(Vertex);
					count++;
				}
				if(myGraph.count(Edge) == 0)
				{
					std::list<long long int> EdgeHold;
					EdgeHold.push_back(0);
					myGraph.insert({Edge,EdgeHold});
					V.push_back(Edge);
				}
			}
		}
		inputFile.close();
	}
	else{
		std::cout << "Could not open file\n";
		return 0;
	}
	// for(auto vertex : myGraph)
	// {
	// 	bool first = true;
	// 	std::cout << vertex.first << std::endl; 
	// 	for(auto edge : vertex.second){
	// 		if(first)
	// 		{
	// 			first = false;
	// 			continue;
	// 		}
	// 		std::cout << '\t' << edge << std::endl;
	// 	}
	// }
	return count;
}


void Walk(long long int Vertex, int damping, long long int walk) {

    long long int total = 0;
	long long int j;


	for(j = 0; j < walk; j++)
	{
		int rank = omp_get_thread_num();
		unsigned long long int seed = rank+1;
		seed = seed*j;
		int dampcheck = (rand_r((unsigned int*)&seed) % 100) + 1; // should be 1 - 100
		if(dampcheck <= damping)
		{
			//std::cout << "TRUE  " << dampcheck << std::endl;
		}
		else
		{
			//std::cout << "FALSE  " << dampcheck << std::endl;
		}
			// int rank = omp_get_thread_num();
			// float x = (float)rand_r((unsigned int*)&seed)/RAND_MAX;
			// seed = seed / 2;
			// float y = (float)rand_r((unsigned int*)&seed)/RAND_MAX;
			// float distance = sqrt((pow((x - 0.5), 2)+pow((y-0.5),2)));
	}
}
