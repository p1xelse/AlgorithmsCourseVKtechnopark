#include "SetGraph.h"

SetGraph::SetGraph(int size) : adjacencySets(size) {}

SetGraph::SetGraph(const IGraph &graph) : adjacencySets(graph.VerticesCount()) {
    for (int i = 0; i < graph.VerticesCount(); i++) {
        for (const auto &el : graph.GetNextVertices(i)) {
            adjacencySets[i].insert(el);
        }
    }
}

SetGraph::~SetGraph() {}

void SetGraph::AddEdge(int from, int to) {
    assert(0 <= from && from < adjacencySets.size());
    assert(0 <= to && to < adjacencySets.size());
    adjacencySets[from].insert(to);
}

int SetGraph::VerticesCount() const { return (int)adjacencySets.size(); }

std::vector<int> SetGraph::GetNextVertices(int vertex) const {
    assert(0 <= vertex && vertex < adjacencySets.size());
    std::vector<int> nextVertices;
    for (const auto &el : adjacencySets[vertex]) {
        nextVertices.push_back(el);
    }

    return nextVertices;
}

std::vector<int> SetGraph::GetPrevVertices(int vertex) const {
    assert(0 <= vertex && vertex < adjacencySets.size());
    std::vector<int> prevVertices;

    for (int i = 0; i < adjacencySets.size(); ++i) {
        if (adjacencySets[i].count(vertex)) {
            prevVertices.push_back(i);
        }
    }
    return prevVertices;
}