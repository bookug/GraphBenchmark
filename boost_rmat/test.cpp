/*=============================================================================
# Filename: test.c
# Author: bookug 
# Mail: bookug@qq.com
# Last Modified: 2018-10-25 19:32
# Description: 
https://www.boost.org/doc/libs/1_68_0/libs/graph_parallel/doc/html/rmat_generator.html
=============================================================================*/

#include <iostream> 

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/rmat_graph_generator.hpp>
#include <boost/random/linear_congruential.hpp>

using namespace std;

typedef boost::adjacency_list<> Graph;
typedef boost::rmat_iterator<boost::minstd_rand, Graph> RMATGen;

int main()
{
  boost::minstd_rand gen;
  // Create graph with 100 nodes and 400 edges
  Graph g(RMATGen(gen, 100, 400, 0.57, 0.19, 0.19, 0.05), RMATGen(), 100);

  //QUERY: how to output
  //cout<<g<<endl;

  return 0;
}

