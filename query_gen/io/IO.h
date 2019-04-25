/*=============================================================================
# Filename: IO.h
# Author: Bookug Lobert 
# Mail: 1181955272@qq.com
# Last Modified: 2016-10-24 22:55
# Description: 
=============================================================================*/

#ifndef _IO_IO_H
#define _IO_IO_H

#include "../util/Util.h"
#include "../graph/Graph.h"

class IO
{
public:
	IO();
	IO(std::string query, std::string data, std::string file);
	bool input(std::vector<int>& node_list, std::vector<int>& edge_list, std::vector<int>& query_list);
	bool input(Graph*& data_graph);
	Graph* input(FILE* fp);
	bool output(int qid);
	bool output();
	bool output(int* m, int size);
	void flush();
	~IO();
    FILE* getOFP() const
    {
        return this->ofp;
    }
    std::string getOutputDIR() const
    {
        return this->output_directory;
    }

private:
	std::string line;
	int data_id;
	//query file pointer
	std::string qfn;
	//data file pointer
	FILE* dfp;
	//output file pointer
	FILE* ofp;
    std::string output_directory;
};

#endif

