#include "Clique_query.h"

Clique_query::Clique_query()
{
	this->query_ptr = NULL;
    this->segreg_line = "============================================================";
}

Clique_query::Clique_query(std::string _query_req_path, std::string _query_dir)
{
	this->segreg_line = "============================================================";
	this->query_req_path=_query_req_path;

    this->query_dir = _query_dir;
    Util::create_dir(_query_dir);
}

Clique_query::~Clique_query()
{
    if(this->query_ptr != NULL)
    {
        //NOTICE: fclose(NULL) will cause error, while fflush(NULL) is ok
        fclose(this->query_ptr);
        this->query_ptr = NULL;
    }
}

bool 
Clique_query::get_req_list(std::vector<int>& node_list, std::vector<int>& edge_list, std::vector<int>& query_list)
{
    std::ifstream query_req_ifs(this->query_req_path.c_str());
	while (true)
	{
        
        int queryNodeNum;
		query_req_ifs >> queryNodeNum;
		if (queryNodeNum <=0) 
        {
			break;
		}

        //clique
	    int queryEdgeNum = queryNodeNum*(queryNodeNum-1)/2;
        int queryNum;
        query_req_ifs >> queryNum;
		node_list.push_back(queryNodeNum);
		edge_list.push_back(queryEdgeNum);
        query_list.push_back(queryNum);
        
        
	}
    query_req_ifs.close();
	return true;
}
