/*=============================================================================
# Filename: Match.cpp
# Author: Bookug Lobert 
# Mail: 1181955272@qq.com
# Last Modified: 2016-12-15 01:38
# Description: 
=============================================================================*/

#include "Match.h"
#include <utility>

using namespace std;

#define MAXSEARCHTIME 10000
#define MAXSEARCHTIME2 10000

int Match::query_count = 0;

Match::Match(int queryNodeNum, int queryEgdeNum, int queryNum, Graph* _data)
{
	this->data = _data;
	this->qsize = queryNodeNum;
	this->dsize = _data->vSize();
	this->edgeNum = queryEgdeNum;
    this->queryNum = queryNum;
}

Match::~Match()
{

}

int myFind(std::vector<Neighbor>& list,  int value) {
	vector<Neighbor>::iterator it;
	int elb = -1;
	for (it = list.begin(); it != list.end(); it ++) {
		if (it->vid == value) {
			elb = it->elb;
			break;
		}
	}
	return elb;
}

struct sortEdges{
	int src;
	int dst;
	int label;
	bool operator < (const sortEdges& e)const{
		return src < e.src || (src == e.src && dst < e.dst);
	}
};

bool 
Match::isDuplicate(std::vector<int*>& query_set, vector<int>& vlabel, std::vector<std::pair<int,int>*>& edges, std::vector<int>& elabel)
{
    int* record = new int[qsize+3*edgeNum];
    for(int i = 0; i < qsize; ++i)
    {
        record[i] = vlabel[i];
    }
    for (int i = 0, pos = qsize; i < edges.size(); i ++, pos+=3) 
    {
        record[pos] = edges[i]->first;
        record[pos+1] = edges[i]->second;
        record[pos+2] = elabel[i];
    }
	//cout  << "sizeof(struct) is " << sizeof(sortEdges) << endl;
    //QUERY: no alignment in sortEdges? 12 bytes instead of 16 bytes?
	sort((sortEdges*)(record+qsize),(sortEdges*)(record+qsize+3*edgeNum));
	bool dupl = true;
	if (query_set.size() == 0) {
		query_set.push_back(record);
		cout<<"a result found"<<endl;
		return false;
	}
	for (int r = 0; r < query_set.size(); r ++) {
		dupl = true;
		for (int i = 0; i < qsize+3*edgeNum; i++) {
			if(record[i] != query_set[r][i]) {
				dupl = false;
				break;
			}
		}
		if(dupl == true)
			break;
	}
	if (dupl) {
		delete [] record;
		return true;
	}
    cout<<"a result found"<<endl;
    query_set.push_back(record);
    return false;
}

