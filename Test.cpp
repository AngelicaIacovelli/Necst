#include "headers.h"

#include <unistd.h>
#include <ios>
#include <iostream>
#include <fstream>
#include <string>

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
}


// Funzione dens 
bool dens(int d) {
    return rand()%100+1 < d; 
}

// Creo strutture per Adjacency Matrix
typedef adjacency_matrix<directedS,
    no_property, property<edge_weight_t, int> > Graph;

typedef graph_traits<Graph>::vertex_descriptor vertex_descriptor;

typedef std::pair<int, int> Edge;

//MAIN 

int main(int argc, char *argv[]) {
/* Cosa passo al main:
argv[] è un vettore dove:
argv[0] = num iterazioni
argv[1] = num_nodes 
argv[2] = density 
argv[3] = seed       */


// fisso numero di nodi 
    const int num_nodes = atoi(argv[1]);
    std::cout << "Number of nodes: " << num_nodes << std::endl;

// fisso il seed
    const int seed = atoi(argv[3]);
    srand(seed);
    std::cout << "Seed: " << seed << std::endl;

// Genero edges
    std::vector<Edge> edges_array;
    const int density = atoi(argv[2]);
    std::cout << "Density: " << density << "%" << std::endl;
   
    for(int i=0; i < num_nodes; i++){
        for(int j=0; j < num_nodes; j++){
            if(dens(density)){
                edges_array.push_back(Edge(i,j));
            }
        }
    }

    const int num_edges = edges_array.size();

// Genero weights
    int *weights_array = (int*)malloc(sizeof(int)*num_edges);

    for(int i = 0; i < num_edges; i++){
        weights_array[i] = rand()%(10) + 1;
    }

    // Utilizzo Memoria 0  
    double vm, rss;
    process_mem_usage(vm, rss);
    double rss0;
    rss0 = rss;

// Creo Grafo 
    Graph g(edges_array.begin(), edges_array.end(), weights_array, num_nodes);

    // Utilizzo Memoria 1 
    process_mem_usage(vm, rss);
    rss = rss - rss0;
    std::cout << std::fixed << "Memory usage: " << rss << " kB" << std::endl;


    std::vector< vertex_descriptor > p(num_vertices(g));
    std::vector< int > d(num_vertices(g));

// Genero nodo radice
    int V = rand()%(num_nodes-2);

    vertex_descriptor s = vertex(V, g);

// Dijkstra

    // Avvio misurazione tempo
    auto start = std::chrono::high_resolution_clock::now();    

    dijkstra_shortest_paths_no_color_map(g, s,
        predecessor_map(make_iterator_property_map(
                            p.begin(), get(vertex_index, g)))
        .distance_map(make_iterator_property_map(
                d.begin(), get(vertex_index, g))));

    // Stop Tempo
    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);  
    std::cout << "Duration Dijkstra: " << duration.count() << "\u00B5s" << std::endl; // \u00B5s : Character 'MICRO SIGN'

    return 0;

}


