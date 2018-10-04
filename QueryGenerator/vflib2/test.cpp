#include <iostream>
#include <fstream>
#include <stdio.h>

#include "argraph.h"
#include "argedit.h"
#include "argloader.h"
#include "allocpool.h"
#include "vf2_sub_state.h"
#include "match.h"
#include "math.h"

//To load and save graph from files, there are two classes derived from ARGLoader: BinaryGraphLoader and StreamARGLoader.
//The former does not consider the node/edge attributes, while the latter considers.

using namespace std;

//NOTICE:there are many algorithms can be used, both for isomorphism and graph-subgraph isomorphism
//1. Ullmann: 
//1.1 isomorphism: ull_state.h UllState
//1.2 graph-subgraph isomorphism: ull_sub_state.h UllSubState
//1. VF: 
//1.1 isomorphism: vf_state.h VFState
//1.2 graph-subgraph isomorphism: vf_sub_state.h VFSubState
//1.3 monomorphism: vf_mono_state.h VFMonoState
//1. VF2: 
//1.1 isomorphism: vf2_state.h VF2State
//1.2 graph-subgraph isomorphism: vf2_sub_state.h VF2SubState
//1.3 monomorphism: vf2_mono_state.h VF2MonoState

//TODO:adding and using node/edge attributes, attribute destroyer and attribute comparator

#define MAXNODES 200

class Point
{
public:
	float x, y;
	Point()
	{
		x = y = 0.0;
	}
	Point(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
};

class PointDestroyer:public AttrDestroyer
{
public:
	virtual void destroy(void* p)
	{
		delete p;
	}
};

class PointComparator:public AttrComparator
{
private:
	double threshold;
public:
	PointComparator(double thr)
	{
		threshold = thr;
	}
	virtual bool compatible(void* pa, void* pb)
	{
		Point* a = (Point*)pa;
		Point* b = (Point*)pb;
		//function hypot is declared in <math.h>
		double dist = hypot(a->x - b->x, a->y - b->y);
		return dist < threshold;
	}
};

istream& operator>>(istream& in, Point& p)
{
	in >> p.x >> p.y;
	return in;
}

ostream& operator<<(ostream& out, Point& p)
{
	out << p.x << ' ' << p.y;
	return out;
}

class Empty
{
};

istream& operator>>(istream& in, Empty&)
{
	return in;
}

ostream& operator<<(ostream& out, Empty&)
{
	return out;
}

void buildGraph()
{
	ARGEdit ed;   //the object used to create the graph
	int i, j;

	//insert 4 nodes
	for(i = 0; i < 4; ++i)
	{
		//the node will have index i
		//NULL means no semantic attribute
		ed.InsertNode(NULL); 
	}

	//insert the edges
	for(i = 0; i < 4; ++i)
	{
		for(j = 0; j < 4; ++j)
		{
			if(i != j)
			{
				//edge i->j without semantic attribute
				ed.InsertEdge(i, j, NULL);
			}
		}
	}

	//now the graph can be built
	Graph g(&ed);
}

bool my_visitor(int n, node_id ni1[], node_id ni2[], void* usr_data)
{
	FILE* f = (FILE*)usr_data;
	//print the matching pairs on the file
	int i;
	for(i = 0; i < n; ++i)
	{
		fprintf(f, "(%hd, %hd) ", ni1[i], ni2[i]);
	}
	fprintf(f, "\n");
	//return false to search for the next matching
	return false;
}

int main()
{
	int i, j;

	//perform graph-subgraph isomorphism this way
	ARGEdit small_ed, large_ed;
	for(i = 0; i < 4; ++i)
	{
		small_ed.InsertNode(NULL); 
	}
	//insert the edges
	for(i = 0; i < 4; ++i)
	{
		for(j = 0; j < 4; ++j)
		{
			if(i != j)
			{
				small_ed.InsertEdge(i, j, NULL);
			}
		}
	}

	for(i = 0; i < 6; ++i)
	{
		large_ed.InsertNode(NULL); 
	}
	for(i = 0; i < 6; ++i)
	{
		for(j = 0; j < 6; ++j)
		{
			if(i != j)
			{
				large_ed.InsertEdge(i, j, NULL);
			}
		}
	}

//=====================================================================================================================================================
//Find The First Matching Between Graph and Subgraph
//=====================================================================================================================================================

	//construct twoo graphs
	Graph small_graph(&small_ed), large_graph(&large_ed);
	//create initial state
	VF2SubState s0(&small_graph, &large_graph);
	int n; //matching node num
	node_id ni1[MAXNODES], ni2[MAXNODES];

	if(!match(&s0, &n, ni1, ni2))
	{
		printf("No matching found!\n");
		return 1;
	}
	printf("Found a matching with %d nodes:\n", n);
	for(i = 0; i < n; ++i)
	{
		printf("\tNode %hd of graph 1 is paired with node %hd of graph 2\n", ni1[i], ni2[i]);
	}

//=====================================================================================================================================================
//Find All Matchings Between Graph and Subgraph
//=====================================================================================================================================================
	FILE* f = fopen("output.txt", "w");
	match(&s0, my_visitor, f);
	fclose(f);

//=====================================================================================================================================================
//Find All Matchings Between Graph and Subgraph
//=====================================================================================================================================================
	//create the allocators
	NewAllocator<Point> node_allocator;
	NullAllocator<Empty> edge_allocator;
	//open the file
	ifstream in("infile.txt");
	//create the ARGLoader
	StreamARGLoader<Point, Empty> loader(&node_allocator, &edge_allocator, in);
	//build the graph
	ARGraph<Point, Empty> graph(&loader);
	in.close();
	//open a text file to write
	ofstream out("outfile.txt");
	//write the graph
	StreamARGLoader<Point, Empty>::write(out, graph);
	out.close();

	return 0;
}

