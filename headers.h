#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <ios>
#include <fstream>
#include <string>
#include <chrono>
#include <vector>

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/adjacency_matrix.hpp>
#include <boost/graph/compressed_sparse_row_graph.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/dijkstra_shortest_paths_no_color_map.hpp>

using namespace std;