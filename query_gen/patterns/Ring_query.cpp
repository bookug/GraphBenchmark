#include "Ring_query.h"
#include<iostream>
using namespace std;


Ring_query::Ring_query()
{
	this->query_ptr = NULL;
    this->segreg_line = "============================================================";
}

Ring_query::Ring_query(std::string _query_req_path, std::string _query_dir)
{
	this->segreg_line = "============================================================";
	this->query_req_path=_query_req_path;

    this->query_dir = _query_dir;
    Util::create_dir(_query_dir);
}

Ring_query::~Ring_query()
{
    if(this->query_ptr != NULL)
    {
        //NOTICE: fclose(NULL) will cause error, while fflush(NULL) is ok
        fclose(this->query_ptr);
        this->query_ptr = NULL;
    }
}

bool 
Ring_query::get_req_list(std::vector<int>& node_list, std::vector<int>& edge_list, std::vector<int>& query_list)
{
    //to generate what kind of query

    std::ifstream query_req_ifs(this->query_req_path.c_str());
	while (true)
	{
        
        int queryNodeNum;
		query_req_ifs >> queryNodeNum;
		if (queryNodeNum <=0) 
        {
			break;
		}

	    int queryEdgeNum = queryNodeNum;
        int queryNum;
        query_req_ifs >> queryNum;
		node_list.push_back(queryNodeNum);
		edge_list.push_back(queryEdgeNum);
        query_list.push_back(queryNum);
        
        
	}
    query_req_ifs.close();
	return true;
}
