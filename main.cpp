#include <iostream>
#include <vector>
#include <queue>
#include <chrono>
#include <random>
#include <algorithm>

class Graph {
private:
    int vertices;
    std::vector<std::vector<int>> adjacencyList;
    std::mt19937 rng;

public:
    Graph(int v) : vertices(v), adjacencyList(v), rng(std::random_device()()) {}

    void addEdge(int source, int destination) {
        adjacencyList[source].push_back(destination);
        adjacencyList[destination].push_back(source);
    }

    void generateRandomGraph(double probability) {
        std::uniform_real_distribution<> dist(0, 1);
        for (int i = 0; i < vertices; i++) {
            for (int j = i + 1; j < vertices; j++) {
                if (dist(rng) < probability) {
                    addEdge(i, j);
                }
            }
        }
    }

    void dfsRecursive(int startVertex) {
        std::vector<bool> visited(vertices, false);
        dfsUtil(startVertex, visited);
    }

    void dfsUtil(int vertex, std::vector<bool>& visited) {
        visited[vertex] = true;
        for (int neighbor : adjacencyList[vertex]) {
            if (!visited[neighbor]) {
                dfsUtil(neighbor, visited);
            }
        }
    }

    void bfsIterative(int startVertex) {
        std::vector<bool> visited(vertices, false);
        std::queue<int> q;

        visited[startVertex] = true;
        q.push(startVertex);

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            for (int neighbor : adjacencyList[current]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
    }
};

int main() {
    std::vector<int> networkSizes = {1, 10, 20, 50, 100, 1000, 5000, 10000};
    std::vector<double> dfsTimes, bfsTimes;

    for (int size : networkSizes) {
        Graph graph(size);
        graph.generateRandomGraph(0.1);

        // Measure DFS Time
        auto dfsStart = std::chrono::high_resolution_clock::now();
        graph.dfsRecursive(0);
        auto dfsEnd = std::chrono::high_resolution_clock::now();
        double dfsTime = std::chrono::duration<double>(dfsEnd - dfsStart).count();

        // Measure BFS Time
        auto bfsStart = std::chrono::high_resolution_clock::now();
        graph.bfsIterative(0);
        auto bfsEnd = std::chrono::high_resolution_clock::now();
        double bfsTime = std::chrono::duration<double>(bfsEnd - bfsStart).count();

        dfsTimes.push_back(dfsTime);
        bfsTimes.push_back(bfsTime);

        std::cout << "Network Size: " << size << std::endl;
        std::cout << "DFS Time: " << dfsTime << " seconds" << std::endl;
        std::cout << "BFS Time: " << bfsTime << " seconds" << std::endl;
    }

    return 0;
}
