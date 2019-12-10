/*
 * Samuel Carroll
 * CPTS 411
 * White Paper Project
 * December 9th, 2019
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
#include <stack>

/*
 * Simple struct I use to hold key, value pair for when I'm
 * calculating my top 5 highest values, I wanted to return both 
 * the keys that hold those values and the values themselves so I used
 * this struct to keep them tied together. 
 */
struct maxfive
{
	long long int key;
	long long int value;
};

std::map<long long int, std::vector<long long int>> myGraph;

std::vector<long long int> V; // V will hold the numbers of vertexes to make finding the values easier because I can't iterate a map in this version
				 // of Openmp
void TopFive(long long int total);
std::vector<std::string> split(std::string line, char delim);
void Walk(long long int Vertex, int damping, long long int walk);
long long int generateGraph(std::string fName);

int main(int argc, char *argv[])
{

	long long int K = 0; // Length of Walk
	long long int Vertices = 0, Edges = 0;
	long long int total = 0;
	long long int i;
	int damping = 0; // Damping value 0 - 100	
	if(argc<3) {
		printf("Usage: loop [Length of Walk] [Damping value 0-100] {Optional: Number of Threads} {Optional: Filename}\n");
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
	if(argc >= 5){
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
	std::cout << "Vertices: " << Vertices << std::endl;
	std::cout << "Edges: " << Edges << std::endl;

	/*
	 * This is where the parallel for loop is called. This loop simply
	 * divides the vertices evenly among the threads and allows each 
	 * thread to then make its walk with each vertex. 
	 */
	double time = omp_get_wtime();

	#pragma omp parallel for schedule(static)
	for(i = 0; i < Vertices; i++)
	{
		Walk(V[i], damping, K);
	}

	time = omp_get_wtime() - time;
	long long int nK = Vertices * K;
	TopFive(nK); // Call top 5 and give the n*K value that will help find the ratios of visits to total walks. 
	std::cout << "Total time = " << time << "seconds" << std::endl;
	return 0;
}

/*
 * TopFive function:
 * This function is what I use to calculate the top 5 visited nodes
 * in the graph, I do it a single pass through of the graph (O(n) time)
 * to reduce on time consumption since the graphs are so huge and this section
 * is done serially.
 */
void TopFive(long long int total)
{
	std::stack<struct maxfive> ret;
	struct maxfive check;
	check.key = -1;
	check.value = 0;
	ret.push(check);
	ret.push(check);
	ret.push(check);
	ret.push(check);
	ret.push(check);
	struct maxfive hold[4] = {0, 0, 0, 0};
	for(const auto& run : myGraph)
	{
		if(run.second.front() > ret.top().value)
		{
			check.key = run.first;
			check.value = run.second.front();
			ret.pop();
			int i = 0;
			while(!ret.empty() && i < 4)
			{
				if(check.value < ret.top().value)
				{
					ret.push(check);
					break;
				}
				hold[i] = ret.top();
				ret.pop();
				i++;
			}
			if(i==4)
				ret.push(check);
			i--;
			for(i; i >= 0; i--)
			{
				ret.push(hold[i]);
			}
		}
	}
	std::cout << "Top 5: " << std::endl;
	for(int j = 0; j < 5; j++)
	{
		std::cout << ret.top().key << ' ' << (double)ret.top().value / total << std::endl;
		ret.pop();
	}
}

/*
 * Split function:
 * This is a simply function for splitting a string based on a
 * provided deliminator char. This is used in separating the Vertex
 * with its corresponding edge when reading in the graph.
 */
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

/*
 * GenerateGraph function:
 * This is the function to generate the graph. It takes only a file name as input
 * and goes to open that file. Once the file is open it traverses it line by line
 * and adds every vertex and corresponding edge to the global variable map that I have.
 * If an edge is being added and that edge is has not been made a vertex yet that edge
 * will be added as a vertex, this is to ensure that all vertices that don't have any 
 * outgoing edges will stil be able to exist in the map. The vector is always initialized
 * with a 0 value which represents the number of visits counter, after that it's all made
 * up of that vertices edges. 
 */
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
				std::cout << curLine << std::endl;
			}
			else
			{
				std::vector<std::string> hold;
				// This is ' ' because it's currently set up to work with the Facebook file
				// I just modify this delimiter when I want to test on other files. 
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
					std::vector<long long int> EdgeHold;
					EdgeHold.push_back(0);
					EdgeHold.push_back(Edge);
					myGraph.insert({Vertex,EdgeHold});
					V.push_back(Vertex);
					count++;
				}
				if(myGraph.count(Edge) == 0)
				{
					std::vector<long long int> EdgeHold;
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
	return count;
}

/*
 * Walk function:
 * This is the function which addresses the algorithm we're meant to be implementing
 * in this project. For its inputs it takes the Vertex value that you want to start
 * from, the damping value to determine where you'll go next, and the total length of 
 * the walk. This function is only called within a parallel for loop and thus has some
 * precautions for thread safety even though within itself it never actually makes itself
 * parallel, this is the reason for a omp atomic being called in an otherwise serial looking
 * function. The function itself simply iterates the current vertex, then generates a 
 * "damping coin flip" to determine if the next vertex will be one of its edges or a random 
 * vertex in the graph, it jumps to the new vertex, iterates that vertices number of visits and
 * the walk continues until it reaches the user provided walk length. 
 */
void Walk(long long int Vertex, int damping, long long int walk) {

    long long int total = 0;
	long long int j, curHop = Vertex, count;
	long long int size = V.size();
	long long int next;
	int rank = omp_get_thread_num();
	unsigned long long int seed = rank+1;
	long long int edges = 0;
	int dampcheck = 0;

	for(j = 0; j < walk; j++)
	{
		#pragma omp atomic
			myGraph[curHop].front()++;
		seed = seed*j;
		dampcheck = (rand_r((unsigned int*)&seed) % 100) + 1; // should be 1 - 100
		if(dampcheck <= damping)
		{
			seed = seed * 4;
			next = (rand_r((unsigned int*)&seed)) % size;
			curHop = V[next];
		}
		else
		{
			seed = seed * 4;
			edges =  myGraph[curHop].size();
			count = 1; // Count starts at 1 because nothing needs to change if next node returns 0 as 
					   // the next node is just itself.
			next = (rand_r((unsigned int*)&seed) % edges); // I use my first value in vector of edges for a visit count
															 // but it also qualifies for that vertexes edge to itself
															 // since it is always present on every vertex.		
			if(next != 0)
			{
				for(count = 1; count < edges; count++)
				{
					if(count == next)
					{
						curHop = myGraph[curHop][count];
						break;
					}
				}
			}
		}
	}
}
