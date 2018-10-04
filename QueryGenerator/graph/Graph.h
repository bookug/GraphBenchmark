/*=============================================================================
# Filename: Graph.h
# Author: Bookug Lobert 
# Mail: 1181955272@qq.com
# Last Modified: 2016-10-24 23:00
# Description: 
=============================================================================*/

#ifndef _GRAPH_GRAPH_H
#define _GRAPH_GRAPH_H

#include "../util/Util.h"

class Neighbor
{
public:
	VID vid;
	LABEL elb;
	Neighbor()
	{
		vid = -1;
		elb = -1;
	}
	Neighbor(int _vid, int _elb)
	{
		vid = _vid;
		elb = _elb;
	}
};

class Vertex
{
public:
	//VID id;
	LABEL label;
	//NOTICE:VID and EID is just used in this single graph
	std::vector<Neighbor> in;
	std::vector<Neighbor> out;
	Vertex()
	{
		label = -1;
	}
	Vertex(LABEL lb):label(lb)
	{
	}
};

class Graph
{
public:
	std::vector<Vertex> vertices;
	Graph() { }
	~Graph() { }
	int vSize() const
	{
		return vertices.size();
	}
	void addVertex(LABEL _vlb);
	void addEdge(VID _from, VID _to, LABEL _elb);
};

#endif

