#include <iostream>
#include <boost/math/distributions/poisson.hpp>

using namespace std;

// Inizio lavorando su grafo non orientato

int main()
{
    unsigned long num_nodes;
    unsigned long density; 
    
    cout<<"Inserire numero di nodi: ";
    cin>> num_nodes;
    cout<<"Inserire il parametro di densita' in percentuale: ";
    cin>> density;


/* GENERATE A RANDOM GRAPH
    template <typename MutableGraph, class RandNumGen>
  void generate_random_graph
    (MutableGraph& g, 
     typename graph_traits<MutableGraph>::vertices_size_type V,
     typename graph_traits<MutableGraph>::vertices_size_type E,
     RandNumGen& gen,
     bool allow_parallel = true,
     bool self_edges = false);

     Effects: Adds V vertices and E edges, to g. Source and target vertices of each edge are randomly choosen. If self_edges is false, then no edge will have the same source and targets.

Precondition: num_vertices(g) == 0
Compleixity: O(V*E)
*/
   unsigned long L; // L è il numero di archi che voglio calcolare tramite la densità
/* La densità di un grafo semplice (Δ) o non orientato è definita come: Δ = 2L / n(n-1)
La densità di un grafo (Δ) orientato è definita come: Δ = L / n(n-1)                      */
   L = num_nodes*(num_nodes-1)*density/2   //Caso non direzionato
   unsigned int E; // Rendo intero il numero di archi
   E = L;
   

    template <typename MutableGraph, class RandNumGen>
  void generate_random_graph
    (MutableGraph& g, 
     typename graph_traits<MutableGraph>::vertices_size_type num_nodes,
     typename graph_traits<MutableGraph>::vertices_size_type E,
     RandNumGen& gen,
     bool allow_parallel = true,
     bool self_edges = false);





// NB: Ricordati di aggiungere preconditions righe:29