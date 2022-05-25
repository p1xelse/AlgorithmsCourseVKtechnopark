#include <cassert>
#include <deque>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>

#include "ArcGraph.h"
#include "IGraph.h"
#include "ListGraph.h"
#include "MatrixGraph.h"
#include "SetGraph.h"

void BFS(const IGraph &graph, int vertex, std::vector<bool> &visited,
         const std::function<void(int)> &func) {
    std::queue<int> qu;
    qu.push(vertex);
    visited[vertex] = true;

    while (!qu.empty()) {
        int currentVertex = qu.front();
        qu.pop();

        func(currentVertex);

        for (int nextVertex : graph.GetNextVertices(currentVertex)) {
            if (!visited[nextVertex]) {
                visited[nextVertex] = true;
                qu.push(nextVertex);
            }
        }
    }
}

void mainBFS(const IGraph &graph, const std::function<void(int)> &func) {
    std::vector<bool> visited(graph.VerticesCount(), false);

    for (int i = 0; i < graph.VerticesCount(); i++) {
        if (!visited[i]) BFS(graph, i, visited, func);
    }
}

void DFS(const IGraph &graph, int vertex, std::vector<bool> &visited,
         const std::function<void(int)> &func) {
    visited[vertex] = true;
    func(vertex);

    for (int nextVertex : graph.GetNextVertices(vertex)) {
        if (!visited[nextVertex]) DFS(graph, nextVertex, visited, func);
    }
}

void mainDFS(const IGraph &graph, const std::function<void(int)> &func) {
    std::vector<bool> visited(graph.VerticesCount(), false);

    for (int i = 0; i < graph.VerticesCount(); i++) {
        if (!visited[i]) DFS(graph, i, visited, func);
    }
}

void topologicalSortInternal(const IGraph &graph, int vertex,
                             std::vector<bool> &visited,
                             std::deque<int> &sorted) {
    visited[vertex] = true;

    for (int nextVertex : graph.GetNextVertices(vertex)) {
        if (!visited[nextVertex])
            topologicalSortInternal(graph, nextVertex, visited, sorted);
    }

    sorted.push_front(vertex);
}

std::deque<int> topologicalSort(const IGraph &graph) {
    std::deque<int> sorted;
    std::vector<bool> visited(graph.VerticesCount(), false);

    for (int i = 0; i < graph.VerticesCount(); i++) {
        if (!visited[i]) topologicalSortInternal(graph, i, visited, sorted);
    }

    return sorted;
}

int main(int argc, const char *argv[]) {
    ListGraph graph(7);
    graph.AddEdge(0, 1);
    graph.AddEdge(0, 5);
    graph.AddEdge(1, 2);
    graph.AddEdge(1, 3);
    graph.AddEdge(1, 5);
    graph.AddEdge(1, 6);
    graph.AddEdge(3, 2);
    graph.AddEdge(3, 4);
    graph.AddEdge(3, 6);
    graph.AddEdge(5, 4);
    graph.AddEdge(5, 6);
    graph.AddEdge(6, 4);

    mainBFS(graph, [](int vertex) { std::cout << vertex << " "; });
    std::cout << std::endl;
    mainDFS(graph, [](int vertex) { std::cout << vertex << " "; });
    std::cout << std::endl;

    std::cout << std::endl;

    ListGraph graph2(graph);
    mainBFS(graph2, [](int vertex) { std::cout << vertex << " "; });
    std::cout << std::endl;
    mainDFS(graph2, [](int vertex) { std::cout << vertex << " "; });
    std::cout << std::endl;

    std::cout << std::endl;

    MatrixGraph matrixGraph(graph2);
    mainBFS(matrixGraph, [](int vertex) { std::cout << vertex << " "; });
    std::cout << std::endl;
    mainDFS(matrixGraph, [](int vertex) { std::cout << vertex << " "; });
    std::cout << std::endl;

    std::cout << std::endl;

    MatrixGraph SetGraph(matrixGraph);
    mainBFS(SetGraph, [](int vertex) { std::cout << vertex << " "; });
    std::cout << std::endl;
    mainDFS(SetGraph, [](int vertex) { std::cout << vertex << " "; });
    std::cout << std::endl;

    std::cout << std::endl;

    ArcGraph arcGraph(SetGraph);
    mainBFS(arcGraph, [](int vertex) { std::cout << vertex << " "; });
    std::cout << std::endl;
    mainDFS(arcGraph, [](int vertex) { std::cout << vertex << " "; });
    std::cout << std::endl;

    std::cout << std::endl;

    return 0;
}
