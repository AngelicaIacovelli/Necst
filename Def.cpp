#include "headers.h"

// Funzioni per la memoria
void process_mem_usage(unsigned long& vm_usage, unsigned long& resident_set, bool diff);
unsigned long vm;
unsigned long rss = 0;

// Funzione dens 
bool dens(int d) {
    return rand()%100+1 < d; 
}

// Creo strutture
typedef std::pair<int, int> Edge; 
// This class couples together a pair of values, which may be of different types (T1 and T2). 
// The individual values can be accessed through its public members first and second.
// Pairs are a particular case of tuple.

// Creo strutture per Adjacency List
typedef adjacency_list<listS, vecS, directedS, no_property, property<edge_weight_t, int> > list;
typedef graph_traits<list>::vertex_descriptor vertex_list;


// Creo strutture per Adjacency Matrix
typedef adjacency_matrix<directedS,no_property, property<edge_weight_t, int> > matrix;    
typedef graph_traits<matrix>::vertex_descriptor vertex_matrix;

// Creo strutture per la CSR
struct CsrWeight{
    int w;
};
typedef compressed_sparse_row_graph <directedS, no_property, CsrWeight> csr;
typedef graph_traits<csr>::vertex_descriptor vertex_csr;

//MAIN

int main(int argc, char *argv[]) { 
/* Cosa passo al main:
argv[] è un vettore dove:
argv[0] = num iterazioni
argv[1] = num_nodes 
argv[2] = density 
argv[3] = seed      */ 


// fisso numero di nodi 
    const int num_nodes = atoi(argv[1]);
    std::cout << "Number of nodes: " << num_nodes << std::endl;

// fisso il seed 
    const int seed = atoi(argv[3]); //atoi convert string to integer
    srand(seed); //srand initialize random number generator
    std::cout << "Seed: " << seed << std::endl;
   
// Genero edges
    std::vector<Edge> edges_array;
    const int density = atoi(argv[2]);
    std::cout << "Density: " << density << "%" << std::endl;

    for(int i=0; i < num_nodes; i++) {
        for(int j=0; j < num_nodes; j++) {
             if(dens(density)){
                    edges_array.push_back(Edge(i,j));
                }  
        }
    }

    const int num_edges = edges_array.size();

// Genero weights
    int *weights = (int*)malloc(sizeof(int)*num_edges);
    std::vector<CsrWeight> weights2;
    weight random;

    for(int i = 0; i < num_edges; i++){
        random.w = rand()%(10) + 1;     /*A: random è di tipo csr_weight. Se vedo csr_weight è una struct formata solo dal tipo w! quindi scrivendo random.w posso dire a quanto equivale il campo w*/
        weights2.push_back(random);
        weights[i] = random.w;                
    }

// Genero nodo radice
    int V = rand()%(num_nodes-2);

    // Utilizzo Memoria 0  
    process_mem_usage(vm, rss, 0);

// Creo Grafo (Adjacency List)
    list list_g(edges_array.begin(), edges_array.end(), weights, num_nodes);

    // Utilizzo Memoria 1
    process_mem_usage(vm, rss, 1);
    std::cout << std::fixed << "Memory usage: " << rss << " kB" << std::endl;
    
    std::vector< vertex_list > list_p(num_vertices(list_g));
    std::vector< int > list_d(num_vertices(list_g));
    vertex_list list_s = vertex(V, list_g);





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