#include <limits.h>

#include <cassert>
#include <deque>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>

struct IGraph {
    virtual ~IGraph() {}

    virtual void addEdge(int from, int to, int weight) = 0;
    virtual int VerticesCount() const = 0;

    virtual std::vector<std::pair<int, int>> GetNextVertices(
        int vertex) const = 0;
    virtual std::vector<std::pair<int, int>> GetPrevVertices(
        int vertex) const = 0;
};

class ListGraph : public IGraph {
 public:
    ListGraph(int size);

    ListGraph(const IGraph &graph);

    ~ListGraph();

    void addEdge(int from, int to, int weight) override;

    int VerticesCount() const override;

    std::vector<std::pair<int, int>> GetNextVertices(int vertex) const override;

    std::vector<std::pair<int, int>> GetPrevVertices(int vertex) const override;

 private:
    std::vector<std::vector<std::pair<int, int>>> adjacencyLists;
};

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

std::vector<int> Dijkstra(IGraph &graph, int vertex) {
    std::vector<int> pathsLen(graph.VerticesCount(), INT_MAX);
    pathsLen[vertex] = 0;
    using intPait = std::pair<int, int>;
    std::priority_queue<intPait, std::vector<intPait>, std::greater<intPait>>
        pq;

    pq.push(std::make_pair(0, vertex));

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (auto &el : graph.GetNextVertices(u)) {
            int v = el.first;
            int weight = el.second;

            if (pathsLen[v] > pathsLen[u] + weight) {
                pathsLen[v] = pathsLen[u] + weight;
                pq.push(std::make_pair(pathsLen[v], v));
            }
        }
    }

    return pathsLen;
}

void task(std::istream &input, std::ostream &output) {
    int countCities, countRoads;
    input >> countCities >> countRoads;

    ListGraph graph(countCities);

    for (int i = 0; i < countRoads; ++i) {
        int from, to, weight;
        input >> from >> to >> weight;

        graph.addEdge(from, to, weight);
    }

    int from, to;
    input >> from >> to;

    std::vector<int> lens = Dijkstra(graph, from);
    output << lens[to];
}

int main() { task(std::cin, std::cout); }