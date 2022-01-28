// FACEBOOK GRAPH
// Adjacency List representation: https://www.programiz.com/dsa/graph-adjacency-list

#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

// Add edge
void addEdge(vector<int> adj[], int s, int d) {
  adj[s].push_back(d);
  adj[d].push_back(s);
}

// Print the graph
void printGraph(vector<int> adj[], int V) {
  for (int d = 0; d < V; ++d) {
    cout << "\n Vertex "
       << d << ":";
    for (auto x : adj[d])
      cout << "-> " << x;
    printf("\n");
  }
}

int main() {
  int V = 5;

  // Create a graph
  vector<int> adj[V];

/*
  // Add edges
  addEdge(adj, 0, 1);
  addEdge(adj, 0, 2);
  addEdge(adj, 0, 3);
  addEdge(adj, 1, 2);
  printGraph(adj, V);  

*/

// https://java2blog.com/read-csv-file-in-cpp/#:~:text=To%20read%20a%20CSV%20file%2C,variable%20as%20its%20second%20argument.

	string fname;
	cout<<"facebook_combined.csv";
	cin>>fname;
 
	vector<vector<string>> content;
	vector<string> row;
	string line, word;
 
	fstream file (fname, ios::in);
	if(file.is_open())
	{
		while(getline(file, line))
		{
			row.clear();
 
			stringstream str(line);
 
			while(getline(str, word, ','))
				row.push_back(word);
			content.push_back(row);
		}
	}
	else
		cout<<"Could not open the file\n";

  string s1,s2;  
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
    e1 = stoi(s1);
    e2 = stoi(s2);
		addEdge(adj, e1, e2);
	}

printGraph(adj, V);

}

