/*
Represent a graph of city using adjacency matrix /adjacency list. Nodes should represent the various landmarks and links should represent the distance between them. Find the shortest path using
Dijkstra's algorithm from single source to all destination.
*/

#include <iostream>
#include <vector>
#include <climits>
using namespace std;

class Graph {
public:
    int V;
    vector<vector<int>> adjMatrix;

    Graph(int v) {
        V = v;
        adjMatrix.resize(V, vector<int>(V, INT_MAX));
    }

    void addEdge(int u, int v, int weight) {
        adjMatrix[u][v] = weight;
        adjMatrix[v][u] = weight;
    }

    void dijkstra(int source) {
        vector<int> dist(V, INT_MAX);
        dist[source] = 0;
        vector<bool> sptSet(V, false);

        for (int count = 0; count < V - 1; count++) {
            int u = minDistance(dist, sptSet);
            sptSet[u] = true;

            for (int v = 0; v < V; v++) {
                if (!sptSet[v] && adjMatrix[u][v] != INT_MAX && dist[u] != INT_MAX && dist[u] + adjMatrix[u][v] < dist[v]) {
                    dist[v] = dist[u] + adjMatrix[u][v];
                }
            }
        }

        printSolution(dist);
    }

    int minDistance(vector<int>& dist, vector<bool>& sptSet) {
        int min = INT_MAX, min_index;
        for (int v = 0; v < V; v++) {
            if (!sptSet[v] && dist[v] <= min) {
                min = dist[v];
                min_index = v;
            }
        }
        return min_index;
    }

    void printSolution(vector<int>& dist) {
        cout << "Shortest distances from source:" << endl;
        for (int i = 0; i < V; i++) {
            cout << "Landmark " << i << " : " << dist[i] << endl;
        }
    }
};

int main() {
    Graph g(5);
    g.addEdge(0, 1, 10);
    g.addEdge(0, 3, 5);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 3, 2);
    g.addEdge(2, 4, 4);
    g.addEdge(3, 1, 3);
    g.addEdge(3, 2, 9);
    g.addEdge(3, 4, 2);
    g.addEdge(4, 0, 7);

    int source = 0;
    g.dijkstra(source);

    return 0;
}
