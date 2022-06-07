#include "ListGraph.h"

ListGraph::ListGraph(int size) : adjacencyLists(size) {}

ListGraph::ListGraph(const IGraph &graph)
    : adjacencyLists(graph.VerticesCount()) {
    for (int i = 0; i < graph.VerticesCount(); i++)
        adjacencyLists[i] = graph.GetNextVertices(i);
}

ListGraph::~ListGraph() {}

void ListGraph::addEdge(int from, int to, int weight) {
    assert(0 <= from && from < adjacencyLists.size());
    assert(0 <= to && to < adjacencyLists.size());
    adjacencyLists[from].push_back(std::make_pair(to, weight));
    adjacencyLists[to].push_back(std::make_pair(from, weight));
}

int ListGraph::VerticesCount() const { return (int)adjacencyLists.size(); }

std::vector<std::pair<int, int>> ListGraph::GetNextVertices(int vertex) const {
    assert(0 <= vertex && vertex < adjacencyLists.size());
    std::vector<int> nextVertexes;
    return adjacencyLists[vertex];
}

int ListGraph::weight(int from, int to) const {
    int w = 0;
    for (auto &el : GetNextVertices(from)) {
        if (el.first == to) {
            w = el.second;
        }
    }

    return w;
}

std::vector<std::pair<int, int>> ListGraph::GetPrevVertices(int vertex) const {
    assert(0 <= vertex && vertex < adjacencyLists.size());
    std::vector<std::pair<int, int>> prevVertices;

    for (int from = 0; from < adjacencyLists.size(); from++) {
        for (auto to : adjacencyLists[from]) {
            if (to.first == vertex)
                prevVertices.push_back(std::make_pair(from, to.second));
        }
    }
    return prevVertices;
}