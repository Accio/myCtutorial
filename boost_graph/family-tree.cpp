// Adapted from boost graph library example by Siek, Lumsdaine, and Lee

#include <boost/config.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <boost/graph/adjacency_list.hpp>
#include <boost/tuple/tuple.hpp>

enum family
  { David, Agnes, Levin, Maria, Fabian, Johannes, N};

int main() {
  using namespace boost;
  const char *name[] = {"David", "Agnes", "Levin", "Maria", "Fabian", "Johannes"};
  
  adjacency_list <> g(N); // N is an interesting trick, since N=length(enum) [starting from 0]
  add_edge(David,Agnes, g);
  add_edge(David,Levin, g);
  add_edge(Agnes,Maria, g);
  add_edge(Agnes,Fabian, g);
  add_edge(Levin,Johannes, g);

  graph_traits < adjacency_list<> >::vertex_iterator i, end;
  graph_traits < adjacency_list<> >::adjacency_iterator ai, a_end; // the same iterator concept as out_edge_iterator
  property_map <adjacency_list<>, vertex_index_t >::type index_map = get(vertex_index, g); // use the vertex property 'vertex_index'
  
  for(boost::tie(i, end)=vertices(g); i!=end; ++i) { //boost::tie returns a tuple, i=first, end=last;
    std::cout << name[get(index_map, *i)]; // notice *i is used to get the 
    boost::tie(ai, a_end) = adjacent_vertices(*i, g); // i is an iterator, and *i is the vertex_descriptor
    if(ai==a_end) // test whether *i has no children
      std::cout << " has no children";
    else
      std::cout << " is the parent of ";
    for(; ai!=a_end; ++ai) {
      std::cout << name[get(index_map, *ai)];
      if(boost::next(ai) != a_end)
	std::cout << ", ";
    }
    std::cout << std::endl;
  }
  return EXIT_SUCCESS;
}