void 
Match::match(IO& io)
{
//    cout<<"check sortEdges: "<<sizeof(sortEdges)<<endl;
	if(qsize > dsize)
	{
		return;
	}
	//cout << "node num is " << qsize << ", edge num is " << edgeNum << endl;
    //NOTICE: duplicate queries generated can only occur in a specific (node num, edge num) pair
    vector<int*> query_set;

    //BETTER: use goto here instead of nested break
    for(int qq = 0; qq < this->queryNum; ++qq)
    {
        //NOTICE: srand is needed to produce random number, otherwise every time the number sequence generated will be the same
        srand((unsigned)time(NULL)); 
        //NOTICE: the searching is based on random rather than dfs, which is not strictly in random
        for (int t = 0; t < MAXSEARCHTIME; t ++) 
        {
            bool queryFound = true;
            std::vector<int> vid;
            std::vector<int> vlabel;
            std::vector<pair<int,int>*> edge;
            std::vector<int> elabel;
            for (int i = 0; i < qsize; i ++)
            {
                //random select a mapping of the first query node
                if (i == 0) 
                {
                    int qid = rand()%dsize;
                    vid.push_back(qid);
                    vlabel.push_back(data->vertices[qid].label);
                    continue;
                }
                for (int t2 = 0; t2 < MAXSEARCHTIME2; t2 ++) 
                {
                    bool queryFound2 = true;
                    int randForStartId = rand()%i;
                    //random select a known node to expand
                    int startId = vid[randForStartId];
                    int vertexInSize = data->vertices[startId].in.size();
                    int vertexOutSize = data->vertices[startId].out.size();
                    int startIdNeighbor = vertexInSize + vertexOutSize;
                    int randNum = rand()%startIdNeighbor;
                    int nextId;
                    if (randNum < vertexInSize) 
                    {
                        int randPosInNeibList = rand()%vertexInSize;
                        nextId = data->vertices[startId].in[randPosInNeibList].vid;
                        for (int c = 0; c < i; c ++) 
                        {
                            if (nextId == vid[c]) 
                            {
                                queryFound2 = false;
                                break;
                            }
                        }
                        if (!queryFound2)
                            continue;
                        vid.push_back(nextId);
                        vlabel.push_back(data->vertices[nextId].label);
                        pair<int,int> * tmpPairPtr = new pair<int,int>(i,randForStartId);
                        edge.push_back(tmpPairPtr);
                        elabel.push_back(data->vertices[startId].in[randPosInNeibList].elb);
                    } 
                    else 
                    {
    //					randNum -= vertexInSize;
                        int randPosOutNeibList = rand()%vertexOutSize;
                        nextId = data->vertices[startId].out[randPosOutNeibList].vid;
                        for (int c = 0; c < i; c ++) 
                        {
                            if (nextId == vid[c]) 
                            {
                                queryFound2 = false;
                                break;
                            }
                        }
                        if (!queryFound2)
                            continue;
                        vid.push_back(nextId);
                        vlabel.push_back(data->vertices[nextId].label);
                        pair<int,int> * tmpPairPtr = new pair<int,int>(randForStartId,i);
                        edge.push_back(tmpPairPtr);
                        elabel.push_back(data->vertices[startId].out[randPosOutNeibList].elb);
                    }
                    if (queryFound2)
                        break;
                    if (t2 == MAXSEARCHTIME2 - 1)
                        queryFound = false;
                }
                if (!queryFound) 
                    break;
            }
            //cout << "minimum graph find!" << endl;

            if (queryFound) 
            {
                int remainEdgeNum = edgeNum + 1 - qsize;
                //cout << "the remainEdge number is " << remainEdgeNum  << endl;
                int added = 0;
                for (int j = 0; j < qsize; j ++) 
                {
                    for (int i = 0; i < qsize; i ++) 
                    {
                        if (j == i)
                            continue;
                        int src,dst,elb;
                        int iID = vid[i], jID = vid[j];
                        //cout << "iID is " << iID << ", jID is " << jID << endl;
                        bool findInList = false;
                        if (myFind(data->vertices[iID].in, jID) != -1) 
                        {
                            findInList = true;
                            src = j;
                            dst = i;
                            elb = myFind(data->vertices[iID].in, jID);
                        } 
                        else if (myFind(data->vertices[iID].out, jID) != -1)
                        {
                            findInList = true;
                            src = i;
                            dst = j;
                            elb = myFind(data->vertices[iID].out, jID);
                        }
                        //if (findInList) cout << "	find an edge!" << endl;
                        if (!findInList) 
                        {
                            //cout << "	not find!" << endl;
                            continue;
                        }
                        bool dupl = false;
                        for (int p = 0; p < edge.size(); p ++) 
                        {
                            if (edge[p]->first == src && edge[p]->second == dst) 
                            {
                                dupl = true;
                                break;
                            }
                        }
                        if (!dupl) 
                        {
                            pair<int,int> * tmpPairPtr = new pair<int,int>(src, dst);
                            edge.push_back(tmpPairPtr);
                            elabel.push_back(elb);
                            added ++ ;
                        }
                        //cout << "	an edge added!" << endl;
                        if (added >= remainEdgeNum) 
                            break;
                    }
                    if (added >= remainEdgeNum)
                        break;
                }
                if (added < remainEdgeNum)
                    queryFound = false;
            }

            if (queryFound) 
            {
//                cout<<"to check duplicates"<<endl;
                //check if duplicates
                if(isDuplicate(query_set, vlabel, edge, elabel))
                {
                    continue;
                }

                //output the query graph
                string file = io.getOutputDIR() + "/q" + Util::int2string(Match::query_count) + ".g";
                FILE* ofp = fopen(file.c_str(), "w+");

                fprintf(ofp, "t # %d\n", Match::query_count);
                query_count++;
                fprintf(ofp, "%d %d 10 10\n", qsize, edgeNum);
                for (int i = 0; i < qsize; i ++)
                {
                    fprintf(ofp, "v %d %d\n", i, vlabel[i]);
                }
                for (int i = 0; i < edge.size(); i ++) 
                {
                    fprintf(ofp, "e %d %d %d\n", edge[i]->first, edge[i]->second, elabel[i]);
                }

                fprintf(ofp, "t # -1\n");
                fclose(ofp);

                for (int i = 0; i < edge.size(); i ++)
                    delete  edge[i];
				edge.clear();
                break;
            }
			if (!queryFound) {
				for (int i = 0; i < edge.size(); i ++)
					delete  edge[i];
				edge.clear();
			}
            if (!queryFound && t == MAXSEARCHTIME-1)
                cout << "After " << MAXSEARCHTIME << " times search, no query matched! "<< endl;
        }
    }

    for(int i = 0; i < query_set.size(); ++i)
    {
        delete[] query_set[i];
    }
}

