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
    static int query_count;
	Match(int queryNodeNum, int queryEdgeNum, int queryNum, Graph* _data);
	void match(IO& io);
	void match(std::string _query_dir);
	void ring_match(std::string _query_dir);
	~Match();

private:
	int qsize, dsize;
	Graph* query;
	Graph* data;
	int edgeNum;
    int queryNum;    //generate how many queries in this file

    bool isDuplicate(std::vector<int*>&, std::vector<int>&, std::vector<std::pair<int,int>*>&, std::vector<int>&);
	int get_RandStartId(int _tmp_query_len);
	int get_RingStartId(int _tmp_query_len);
};

#endif

