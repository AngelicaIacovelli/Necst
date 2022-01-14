#include <iostream> 
#include <cstdlib> 
#include <unistd.h> 
#include <fstream> 
#include <chrono> 
#include <algorithm> 
#include <vector> 
#include <utility> // per pair
#include <iomanip>
#include <string>
// #include <malloc/_malloc.h>

#include <boost/config.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/adjacency_matrix.hpp>
#include <boost/graph/compressed_sparse_row_graph.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/dijkstra_shortest_paths_no_color_map.hpp>
#include <boost/graph/johnson_all_pairs_shortest.hpp>
#include <boost/graph/graphviz.hpp>

using namespace boost;
