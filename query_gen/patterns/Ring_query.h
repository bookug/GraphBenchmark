#ifndef _RING_QUERY_H
#define _RING_QUERY_H

#include "../util/Util.h"
#include "../graph/Graph.h"

class Ring_query
{
    public:
    
    Ring_query();
    ~Ring_query();
	Ring_query(std::string query_req_path, std::string query_dir);

    //to use previous IO class, need to generate corresponding data
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