#include <iostream>
#include <fstream>
#include <stdio.h>
#include <vector>
#include <math.h>
#include <time.h>
#include <sys/time.h>

#include "argraph.h"
#include "argedit.h"
#include "argloader.h"
#include "allocpool.h"
#include "vf2_sub_state.h"
#include "match.h"

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

//the maxium node num in data/query graphs are 213
#define MAXNODES 300

class LABEL
{
public:
	int lb;
	LABEL(int _lb)
	{
		lb = _lb;
	}
};

class LABELDestroyer: public AttrDestroyer
{
public:
	virtual void destroy(void* p)
	{
		delete p;
	}
};

class LABELComparator: public AttrComparator
{
public:
	LABELComparator()
	{
	}
	virtual bool compatible(void* pa, void* pb)
	{
		int* a = (int*)pa;
		int* b = (int*)pb;
		return *a == *b;
	}
};

long get_cur_time()
{
	timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec*1000 + tv.tv_usec/1000);
}

bool my_visitor(int n, node_id ni1[], node_id ni2[], void* usr_data)
{
	//cout<<"a new matching pair"<<endl;
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

//NOTICE:not use FILE*& here, fp-- does not means the pointer-- for FILE*
//However, it means the FILE position moves (still that file pointer) -- this is invalid!!!
//use fseek to do this thing
bool input(FILE* fp, ARGEdit& ed)
{
	char c1, c2;
	int id0, id1, id2, lb;
	bool flag = false;

	while(true)
	{
		fscanf(fp, "%c", &c1);
		if(c1 == 't')
		{
			if(flag)
			{
				fseek(fp, -1, SEEK_CUR);
				//cout<<"end a graph"<<endl;
				return true;
			}
			flag = true;
			fscanf(fp, " %c %d\n", &c2, &id0);
			//cout<<"graph "<<id0<<endl;
			if(id0 == -1)
			{
				//cout<<"end the file"<<endl;
				return false;
			}
		}
		else if(c1 == 'v')
		{
			fscanf(fp, " %d %d\n", &id1, &lb);
			ed.InsertNode(new int(lb)); 
		}
		else if(c1 == 'e')
		{
			fscanf(fp, " %d %d %d\n", &id1, &id2, &lb);
			//cout<<id1<<" "<<id2<<" "<<lb<<endl;
			ed.InsertEdge(id1, id2, new int(lb));
			ed.InsertEdge(id2, id1, new int(lb));
		}
		else 
		{
			cerr<<"ERROR in input() -- invalid char"<<endl;
			return false;
		}
	}

	return true;
}

//=====================================================================================================================================================
//Find All Matchings Between Graph and Subgraph
//=====================================================================================================================================================
int main(int argc, const char* argv[])
{
	long begin = get_cur_time();

	//0:program 1:dataset 2:query [3:output]
	FILE* dfp = fopen(argv[1], "r");
	FILE* qfp = fopen(argv[2], "r");
	//NOTICE:data file contains large graphs, while query file contains small graphs
	string output = "ans.txt";
	if(argc > 3)
	{
		output = argv[3];
	}
	FILE* ofp = fopen(output.c_str(), "w");
	int i, j;
	string line = "============================================================";
	//perform graph-subgraph isomorphism this way
	//NOTICE:query graphs are much smaller, so we keep all queries in memory,
	//while loop read data graph to save the space cost
	vector<Graph*> query_list;

	while(true)
	{
		ARGEdit query_ed;
		if(!input(qfp, query_ed)) //to the end
			break;
		ARGraph<int,int>* query_graph = new ARGraph<int,int>(&query_ed);
		query_graph->SetNodeDestroyer(new LABELDestroyer());
		query_graph->SetNodeComparator(new LABELComparator());
		query_graph->SetEdgeDestroyer(new LABELDestroyer());
		query_graph->SetEdgeComparator(new LABELComparator());
		query_list.push_back(query_graph);
	}
	fclose(qfp);

	int qnum = query_list.size(), dnum = 0;
	//input data graph one by one
	while(true)
	{
		//cout<<"data graph "<<dnum<<endl;
		ARGEdit data_ed;
		if(!input(dfp, data_ed)) //to the end
			break;
		ARGraph<int,int> data_graph(&data_ed);
		for(i = 0; i < qnum; ++i)
		{
			//cout<<"query graph "<<qnum<<endl;
			VF2SubState s0(query_list[i], &data_graph);
			int n; //matching node num
			node_id ni1[MAXNODES], ni2[MAXNODES];
			fprintf(ofp, "query graph:%d    data graph:%d\n", i, dnum);
			fprintf(ofp, "%s\n", line.c_str());
			match(&s0, my_visitor, ofp);
			fprintf(ofp, "\n\n\n");
		}
		dnum++;
	}

	//release the memory 
	for(i = 0; i < qnum; ++i)
	{
		delete query_list[i];
	}

	fclose(dfp);
	fflush(ofp);
	fclose(ofp);

	long end = get_cur_time();
	cout<<"totally used "<<(end-begin)<<"ms"<<endl;
	return 0;
}

