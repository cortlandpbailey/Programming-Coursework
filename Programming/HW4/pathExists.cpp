#include <list>
#include <iostream>
using namespace std;

class Graph{
public:
    int numVertices;
    list<int> *adjLists;
    Graph(int V) {
        adjLists = new list<int>[V];
        numVertices = V;
    }
    ~Graph() { delete[] adjLists; }
    void addEdge(int src, int dest) {
        adjLists[src].push_back(dest);
    }
};

// DFS function for locating nodes in a graph
bool depthFirstSearch(list<int>* adjacentLists, int vertexFrom, int vertexTo, bool visited[]) {
    visited[vertexFrom] = true;             // the array holding already visited nodes, set the previous node equal to true
    if (vertexFrom == vertexTo) {           // if where we came from is where we want to go, return true
        return true;                        
    }
    for (int neighbor : adjacentLists[vertexFrom]) {        // iterate through the adjacent lists using the neighbors iterator
        if (!visited[neighbor]) {                           // if the neighbor is not in the visited list enter the next if
            if (depthFirstSearch(adjacentLists, neighbor, vertexTo, visited)) {         // recursively call DFS with the neighbor as the source node
                return true;                                // if the DFS returns true at any point, the node is in the graph and return true
            }
        }

    }

    return false;       // if the node does not show up in any point of the graph, return false
}

 bool pathExists(Graph& g, int vertexFrom, int vertexTo) {
    bool *visited = new bool[g.numVertices];        // create an array the size the graph for holding visited nodes
    for (int i = 0; i < g.numVertices; i++) {       // init the array to all false
        visited[i] = false;
    }
    bool exists = depthFirstSearch(g.adjLists, vertexFrom, vertexTo, visited);      // search for the node, set exists to true if it can be found, as there is a path. 
    delete[] visited;   // delete dynamic memory
    return exists;
  }
