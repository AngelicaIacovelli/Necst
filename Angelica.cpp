#include <iostream>
#include <boost/math/distributions/poisson.hpp>
#include <boost/graph/graph_traits.hpp>
#include <cstdlib>
#include <unistd.h>
#include <ios>
#include <fstream>
#include <string>

using namespace std;

// Inizio lavorando su grafo non orientato


/* TEMPLATE GENERATE RANDOM GRAPH
Effects: Adds V vertices and E edges, to g. 
Source and target vertices of each edge are randomly choosen. 
If self_edges is false, then no edge will have the same source and targets. */
template <typename MutableGraph, class RandNumGen>
void generate_random_graph
	(MutableGraph& g, 
	typename boost::graph_traits<MutableGraph>::vertices_size_type V,
	typename boost::graph_traits<MutableGraph>::vertices_size_type E,
	RandNumGen& gen,
	bool allow_parallel = true,
	bool self_edges = false);

// Template Adjency Matrix
  template <class G>
  struct AdjacencyMatrix
  {
    typedef typename boost::graph_traits<G>::edge_descriptor edge_descriptor;
    void constraints() {
      p = edge(u, v, g);
    }
    typename boost::graph_traits<G>::vertex_descriptor u, v;
    std::pair<bool, edge_descriptor> p;
    G g;
  };
/*
  // CSR: Unsorted edge list constructors 
  template<typename InputIterator>
  compressed_sparse_row_graph(edges_are_unsorted_t,
                              InputIterator edge_begin, InputIterator edge_end,
                              vertices_size_type numverts,
                              const GraphProperty& prop = GraphProperty());


 // CSR: New sorted edge list constructors (directed only)
  template<typename InputIterator>
  compressed_sparse_row_graph(edges_are_sorted_t,
                              InputIterator edge_begin, InputIterator edge_end,
                              vertices_size_type numverts,
                              edges_size_type numedges = 0,
                              const GraphProperty& prop = GraphProperty());

// Dijkstra                        
template <typename Graph, typename DijkstraVisitor, 
	  typename PredecessorMap, typename DistanceMap,
	  typename WeightMap, typename VertexIndexMap, typename DistanceCompare, typename DistanceWeightCombine, 
	  typename DistanceInfinity, typename DistanceZero>
void dijkstra_shortest_paths_no_color_map
  (const Graph& graph,
   typename graph_traits<Graph>::vertex_descriptor start_vertex, 
   PredecessorMap predecessor_map, DistanceMap distance_map, WeightMap weight_map, 
   VertexIndexMap index_map,
   DistanceCompare distance_compare, DistanceWeightCombine distance_weight_combine,
   DistanceInfinity distance_infinity, DistanceZero distance_zero);
*/

/* process_mem_usage(double &, double &) - takes two doubles by reference,
 attempts to read the system-dependent data for a process' virtual memory
 size and resident set size, and return the results in KB.

 On failure, returns 0.0, 0.0 */

// prototipo della funzione -> definisce interfaccia
void process_mem_usage(double& vm_usage, double& resident_set);


int main()
{
	unsigned long num_nodes;
	unsigned long density; 

	cout<<"Inserire numero di nodi: ";
	cin>> num_nodes;
	cout<<"Inserire il parametro di densita' in percentuale: ";
	cin>> density;

	// Preconditions

	do{
	cout<<"Renserire correttamente il parametro di densita' in percentuale: ";
	cin>> density;
	}while(density>100 || density<0);

	do{
	cout<<"Renserire correttamente il numero di vertici: ";
	cin>> num_nodes;
	}while(num_nodes<=0);

	unsigned long L; // L è il numero di archi che voglio calcolare tramite la densità

// La densità di un grafo semplice (Δ) o non orientato è definita come: Δ = 2L / n(n-1)
// La densità di un grafo (Δ) orientato è definita come: Δ = L / n(n-1)                     
	L = num_nodes*(num_nodes-1)*density/2;   //Caso non direzionato
	unsigned int num_edges; // Rendo intero il numero di archi
	num_edges = L;

// Dichiara grafo g come MutableGraph di boost
// Richiamo funzione Adjency List
//COMPLETARE
// Richiamo funzione Adjency Matrix
//COMPLETARE
// Richiamo funzione CSR 
//COMPLETARE

//Random Generator da passare a generate_random_graph
// Passare al RanGen il seed -> fa sì che esperimento sia ripetibile

//  Richiamo funzione GENERATE A RANDOM GRAPH 
// 
//generate_random_graph(&g, num_nodes, num_edges);  //passo g per indirizzo



auto start = std::chrono::high_resolution_clock::now(); // record start time

// Richiamo Dijkstra 
// COMPLETA

auto stop = std::chrono::high_resolution_clock::now(); // record end time

auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
std::cout << "Tempo impiegato: " << duration.count() << "\u00B5s" <<std::endl;

// Misuro memoria utilizzata:
// https://stackoverflow.com/questions/669438/how-to-get-memory-usage-at-runtime-using-c

using std::cout;
using std::endl;

double vm, rss;
process_mem_usage(vm, rss);
cout << "VM: " << vm << "; RSS: " << rss << endl;

	return 0;

}



// corpo della funzione
void process_mem_usage(double& vm_usage, double& resident_set)
{
   using std::ios_base;
   using std::ifstream;
   using std::string;

   vm_usage     = 0.0;
   resident_set = 0.0;

// 'file' stat seems to give the most reliable results
   //
   ifstream stat_stream("/proc/self/stat",ios_base::in);

   // dummy vars for leading entries in stat that we don't care about
   //
   string pid, comm, state, ppid, pgrp, session, tty_nr;
   string tpgid, flags, minflt, cminflt, majflt, cmajflt;
   string utime, stime, cutime, cstime, priority, nice;
   string O, itrealvalue, starttime;

   // the two fields we want
   //
   unsigned long vsize;
   long rss;

   stat_stream >> pid >> comm >> state >> ppid >> pgrp >> session >> tty_nr
               >> tpgid >> flags >> minflt >> cminflt >> majflt >> cmajflt
               >> utime >> stime >> cutime >> cstime >> priority >> nice
               >> O >> itrealvalue >> starttime >> vsize >> rss; // don't care about the rest

   stat_stream.close();

   long page_size_kb = sysconf(_SC_PAGE_SIZE) / 1024; // in case x86-64 is configured to use 2MB pages
   vm_usage     = vsize / 1024.0;
   resident_set = rss * page_size_kb;
// Sequenza funzioni memoria terminata
}

