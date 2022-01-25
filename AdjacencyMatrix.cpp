#include "headers.h"

// Funzione utilizzo memoria
void process_mem_usage(unsigned long& vm_usage, unsigned long& resident_set, bool diff);
unsigned long vm;
unsigned long rss = 0;

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
    process_mem_usage(vm, rss, 0);

// Creo Grafo 
    Graph g(edges_array.begin(), edges_array.end(), weights_array, num_nodes);

    // Utilizzo Memoria 1 
    process_mem_usage(vm, rss, 1);
    std::cout << std::fixed << "Memory usage: " << rss << " kB" << std::endl;
    
// Genero descrittori vertici e distance map    
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

    // Calcolo e stampo tempo di esecuzione
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);  
    std::cout << "Duration Dijkstra: " << duration.count() << "\u00B5s" << std::endl; // \u00B5s : Character 'MICRO SIGN'

// Johnson
    // Alloco Distance Matrix
    int **D = (int**)malloc(sizeof(int*)*num_nodes);
    for (int i = 0; i < num_nodes; i++) 
        D[i] = (int*)malloc(sizeof(int)*num_nodes);
    
    // Avvio misurazione tempo
    start = std::chrono::high_resolution_clock::now();   

    // Eseguo Johnson
    johnson_all_pairs_shortest_paths(g, D, distance_map(&d[0]));

    // Stop tempo
    stop = std::chrono::high_resolution_clock::now();

    // Calcolo e stampo tempo di esecuzione
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);  
    std::cout << "Duration Johnson: " << duration.count() << "\u00B5s" << std::endl; // \u00B5s : Character 'MICRO SIGN'


    return 0;

}


// resident set size (RSS) is the portion of memory occupied by a process that is held in main memory (RAM).

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