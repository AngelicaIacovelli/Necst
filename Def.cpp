#include "headers.h"

//L'input per il terminal sarà: Number of nodes, Density, Seed, Num Iterazioni.

// inizializzo array che conterrà gli output
int r [] = {0, 0, 0, 0, 0, 0};

std::vector<double> results;

// Funzione utilizzo memoria
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
argv[1] = num_nodes 
argv[2] = density 
argv[3] = seed    
argv[4] = num iterazioni  */ 


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

// Fisso numero di iterazioni 
    const int num_it= atoi(argv[4]);
    std::cout << "Number of iterations: " << num_it << std::endl;

// Genero weights
    int *weights = (int*)malloc(sizeof(int)*num_edges);
    std::vector<CsrWeight> weights2;
    CsrWeight random;

    for(int i = 0; i < num_edges; i++){
        random.w = rand()%(10) + 1;     /*A: random è di tipo csr_weight. Se vedo csr_weight è una struct formata solo dal tipo w! quindi scrivendo random.w posso dire a quanto equivale il campo w*/
        weights2.push_back(random);
        weights[i] = random.w;                
    }

// Genero nodo radice
    int V = rand()%(num_nodes-2);

    for(int I=0; I < num_it; I++) {  // Ripeto i comandi N volte ( N = num_it = numero di iterazioni richieste)
        int iteration_counter = I + 1;

        // Utilizzo Memoria 0  
        process_mem_usage(vm, rss, 0);

    // Creo Grafo (Adjacency List)
        list list_g(edges_array.begin(), edges_array.end(), weights, num_nodes);

        // Utilizzo Memoria 1
        process_mem_usage(vm, rss, 1);
        std::cout << std::fixed << "Adjacency List -> Memory usage: " << rss << " kB" << std::endl;
        r[0] = rss;
        
        std::vector< vertex_list > list_p(num_vertices(list_g));
        std::vector< int > list_d(num_vertices(list_g));
        vertex_list list_s = vertex(V, list_g);

    // dijkstra algorithm for list graph   
        
        auto start = std::chrono::high_resolution_clock::now();

        dijkstra_shortest_paths_no_color_map(list_g, list_s,
            predecessor_map(make_iterator_property_map(
                                list_p.begin(), get(vertex_index, list_g)))
            .distance_map(make_iterator_property_map(
                    list_d.begin(), get(vertex_index, list_g))));

        auto stop = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);  
        std::cout << "Duration Dijkstra: " << duration.count() << "\u00B5s" << std::endl; // \u00B5s : Character 'MICRO SIGN'
        r[1] = duration.count();
    
    // Utilizzo Memoria 0  
        process_mem_usage(vm, rss, 0);

    // Creo Grafo (Adjacency Matrix)
        matrix matrix_g(edges_array.begin(), edges_array.end(), weights, num_nodes);

        // Utilizzo Memoria 1 
        process_mem_usage(vm, rss, 1);
        std::cout << std::fixed << "Adjacency Matrix -> Memory usage: " << rss << " kB" << std::endl;
        r[2] = rss;
        
        std::vector< vertex_matrix > matrix_p(num_vertices(matrix_g));
        std::vector< int > matrix_d(num_vertices(matrix_g));

        vertex_matrix matrix_s = vertex(V, matrix_g);

    // Dijkstra

        // Avvio misurazione tempo
        start = std::chrono::high_resolution_clock::now();    

        dijkstra_shortest_paths_no_color_map(matrix_g, matrix_s,
            predecessor_map(make_iterator_property_map(
                                matrix_p.begin(), get(vertex_index, matrix_g)))
            .distance_map(make_iterator_property_map(
                    matrix_d.begin(), get(vertex_index, matrix_g))));

        // Stop Tempo
        stop = std::chrono::high_resolution_clock::now();

        duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);  
        std::cout << "Duration Dijkstra: " << duration.count() << "\u00B5s" << std::endl; // \u00B5s : Character 'MICRO SIGN'
        r[3] = duration.count();
        

    // Utilizzo Memoria 0  
        process_mem_usage(vm, rss, 0);

    // Creo Grafo (Csr)
        csr csr_g(edges_are_unsorted, edges_array.begin(), edges_array.end(), weights2.begin(), num_nodes);

        // Utilizzo memoria 1
        process_mem_usage(vm, rss, 1);
        std::cout << std::fixed << "Csr -> Memory usage: " << rss << " kB" << std::endl;
        r[4] = rss;

        std::vector< vertex_csr > csr_p(num_vertices(csr_g));
        std::vector< int > csr_d(num_vertices(csr_g));
        vertex_csr csr_s = vertex(V, csr_g);

    // Dijkstra 

        // Avvio misurazione tempo
        start = std::chrono::high_resolution_clock::now();    

        dijkstra_shortest_paths_no_color_map(csr_g, csr_s,
            predecessor_map(make_iterator_property_map(
                                csr_p.begin(), get(boost::vertex_index, csr_g))).
            distance_map(make_iterator_property_map(
                    csr_d.begin(), get(vertex_index, csr_g))).
            weight_map(boost::get(&CsrWeight::w, csr_g))
            );

        // Stop tempo
        stop = std::chrono::high_resolution_clock::now();

        duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);  
        std::cout << "Duration Dijkstra: " << duration.count() << "\u00B5s" << std::endl; // \u00B5s : Character 'MICRO SIGN'
        r[5] = duration.count();


        // Salvo i risultati su data.csv 
            std::ifstream myfile;
            myfile.open("data.csv");
            if(myfile) {  // controllo se il csv già esiste: se esiste apro in appendice, altrimenti apro (senza appendice) semplicemente e stampo prima riga
                std::ofstream myfile;
                myfile.close();
                myfile.open ("data.csv",std::ios_base::app);
                myfile << num_nodes << "," << seed << "," << density << "," << iteration_counter << "," << "Adjacency List"   << "," << r[0] << "," << r[1] << "\n" ;
                myfile << num_nodes << "," << seed << "," << density << "," << iteration_counter << "," << "Adjacency Matrix" << "," << r[2] << "," << r[3] << "\n" ;
                myfile << num_nodes << "," << seed << "," << density << "," << iteration_counter << "," << "Csr"              << "," << r[4] << "," << r[5] << "\n" ;
                myfile.close();

            } else {
                std::ofstream myfile;
                myfile.close();
                myfile.open ("data.csv");
                myfile << "Number of nodes,Seed,Density (%),Number of Iteration,Data structure,Memory Usage (kB),Duration Dijkstra (µs),\n";
                myfile << num_nodes << "," << seed << "," << density << "," << iteration_counter << "," << "Adjacency List"   << "," << r[0] << "," << r[1] << "\n" ;
                myfile << num_nodes << "," << seed << "," << density << "," << iteration_counter << "," << "Adjacency Matrix" << "," << r[2] << "," << r[3] << "\n" ;
                myfile << num_nodes << "," << seed << "," << density << "," << iteration_counter << "," << "Csr"              << "," << r[4] << "," << r[5] << "\n" ;
                myfile.close();
            }
    }

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

