#include "ArcGraph.h"

#include <set>

ArcGraph::ArcGraph(int size) : edges(), count(size) {}

ArcGraph::ArcGraph(const IGraph &graph) : count(graph.VerticesCount()) {
    for (int i = 0; i < graph.VerticesCount(); i++) {
        for (const auto &el : graph.GetNextVertices(i)) {
            edges.push_back(std::make_pair(i, el));
        }
    }
}

ArcGraph::~ArcGraph() {}

void ArcGraph::AddEdge(int from, int to) {
    assert(0 <= from && from < count);
    assert(0 <= to && to < count);
    edges.push_back(std::make_pair(from, to));
    count++;
}

int ArcGraph::VerticesCount() const { return count; }

std::vector<int> ArcGraph::GetNextVertices(int vertex) const {
    assert(0 <= vertex && vertex < count);
    std::vector<int> nextVertices;
    for (const auto &el : edges) {
        if (el.first == vertex) nextVertices.push_back(el.second);
    }

    return nextVertices;
}

std::vector<int> ArcGraph::GetPrevVertices(int vertex) const {
    assert(0 <= vertex && vertex < count);
    std::vector<int> prevVertices;

    for (const auto &el : edges) {
        if (el.second == vertex) prevVertices.push_back(el.first);
    }

    return prevVertices;
}