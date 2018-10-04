/*=============================================================================
# Filename: Match.h
# Author: Bookug Lobert 
# Mail: 1181955272@qq.com
# Last Modified: 2016-10-24 22:55
# Description: find all subgraph-graph mappings between query graph and data graph
=============================================================================*/

#ifndef _MATCH_MATCH_H
#define _MATCH_MATCH_H

#include "../util/Util.h"
#include "../graph/Graph.h"
#include "../io/IO.h"

class Match
{
public:
	Match(int queryNodeNum, int queryEdgeNum, Graph* _data);
	void match(int order);
	~Match();

private:
	int qsize, dsize;
	Graph* query;
	Graph* data;
	int edgeNum;
	
};

#endif

