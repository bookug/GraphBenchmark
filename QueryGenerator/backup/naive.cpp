/*=============================================================================
# Filename: run.cpp
# Author: Bookug Lobert 
# Mail: zengli-bookug@pku.edu.cn
# Last Modified: 2018-06-25 20:27
# Description: 
1. generate a connected undirected graph first
2. then change it to directed graph, with edge labels and vertex labels(begin from 1, 10 in total, 20/80 rule)
3. run and pick the useful one (those queries with answer num > 0)
//
//self circle is not produced, as well as a 2-ele circle
//
//NOTICE: this generator can not ensure that answer exists for this query!
//A better straetegy is to generate from the data graph, which is called random walk 
//The first straetegy generates one query set for all data graphs, but the latter generates one query set only for one data graph
//(i.e. data graph specific/based)
=============================================================================*/

#include <iostream>
#include <stdio.h> 
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <iomanip>

#define MAX 1000

using namespace std;

int a[MAX][MAX];        //adjancency matrix of graph
int b[MAX];             //degree of each vertex
int label[MAX];         //label of each vertex
bool visit[MAX],ff=true;    //record if this vertex is visited already
int euler[MAX],ans[MAX];     //Euler road
int m,n;    //m is the num of vertices, n is the num of edges
int c[MAX][MAX];    //record if this edge is visited

void randcreat();   //generate a undirected graph randomly
void DFS(int x);    //finish a depth-first search on the undirected graph
bool judge_connect();       //judge if this undirected graph is a connected graph
int judge_euler();     //judge if it has an Euler road
void find_euler(int x,int y);     //begin from x, to find if there exists an Euler road

void clearmap()
{
    ff=true;
    memset(b,0,MAX*sizeof(int));
    memset(euler,-1,MAX*sizeof(int));
    memset(c,0,MAX*sizeof(int));
    for(int i=0;i<m;i++)
    {
        visit[i]=false;
        for(int j=0;j<m;j++)
        {
            a[i][j]=0;
            c[i][j]=0;
        }
    }
}

//generate labels following 20/80 rule, the labels range from 1 to 10
//1 and 2 consume 80%, while others consume 20%
int generateLabel()
{
	int t = rand() % 10;
	if(t < 8)
	{
		t = t / 4;
		return t+1;
	}
	t = (t-8)*4 + 3;
	int add = rand() % 4;
	return t+add;
}

//add labels for vertices and edges, meanwhile set directed randomly
void transform()
{
    srand(time(0));
	for(int i = 0; i < m; ++i)
	{
		label[i] = generateLabel();
	}
	for(int i = 0; i < m; ++i)
    {
		for(int j = i+1; j < m; ++j)
		{
			if(a[i][j] == 0)
			{
				continue;
			}
			int label = generateLabel();
			if(rand()%2 == 0) //from i to j
			{
				a[i][j] = label;
				a[j][i] = -label;
			}
			else              //from j to i
			{
				a[i][j] = -label;
				a[j][i] = label;
			}
		}
	}

	return; 
}

void output(FILE* fp)
{
	fprintf(fp, "t # 0\n");
	fprintf(fp, "%d %d 10 10\n", m, n);
	for(int i = 0; i < m; ++i)
	{
		fprintf(fp, "v %d %d\n", i, label[i]);
	}
	//int edge_num = 0; 
	for(int i = 0; i < m; ++i)
	{
		for(int j = 0; j < m; ++j)
		{
			if(a[i][j] > 0)
			{
				fprintf(fp, "e %d %d %d\n", i, j, a[i][j]);
				//edge_num++;
			}
		}
	}
	fprintf(fp, "t # -1\n");
	return;
}

//  ./run query_file_name
int main(int argc, const char* argv[])
{
	int query_num = 1000;
	int vertex_num = 6;
	int edge_num = 12;

	string file = "query.g";
	if(argc > 1)
	{
		file = argv[1];
	}
	FILE* fp = fopen(file.c_str(), "w+");
	if(fp == NULL)
	{
		cerr<<"error to open file"<<endl;
		exit(1);
	}

    memset(euler,-1,MAX*sizeof(int));
    while(query_num--)
    {
        //cout<<"please input the number of vertices and edges in order: "<<endl;
        //cin>>m>>n;
		m = vertex_num;
		n = edge_num;
        if(n>(m*(m-1)/2))
        {
            cout<<"the number of edges is too large!"<<endl;
            continue;
        }

        randcreat();
        if(judge_connect())
    		cout<<query_num<<" this is a connected graph"<<endl;
        else
        {
            cout<<"this is not a connected graph"<<endl;
            clearmap();
            continue;
        }

        //for(int i=0;i<m;i++)
            //cout<<" "<<b[i]<<" ";
        //cout<<endl;
        //ff=true;
        //judge_euler();
        /*
        for(int j=0;j<=n;j++)
            cout<<setw(3)<<euler[j];
        cout<<endl;
        */

		//add labels for vertices and edges, meanwhile set directed randomly
		transform();
		//output the graph to file in specified format
		output(fp);

        clearmap();
        //cout<<"***********************"<<endl<<endl;
    }

	fclose(fp);
    return 0;
}

void randcreat()
{
    int ra,rb;      //two random number
    int count=0;    //the number of edges generated currently
    srand(time(0));
    while(count<n)
    {
        ra=rand()%m;
        rb=rand()%m;
        while(ra==rb)
            rb=rand()%m;
        if(!a[ra][rb])
        {
            a[ra][rb]=a[rb][ra]=1;
            count++;
            b[ra]++;
            b[rb]++;
        }
    }
    //for(int i=0;i<m;i++)
    //{
        //for(int j=0;j<m;j++)
            //cout<<"  "<<a[i][j]<<"  ";
        //cout<<endl;
    //}
}

void DFS(int x)
{
    visit[x]=true;
    for(int i=0;i<m;i++)
        if(!visit[i]&&a[x][i])
            DFS(i);
}
bool judge_connect()
{
    DFS(0);
    for(int i=0;i<m;i++)
        if(!visit[i])
            return false;
    return true;
}

//TODO: 欧拉图和半欧拉图可直接由度数判定
//https://blog.csdn.net/gzh1992n/article/details/18567125
int judge_euler()
{
    int first=0;  //记录递归的起点
    int num=0;  //奇数度数结点个数
    for(int i=0;i<m;i++)
        if(b[i]%2)
        {
            first = i;
            num++;
        }
    if(num==1||num>2)
        cout<<"非欧拉图或半欧拉图！"<<endl;
    else
    {
        euler[0]=first;         //euler[]记录结点
        find_euler(first,1);
        if(num==0)
            cout<<"欧拉图"<<endl;
        else
            cout<<"半欧拉图"<<endl;
        for(int k=0;k<=n;k++)
        {
            cout<<setw(3)<<ans[k];
        }
        cout<<endl<<endl;
    }
}
void find_euler(int x,int y)
{
    if(euler[n]!=-1)
    {
        if(ff)
        {
            for(int k=0;k<=n;k++)
                ans[k]=euler[k];
            ff=false;
        }
        return ;
    }
    for(int i=0;i<m;i++)
    {
        if(a[x][i]&&!c[x][i])
        {
            euler[y]=i;
            c[x][i]=c[i][x]=1;
            find_euler(i,y+1);
            if(!ff)     //ff来标记是否需要取消标记如果找到欧拉路直接回退
                return;
            else
                c[x][i]=c[i][x]=0;
        }
    }
}

