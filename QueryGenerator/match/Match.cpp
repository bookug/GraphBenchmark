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
#define MAXSEARCHTIME 50
#define MAXSEARCHTIME2 50
Match::Match(int queryNodeNum, int queryEgdeNum, Graph* _data)
{
	this->data = _data;
	this->qsize = queryNodeNum;
	this->dsize = _data->vSize();
	this->edgeNum = queryEgdeNum;
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
void 
Match::match(int order)
{
	if(qsize > dsize)
	{
		return;
	}
	//cout << "node num is " << qsize << ", edge num is " << edgeNum << endl;
	for (int t = 0; t < MAXSEARCHTIME; t ++) {
		bool queryFound = true;
		std::vector<int> vid;
		std::vector<int> vlabel;
		std::vector<pair<int,int>*> edge;
		std::vector<int> elabel;
		for (int i = 0; i < qsize; i ++)
		{
			if (i == 0) {
				int qid = rand()%dsize;
				vid.push_back(qid);
				vlabel.push_back(data->vertices[qid].label);
				continue;
			}
			for (int t2 = 0; t2 < MAXSEARCHTIME2; t2 ++) {
				bool queryFound2 = true;
				int randForStartId = rand()%i;
				int startId = vid[randForStartId];
				int vertexInSize = data->vertices[startId].in.size();
				int vertexOutSize = data->vertices[startId].out.size();
				int startIdNeighbor = vertexInSize + vertexOutSize;
				int randNum = rand()%startIdNeighbor;
				int nextId;
				if (randNum < vertexInSize) {
					int randPosInNeibList = rand()%vertexInSize;
					nextId = data->vertices[startId].in[randPosInNeibList].vid;
					for (int c = 0; c < i; c ++) {
						if (nextId == vid[i]) {
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
				} else {
					randNum -= vertexInSize;
					int randPosOutNeibList = rand()%vertexOutSize;
					nextId = data->vertices[startId].out[randPosOutNeibList].vid;
					for (int c = 0; c < i; c ++) {
						if (nextId == vid[i]) {
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
			if (!queryFound) {
				break;
			}
		}
		//cout << "minimum graph find!" << endl;
		if (queryFound) {
			int remainEdgeNum = edgeNum + 1 - qsize;
			//cout << "the remainEdge number is " << remainEdgeNum  << endl;
			int added = 0;
			for (int j = 0; j < qsize; j ++) {
				for (int i = 0; i < qsize; i ++) {
					if (j == i)
						continue;
					int src,dst,elb;
					int iID = vid[i], jID = vid[j];
					//cout << "iID is " << iID << ", jID is " << jID << endl;
					bool findInList = false;
					if (myFind(data->vertices[iID].in, jID) != -1) {
						findInList = true;
						src = j;
						dst = i;
						elb = myFind(data->vertices[iID].in, jID);
					} else if (myFind(data->vertices[iID].out, jID) != -1){
						findInList = true;
						src = i;
						dst = j;
						elb = myFind(data->vertices[iID].out, jID);
					}
					//if (findInList) cout << "	find an edge!" << endl;
					if (!findInList) {
					    //cout << "	not find!" << endl;
					    continue;
					}
					bool dupl = false;
					for (int p = 0; p < edge.size(); p ++) {
						if (edge[p]->first == src && edge[p]->second == dst) {
							dupl = true;
							break;
						}
					}
					if (!dupl) {
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

		if (queryFound) {
			//add edge
			cout << "t # " << order << endl;
			cout << qsize << " " << edgeNum << " 10 10" << endl;
			for (int i = 0; i < qsize; i ++)
				cout << "v " << i << " " << vlabel[i] << endl;
			for (int i = 0; i < edge.size(); i ++) 
				cout << "e " << edge[i]->first << " " << edge[i]->second << " " << elabel[i] << endl; 
			cout << "t # -1" << endl;
			for (int i = 0; i < edge.size(); i ++)
				delete  edge[i];
			break;
		}
		if (!queryFound && t == MAXSEARCHTIME-1)
			cout << "After " << MAXSEARCHTIME << " times search, no query matched! "<< endl;
	}

}
