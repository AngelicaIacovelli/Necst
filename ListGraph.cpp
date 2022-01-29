// FACEBOOK GRAPH
#include "headers.h"

// Funzione utilizzo memoria
void process_mem_usage(unsigned long& vm_usage, unsigned long& resident_set, bool diff);
unsigned long vm;
unsigned long rss = 0;

// Creo strutture per Adjacency List
typedef adjacency_list<listS, vecS, directedS, no_property, property<edge_weight_t, int> > Graph;
typedef graph_traits<Graph>::vertex_descriptor vertex_descriptor;
typedef std::pair<int, int> Edge; 
// This class couples together a pair of values, which may be of different types (T1 and T2). 
// The individual values can be accessed through its public members first and second.
// Pairs are a particular case of tuple.

//MAIN
int main() { // Non passo nulla al main.

// Reading the csv lines: https://java2blog.com/read-csv-file-in-cpp/#:~:text=To%20read%20a%20CSV%20file%2C,variable%20as%20its%20second%20argument.

	std::string fname;
	std::cout<<"facebook_combined.csv";
	std::cin>>fname;
 
	std::vector<std::vector<std::string>> content;
	std::vector<std::string> row;
	std::string line, word;
 
	std::fstream file (fname, std::ios::in);
	if(file.is_open())
	{
		while(getline(file, line))
		{
			row.clear();
 
			std::stringstream str(line);
 
			while(getline(str, word, ','))
				row.push_back(word);
			content.push_back(row);
		}
	}
	else
		std::cout<<"Could not open the file\n";
  
  // Fisso numero di nodi 
  int num_nodes = content.size();

  std::vector<Edge> edges_array;
  std::string s1,s2;  
  int e1,e2;
 
	for(int i=0;i<content.size();i++)
	{
		for(int j=0;j<content[i].size();j++)
		{
      if (j = 0) 
      { 
        s1 = content[i][j];
      }
      else
      {
        s2 = content[i][j];
      }
		}
    // Adding adges to the Adjacency List 
    e1 = std::stoi(s1);
    e2 = std::stoi(s2);
    std::vector<Edge> edges_array;
    edges_array.push_back(Edge(e1,e2));

	}

    const int num_edges = edges_array.size();

// Imposto weights tutti uguali
    int *weights_array = (int*)malloc(sizeof(int)*num_edges);
    for(int i = 0; i < num_edges; i++) {
        weights_array[i] = 1;
    }

// Utilizzo Memoria 0  
    process_mem_usage(vm, rss, 0);
    
// Creo Grafo   
    Graph g(edges_array.begin(), edges_array.end(), weights_array, num_nodes);
    
// Utilizzo Memoria 1
    process_mem_usage(vm, rss, 1);
    std::cout << std::fixed << "Memory usage: " << rss << " kB\n" << std::endl;
    
// Genero descrittori vertici e distance map
    std::vector<vertex_descriptor> p(num_vertices(g));
    std::vector < int >d(num_vertices(g), (std::numeric_limits < int >::max)());

// Genero nodo radice
    int V = rand()%(num_nodes-2);
    vertex_descriptor s = vertex(V, g);

// Dijkstra
    // Avvio misurazione tempo
    auto start = std::chrono::high_resolution_clock::now();   
    // Eseguo Dijkstra 
    dijkstra_shortest_paths_no_color_map(g, s,
        predecessor_map(make_iterator_property_map(p.begin(), get(vertex_index, g)))
        .distance_map(make_iterator_property_map(d.begin(), get(vertex_index, g))));
    // Stop tempo
    auto stop = std::chrono::high_resolution_clock::now();

    // Calcolo e stampo tempo di esecuzione
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);  
    std::cout << "Duration Dijkstra: " << duration.count() << "\u00B5s\n" << std::endl; // \u00B5s : Character 'MICRO SIGN'

/*    // Stampo i risultati
    std::cout << "Source vertex: " << V << std::endl;
    std::cout << "Distances and parents:" << std::endl;
    graph_traits < Graph >::vertex_iterator vi, vend;
    for (tie(vi, vend) = vertices(g); vi != vend; ++vi) {
        if (d[*vi] == (std::numeric_limits<int>::max)())
            std::cout << "distance(" << *vi << ") = " << std::setw(7) << "inf, ";
        else
            std::cout << "distance(" << *vi << ") = " << std::setw(5) << d[*vi] << ", ";
        std::cout << "parent(" << *vi << ") = " << p[*vi] << std::endl;
    }
    std::cout << std::endl;
*/



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

/*
    // Stampo i risultati
    std::cout << "       ";
    for (int k = 0; k < num_nodes; ++k)
        std::cout << std::setw(5) << k;
    std::cout << std::endl;
    for (int i = 0; i < num_nodes; ++i) {
        std::cout << std::setw(3) << i << " -> ";
        for (int j = 0; j < num_nodes; ++j) {
            if (D[i][j] == (std::numeric_limits<int>::max)())
                std::cout << std::setw(5) << "inf";
            else
                std::cout << std::setw(5) << D[i][j];
        }
        std::cout << std::endl;
    }
    
    std::ofstream fout("figs/graph.dot");
    fout << "digraph A {\n"
    << "  rankdir=LR\n"
    << "size=\"5,3\"\n"   // %immagine alta 5 e larga 3 pollici (con gdpi definirò densità pixel)
    << "ratio=\"fill\"\n"
    << "edge[style=\"bold\"]\n" << "node[shape=\"circle\"]\n";

    graph_traits < Graph >::edge_iterator ei, ei_end;
    for (boost::tie(ei, ei_end) = edges(g); ei != ei_end; ++ei)
        fout << source(*ei, g) << " -> " << target(*ei, g) 
        << "[label=" << get(edge_weight, g)[*ei] << "]\n";

    fout << "}\n";

*/
    return 0;   

}

void process_mem_usage(unsigned long& vm_usage, unsigned long& resident_set, bool diff)
{
    vm_usage = 0;

    // the two fields we want
    unsigned long vsize;
    unsigned long rss;
    {
        std::string ignore;
        std::ifstream ifs("/proc/self/stat", std::ios_base::in);
        ifs >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore
                >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore
                >> ignore >> ignore >> vsize >> rss;
    }

    long page_size_kb = sysconf(_SC_PAGE_SIZE) / 1024; // in case x86-64 is configured to use 2MB pages
    vm_usage = vsize / 1024.0;
    if(diff == 0){  // stores the rss before creating the graph structure
        resident_set = rss * page_size_kb;
    }
    else{  // calculates the rss of the graph structure by subtracting the old value to the new one
        resident_set = (rss * page_size_kb) - resident_set;
    }
}
