#include "headers.h"

// Funzioni per la memoria
void process_mem_usage(unsigned long& vm_usage, unsigned long& resident_set, bool diff);
unsigned long vm;
unsigned long rss = 0;


// Funzione dens 
bool dens(int d) {
    return rand()%100+1 < d; 
}

// Creo strutture per Adjacency List
typedef adjacency_list<listS, vecS, directedS,
    no_property, property<edge_weight_t, int> > Graph;

typedef graph_traits<Graph>::vertex_descriptor vertex_descriptor;

typedef std::pair<int, int> Edge; 
// This class couples together a pair of values, which may be of different types (T1 and T2). 
// The individual values can be accessed through its public members first and second.
// Pairs are a particular case of tuple.


//MAIN

int main(char *input[]) {  
/* Cosa passo al main:
input[] è un vettore dove:
input[1] = num_nodes 
input[2] = density 
input[3] = seed       */

// fisso numero di nodi 
    const int num_nodes = atoi(input[1]);

// fisso il seed 
    const int seed = atoi(input[3]); //atoi convert string to integer
    srand(seed); //srand initialize random number generator
   
// Genero edges
    std::vector<Edge> edges_array;
    const int density = atoi(input[2]);

    for(int i=0; i < num_nodes; i++) {
        for(int j=0; j < num_nodes; j++) {
             if(density(dens)){
                    edges_array.push_back(Edge(i,j));
                }  
        }
    }

    const int num_edges = edge_arrays.size();

// Genero weights
    int *weights_array = (int*)malloc(sizeof(int)*num_edges);

    for(int i = 0; i < num_edges; i++) {
        weights_array[i] = rand()%(10) + 1;
    }

    // Utilizzo Memoria 0  
    process_mem_usage(vm, rss, 0);

// Creo Grafo   
    Graph g(edges_array.begin(), edge_arrays.end(), weights_array, num_nodes);

    // Utilizzo Memoria 1
    process_mem_usage(vm, rss, 1);
    
    
    std::vector<vertex_descriptor> p(num_vertices(g));
    std::vector<int> d(num_vertices(g));

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

    // Stop tempo
    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);  
   
    return 0;   

}

void process_mem_usage(unsigned long& vm_usage, unsigned long& resident_set, bool diff)
{
    vm_usage = 0;
    unsigned long vsize;
    unsigned long rss;
    {
        std::string ignore;
        std::ifstream ifs("/proc/self/stat", std::ios_base::in);
        ifs >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore
                >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore
                >> ignore >> ignore >> vsize >> rss;
    }

    long page_size_kb = sysconf(_SC_PAGE_SIZE) / 1024; 
    vm_usage = vsize / 1024.0;
    if(diff == 0){  
        resident_set = rss * page_size_kb;
    }
    else{  
        resident_set = (rss * page_size_kb) - resident_set;
    }
}