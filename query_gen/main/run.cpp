/*=============================================================================
# Description: for line query pattern
=============================================================================*/
#include "../util/Util.h"
#include "../io/IO.h"
#include "../io/IO_data.h"
#include "../graph/Graph.h"
#include "../match/Match.h"
#include "../patterns/Query_patterns.h"
#include <iostream>


using namespace std;

//NOTICE:a pattern occurs in a graph, then support++(not the matching num in a graph), support/N >= minsup
vector<int> node_list;
vector<int> edge_list;
vector<int> query_list;

void run_line_query(string _query_req_path,string _query_dir,string _data_path)
{
	Line_query line_query(_query_req_path,_query_dir);
		// fill this three list
	line_query.get_req_list(node_list,edge_list,query_list);
	


	int qnum = query_list.size();
	printf("in query requirement txt, there are %d different requirement\n", qnum);


	//read data graph
	Graph* data_graph = NULL;
	IO_data io_data=IO_data(_data_path);
	
	// can read more than one data graph, and random walk on each graph to generate query
	while(true)
	{
		if(!io_data.get_data_graph(data_graph))
		{
			break;
		}
		cout << "one dataset read done!" << endl;
		
		for(int i = 0; i < qnum; ++i)
		{
			//initialize
			Match m(node_list[i], edge_list[i], query_list[i], data_graph);
			//random walk to find match
			// generate query and put into this dir
			m.match(_query_dir);
		}
		
		
		delete data_graph;
		
	}
}

void run_clique_query(string _query_req_path,string _query_dir, string _data_path)
{
	Clique_query clique_query(_query_req_path,_query_dir);
		// fill this three list
	clique_query.get_req_list(node_list,edge_list,query_list);
	


	int qnum = query_list.size();
	printf("in query requirement txt, there are %d different requirement\n", qnum);


	//read data graph
	Graph* data_graph = NULL;
	IO_data io_data=IO_data(_data_path);
	
	// can read more than one data graph, and random walk on each graph to generate query
	while(true)
	{
		if(!io_data.get_data_graph(data_graph))
		{
			break;
		}
		cout << "one dataset read done!" << endl;
		
		for(int i = 0; i < qnum; ++i)
		{
			//initialize
			Match m(node_list[i], edge_list[i], query_list[i], data_graph);
			//random walk to find match
			// generate query and put into this dir
			m.match(_query_dir);
		}
		
		
		delete data_graph;
		
	}
}

void run_ring_query(string _query_req_path,string _query_dir,string _data_path)
{
	Ring_query ring_query(_query_req_path,_query_dir);
		// fill this three list
	ring_query.get_req_list(node_list,edge_list,query_list);
	

	int qnum = query_list.size();
	printf("in query requirement txt, there are %d different requirement\n", qnum);


	//read data graph
	Graph* data_graph = NULL;
	IO_data io_data=IO_data(_data_path);
	
	// can read more than one data graph, and random walk on each graph to generate query
	while(true)
	{
		if(!io_data.get_data_graph(data_graph))
		{
			break;
		}
		cout << "one dataset read done!" << endl;
		
		for(int i = 0; i < qnum; ++i)
		{
			//initialize
			Match m(node_list[i], edge_list[i], query_list[i], data_graph);
			//random walk to find match
			// generate query and put into this dir
			m.ring_match(_query_dir);
		}
		
		
		delete data_graph;
		
	}
}


int
main(int argc, const char * argv[])
{

	string query_dir = "query";
	if(argc > 5 || argc < 4)
	{
		cerr<<"invalid arguments!"<<endl;
		return -1;
	}
    //data file
	string query_pattern=argv[1];
	string data_path = argv[2];
    //query requirement file
	string query_req_path = argv[3];
	if(argc == 5)
	{
		query_dir = argv[4];
	}

	cerr<<"args all got!"<<endl;
	long t1 = Util::get_cur_time();
    
	//initialize line_query with query requirement

	if(query_pattern=="line")
	{
		run_line_query(query_req_path,query_dir,data_path);
	}
	else if(query_pattern=="clique")
	{
		run_clique_query(query_req_path,query_dir,data_path);
	}
	else if(query_pattern=="ring")
	{
		run_ring_query(query_req_path,query_dir,data_path);
	}

//	cerr<<"match ended!"<<endl;
//	long t3 = Util::get_cur_time();

	//output the time for contrast
//	cerr<<"part 1 used: "<<(t2-t1)<<"ms"<<endl;
//	cerr<<"part 2 used: "<<(t3-t2)<<"ms"<<endl;
//	cerr<<"total time used: "<<(t3-t1)<<"ms"<<endl;

	//release all and flush cached writes
	//io.flush();

	return 0;
}

