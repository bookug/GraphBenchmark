/*=============================================================================
# Filename: IO.cpp
# Author: Bookug Lobert 
# Mail: 1181955272@qq.com
# Last Modified: 2016-10-24 22:55
# Description: 
=============================================================================*/

#include "IO.h"

using namespace std;

IO::IO()
{
	this->ifp = NULL;
	this->ofp = NULL;
}

IO::IO(std::string data, std::string file)
{
	ifp = fopen(data.c_str(), "r");
	if(ifp == NULL)
	{
		cerr<<"input open error!"<<endl;
		return;
	}
	ofp = fopen(file.c_str(), "w+");
	if(ofp == NULL)
	{
		cerr<<"output open error!"<<endl;
		return;
	}
}

bool 
IO::input(vector<Graph*>& gs)
{
	char c1, c2;
	int id0, id1, id2, lb;
	Graph* graph = NULL;
	Vertex* vertex = NULL;
	Edge* edge = NULL;

	while(true)
	{
		//build vertices and edges frequence
		fscanf(this->ifp, "%c", &c1);
		if(c1 == 't')
		{
			if(graph != NULL)
			{
				gs.push_back(graph);
			}
			fscanf(this->ifp, " %c %d\n", &c2, &id0);
			if(id0 == -1) break;
			graph = new Graph;
			continue;
		}
		else if(c1 == 'v')
		{
			fscanf(this->ifp, " %d %d\n", &id1, &lb);
			vertex = new Vertex(lb);
			graph->vertices.push_back(vertex);
			continue;
		}
		else if(c1 == 'e')
		{
			fscanf(this->ifp, " %d %d %d\n", &id1, &id2, &lb);
			edge = new Edge(id1, id2, lb);
			graph->edges.push_back(edge);
			id0 = graph->edges.size() - 1;
			graph->vertices[id1]->neighbors.push_back(Neighbor(id2, id0));
			graph->vertices[id2]->neighbors.push_back(Neighbor(id1, id0));
			//ensure label order for edge here, notice that both A-B and B-A exists
			if(graph->getVertex1LabelByEdge(id0) > graph->getVertex2LabelByEdge(id0))
			{
				edge->from = id2;
				edge->to = id1;
			}
			continue;
		}
		else 
		{
			cerr<<"ERROR in IO::input() -- invalid char"<<endl;
			exit(1);
		}
	}

	return true;
}

//DEBUG:output redirection not work?
bool 
IO::output(Pattern& p, int frequence)
{
	p.pid = Pattern::current_pid++;
	unsigned xsize = p.frequence();
	//for single vertex, use frequence instead of xsize
	//but no support available
	if(frequence < 0)
		frequence = xsize;

	fprintf(this->ofp, "t # %ld * %d\n", p.pid, xsize);
	//printf("t # %ld * %d\n", p.pid, frequence);
	int vsize = p.vSize();
	int esize = p.eSize();
	vector<Vertex*>& vl = p.vertices;
	vector<Edge*>& el = p.edges;
	int i;
	unsigned j;
	
	for(i = 0; i < vsize; ++i)
	{
		//printf("v %d %d\n", i, vl[i]->label);
		fprintf(this->ofp, "v %d %d\n", i, vl[i]->label);
	}

	for(i = 0; i < esize; ++i)
	{
		//printf("e %d %d %d\n", el[i]->from, el[i]->to, el[i]->label);
		fprintf(this->ofp, "e %d %d %d\n", el[i]->from, el[i]->to, el[i]->label);
	}

	fprintf(this->ofp, "x");
	//printf("x");
	for(j = 0; j < xsize; ++j)
	{
		//printf(" %d", p.support[j]->gid);
		fprintf(this->ofp, " %d", p.support[j]->gid);
	}
	fprintf(this->ofp, "\n");
	//printf("\n");

	//NOTICE:fflush is needed to flush all cached writes to disk
	//do it at last to keep efficience
	//fflush(this->ofp);
	return true;
}

void
IO::flush()
{
	fflush(this->ofp);
}

IO::~IO()
{
	fclose(this->ifp);
	this->ifp = NULL;
	fclose(this->ofp);
	this->ofp = NULL;
}

