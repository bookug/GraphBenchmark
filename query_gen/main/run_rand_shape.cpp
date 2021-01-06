/*=============================================================================
# Filename: dig.cpp
# Author: Bookug Lobert 
# Mail: 1181955272@qq.com
# Last Modified: 2016-10-24 14:39
# Description: 
=============================================================================*/

#include "../util/Util.h"
#include "../io/IO.h"
#include "../graph/Graph.h"
#include "../match/Match.h"
#include "../patterns/query_patterns.h"

using namespace std;

//NOTICE:a pattern occurs in a graph, then support++(not the matching num in a graph), support/N >= minsup
vector<int> node_list;
vector<int> edge_list;
vector<int> query_list;

int
main(int argc, const char * argv[])
{
	int i, j, k;

	string output = "query";
	if(argc > 4 || argc < 3)
	{
		cerr<<"invalid arguments!"<<endl;
		return -1;
	}
	string data = argv[1];
	string query = argv[2];
	if(argc == 4)
	{
		output = argv[3];
	}

	cerr<<"args all got!"<<endl;
	long t1 = Util::get_cur_time();

	IO io = IO(query, data, output);
	//read query file and keep all queries in memory
	io.input(node_list, edge_list, query_list);
	int qnum = query_list.size();
	
//	cerr<<"input ok!"<<endl;
//	long t2 = Util::get_cur_time();

	Graph* data_graph = NULL;
	while(true)
	{
		if(!io.input(data_graph))
		{
			break;
		}
		cout << "one dataset read done!" << endl;
		for(i = 0; i < qnum; ++i)
		{
			Match m(node_list[i], edge_list[i], query_list[i], data_graph);
			//random walk to find match
            m.match(io);
		}
//        io.output();
		delete data_graph;
	}

//	cerr<<"match ended!"<<endl;
//	long t3 = Util::get_cur_time();

	//output the time for contrast
//	cerr<<"part 1 used: "<<(t2-t1)<<"ms"<<endl;
//	cerr<<"part 2 used: "<<(t3-t2)<<"ms"<<endl;
//	cerr<<"total time used: "<<(t3-t1)<<"ms"<<endl;

	//release all and flush cached writes
	io.flush();

	return 0;
}

