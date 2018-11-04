/*=============================================================================
# Filename: IO.cpp
# Author: Bookug Lobert 
# Mail: 1181955272@qq.com
# Last Modified: 2016-10-24 22:55
# Description: 
=============================================================================*/

#include "IO.h"

using namespace std;

IO::IO()
{
	this->dfp = NULL;
	this->ofp = NULL;
	this->data_id = -1;
}

IO::IO(string query, string data, string _dir)
{
	this->data_id = -1;
	this->line = "============================================================";
	qfn = query;
	dfp = fopen(data.c_str(), "r");
	if(dfp == NULL)
	{
		cerr<<"input open error!"<<endl;
		return;
	}
//	ofp = fopen(file.c_str(), "w+");
//	if(ofp == NULL)
//	{
//		cerr<<"output open error!"<<endl;
//		return;
//	}
    this->output_directory = _dir;
    Util::create_dir(_dir);
}

Graph* 
IO::input(FILE* fp)
{
	char c1, c2;
	int id0, id1, id2, lb;
	bool flag = false;
	Graph* ng = NULL;

	while(true)
	{
		fscanf(fp, "%c", &c1);
		if(c1 == 't')
		{
			if(flag)
			{
				fseek(fp, -1, SEEK_CUR);
				return ng;
			}
			flag = true;
			fscanf(fp, " %c %d\n", &c2, &id0);
			if(id0 == -1)
			{
				return NULL;
			}
			else
			{
				ng = new Graph;
				int nodeNum, edgeNum, ln1, ln2;
				fscanf(fp, "%d %d %d %d\n",&nodeNum,&edgeNum, &ln1, &ln2);
			}
		}
		else if(c1 == 'v')
		{
			fscanf(fp, " %d %d\n", &id1, &lb);
			ng->addVertex(lb); 
		}
		else if(c1 == 'e')
		{
			fscanf(fp, " %d %d %d\n", &id1, &id2, &lb);
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
IO::input(Graph*& data_graph)
{
	data_graph = this->input(this->dfp);
	if(data_graph == NULL)
		return false;
	this->data_id++;
	return true;
}

bool 
IO::input(vector<int>& node_list, vector<int>& edge_list, vector<int>& query_list)
{
	int queryNodeNum = 0;
	int queryEdgeNum = 0;
    int queryNum = 0;
	std::ifstream ifs(qfn.c_str());
	while (true)
	{
		ifs >> queryNodeNum;
		if (queryNodeNum == -1) {
			break;
		}
		ifs >> queryEdgeNum;
        ifs >> queryNum;
		//cout << queryNodeNum << " to add!" << endl;
		node_list.push_back(queryNodeNum);
		edge_list.push_back(queryEdgeNum);
        query_list.push_back(queryNum);
	}
	ifs.close();
	return true;
}

bool 
IO::output(int qid)
{
	fprintf(ofp, "query graph:%d    data graph:%d\n", qid, this->data_id);
	fprintf(ofp, "%s\n", line.c_str());
	return true;
}

bool
IO::output()
{
	fprintf(ofp, "t # -1\n");
	return true;
}

bool 
IO::output(int* m, int size)
{
	for(int i = 0; i < size; ++i)
	{
		fprintf(ofp, "(%d, %d) ", i, m[i]);
	}
	fprintf(ofp, "\n");
	return true;
}

void
IO::flush()
{
	fflush(this->ofp);
}

IO::~IO()
{
	fclose(this->dfp);
	this->dfp = NULL;
	fclose(this->ofp);
	this->ofp = NULL;
}

