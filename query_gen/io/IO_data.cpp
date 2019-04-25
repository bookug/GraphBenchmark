/*=============================================================================
=============================================================================*/

#include "IO_data.h"

using namespace std;

IO_data::IO_data()
{
	this->data_id=-1;
	this->data_ptr=NULL;
	this->segreg_line="============================================================";
}

IO_data::IO_data(std::string _data_path)
{
	this->data_id=-1;
	this->segreg_line="============================================================";
	this->data_ptr=fopen(_data_path.c_str(),"r");
	if(this->data_ptr == NULL)
	{
		cerr<<"data file open error!"<<endl;
		return;
	}
}

bool IO_data::get_data_graph(Graph*& _data_graph)
{
	_data_graph = this->input(this->data_ptr);
	if(_data_graph == NULL)
		return false;
	// a new data graph read
	this->data_id++;
	return true;
}

Graph* 
IO_data::input(FILE* _fp)
{
	char c1, c2;
	int id0, id1, id2, lb;
	bool flag = false;
	Graph* ng = NULL;

	while(true)
	{
		fscanf(_fp, "%c", &c1);
		if(c1 == 't')
		{
			if(flag)
			{
				fseek(_fp, -1, SEEK_CUR);
				return ng;
			}
			flag = true;
			fscanf(_fp, " %c %d\n", &c2, &id0);
			if(id0 == -1)
			{
				return NULL;
			}
			else
			{
				ng = new Graph;
				int nodeNum, edgeNum, ln1, ln2;
				fscanf(_fp, "%d %d %d %d\n",&nodeNum,&edgeNum, &ln1, &ln2);
			}
		}
		else if(c1 == 'v')
		{
			fscanf(_fp, " %d %d\n", &id1, &lb);
			ng->addVertex(lb); 
		}
		else if(c1 == 'e')
		{
			fscanf(_fp, " %d %d %d\n", &id1, &id2, &lb);
			//NOTICE:we treat this graph as directed, each edge represents two
			//This may cause too many matchings, if to reduce, only add the first one
			ng->addEdge(id1, id2, lb);
	//		ng->addEdge(id2, id1, lb);
		}
		else 
		{
			cerr<<"ERROR in input() -- invalid char"<<endl;
			return false;
		}
	}
	return NULL;
}



bool 
IO_data::output(int qid)
{
	fprintf(this->output_ptr, "query graph:%d    data graph:%d\n", qid, this->data_id);
	fprintf(this->output_ptr, "%s\n", this->segreg_line.c_str());
	return true;
}

bool
IO_data::output()
{
	//this query ended
	fprintf(this->output_ptr, "t # -1\n");
	return true;
}

bool 
IO_data::output(int* m, int size)
{
	for(int i = 0; i < size; ++i)
	{
		fprintf(this->output_ptr, "(%d, %d) ", i, m[i]);
	}
	fprintf(this->output_ptr, "\n");
	return true;
}

void
IO_data::flush()
{
	fflush(this->output_ptr);
}

IO_data::~IO_data()
{
	if(this->data_ptr!=NULL)
	{
		fclose(this->data_ptr);
		this->data_ptr=NULL;		
	}

    if(this->output_ptr != NULL)
    {
        //NOTICE: fclose(NULL) will cause error, while fflush(NULL) is ok
        fclose(this->output_ptr);
        this->output_ptr = NULL;
    }
}

