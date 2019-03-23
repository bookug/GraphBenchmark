#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/rmat_graph_generator.hpp>
#include <boost/random/linear_congruential.hpp>
#include <boost/graph/graph_traits.hpp>
#include <iostream>

typedef boost::adjacency_list<> Graph;
typedef boost::rmat_iterator<boost::minstd_rand, Graph> RMATGen;
// typedef boost::graph_traits<Graph>::vertices_size_type size_type;

int main()
{
  boost::minstd_rand gen;
  // Create graph with 100 nodes and 400 edges
  Graph g(RMATGen(gen, 100, 400, 0.57, 0.19, 0.19, 0.05), RMATGen(), 100);
  //print all vertex
  std::cout<<"print all vertices:"<<std::endl;
  boost::graph_traits<Graph>::vertex_iterator vi, vi_end;
  for(boost::tie(vi, vi_end) = vertices(g); vi != vi_end; ++vi)
      std::cout<<*vi<<std::endl;
  boost::graph_traits<Graph>::edge_iterator ei, ei_end;
  for (boost::tie(ei, ei_end) = edges(g); ei != ei_end; ++ei)
  {
    std::cout << "(" << source(*ei, g)<< "," << target(*ei, g)<< ") ";
    std::cout << std::endl;
  }


  //print adjacency vertices of a vertex u
  // std::cout<<"print adjacency vertices of a vertex u"<<std::endl;

  // size_type u=1;
  // boost::graph_traits<Graph>::adjacency_iterator vi, vi_end;
  //   for(boost::tie(vi, vi_end) = adjacent_vertices(u, g); vi != vi_end; ++vi)
  //       std::cout<<*vi<<std::endl;

  return 0;
}