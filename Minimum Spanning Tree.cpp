/*
Represent a graph of your college campus using adjacency list /adjacency matrix. Nodes should
represent the various departments/institutes and links should represent the distance between them.
Find minimum spanning tree
a) Using Kruskal’s algorithm.
b) Using Prim’s algorithm.
*/
#include <iostream>
#include <vector>
#include <algorithm>
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

    void printMST(const vector<int>& parent) {
        for (int i = 1; i < V; i++) {
            cout << "Department " << i << " -> Department " << parent[i] << " with distance " << adjMatrix[i][parent[i]] << endl;
        }
    }

    void kruskalMST() {
        vector<pair<int, pair<int, int>>> edges;
        for (int i = 0; i < V; i++) {
            for (int j = i + 1; j < V; j++) {
                if (adjMatrix[i][j] != INT_MAX) {
                    edges.push_back({adjMatrix[i][j], {i, j}});
                }
            }
        }
        sort(edges.begin(), edges.end());
        vector<int> parent(V), rank(V, 0);
        for (int i = 0; i < V; i++) parent[i] = i;

        int mstWeight = 0;
        vector<int> mstParent(V);
        for (auto& edge : edges) {
            int u = edge.second.first;
            int v = edge.second.second;
            int w = edge.first;

            while (parent[u] != u) u = parent[u];
            while (parent[v] != v) v = parent[v];

            if (u != v) {
                mstWeight += w;
                parent[u] = v;
                mstParent[u] = v;
            }
        }

        cout << "Kruskal's MST:" << endl;
        printMST(mstParent);
    }

    void primMST() {
        vector<int> key(V, INT_MAX), parent(V, -1);
        vector<bool> mstSet(V, false);
        key[0] = 0;

        for (int count = 0; count < V - 1; count++) {
            int minKey = INT_MAX, u;
            for (int v = 0; v < V; v++) {
                if (!mstSet[v] && key[v] < minKey) {
                    minKey = key[v];
                    u = v;
                }
            }
            mstSet[u] = true;
            for (int v = 0; v < V; v++) {
                if (adjMatrix[u][v] != INT_MAX && !mstSet[v] && adjMatrix[u][v] < key[v]) {
                    key[v] = adjMatrix[u][v];
                    parent[v] = u;
                }
            }
        }

        cout << "Prim's MST:" << endl;
        printMST(parent);
    }
};

int main() {
    Graph g(5);
    g.addEdge(0, 1, 2);
    g.addEdge(0, 3, 6);
    g.addEdge(1, 2, 3);
    g.addEdge(1, 3, 8);
    g.addEdge(1, 4, 5);
    g.addEdge(2, 4, 7);
    g.addEdge(3, 4, 9);

    g.kruskalMST();
    cout << endl;
    g.primMST();

    return 0;
}
