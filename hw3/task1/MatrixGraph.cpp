//
// Created by dmitry on 25.05.22.
//

#include "MatrixGraph.h"

MatrixGraph::MatrixGraph(int size)
    : adjacencyMatrix(size, std::vector<int>(size, 0)) {}

MatrixGraph::MatrixGraph(const IGraph &graph)
    : adjacencyMatrix(graph.VerticesCount(),
                      std::vector<int>(graph.VerticesCount())) {
    for (int i = 0; i < graph.VerticesCount(); i++) {
        for (const auto &el : graph.GetNextVertices(i)) {
            adjacencyMatrix[i][el] = 1;
        }
    }
}

MatrixGraph::~MatrixGraph() {}

void MatrixGraph::AddEdge(int from, int to) {
    assert(0 <= from && from < adjacencyMatrix.size());
    assert(0 <= to && to < adjacencyMatrix.size());
    adjacencyMatrix[from][to] = 1;
}

int MatrixGraph::VerticesCount() const { return (int)adjacencyMatrix.size(); }

std::vector<int> MatrixGraph::GetNextVertices(int vertex) const {
    assert(0 <= vertex && vertex < adjacencyMatrix.size());
    std::vector<int> nextVertices;
    for (int i = 0; i < adjacencyMatrix.size(); ++i) {
        if (adjacencyMatrix[vertex][i] == 1) {
            nextVertices.push_back(i);
        }
    }

    return nextVertices;
}

std::vector<int> MatrixGraph::GetPrevVertices(int vertex) const {
    assert(0 <= vertex && vertex < adjacencyMatrix.size());
    std::vector<int> prevVertices;

    for (int i = 0; i < adjacencyMatrix.size(); ++i) {
        if (adjacencyMatrix[i][vertex] == 1) {
            prevVertices.push_back(i);
        }
    }
    return prevVertices;
}