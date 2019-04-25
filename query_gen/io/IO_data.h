/*=============================================================================
io data file, create data graph
=============================================================================*/

#ifndef _IO_DATA_H
#define _IO_DATA_H

#include "../util/Util.h"
#include "../graph/Graph.h"

class IO_data
{
public:

	IO_data();
	IO_data(std::string _data_path);
	~IO_data();

	bool get_data_graph(Graph*& _data_graph);
	Graph* input(FILE* _fp);
	bool output(int _qid);
	bool output();
	bool output(int* _m, int _size);
	void flush();

    FILE* getOFP() const
    {
        return this->output_ptr;
    }


private:
	std::string segreg_line;
	//graph id
	int data_id;
	//data file pointer
	FILE* data_ptr;

	//not used
	FILE* output_ptr;

	
};

#endif


