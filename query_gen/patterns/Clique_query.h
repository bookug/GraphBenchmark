#ifndef CLIQUE_QUERY_H
#define CLIQUE_QUERY_H

#include "../util/Util.h"
#include "../graph/Graph.h"

class Clique_query
{
    public:

    Clique_query();

    ~Clique_query();
    Clique_query(std::string _query_req_path, std::string _query_dir);

    bool get_req_list(std::vector<int>& node_list, std::vector<int>& edge_list, std::vector<int>& query_list);



    private:

    std::string segreg_line;
	//query file pointer
	std::string query_req_path;
	//output file pointer
	FILE* query_ptr;
    std::string query_dir;
};

#endif