#include "IGraph.h"

class ListGraph : public IGraph {
 public:
    ListGraph(int size);

    ListGraph(const IGraph &graph);

    ~ListGraph();

    void addEdge(int from, int to, int weight) override;

    int VerticesCount() const override;

    std::vector<std::pair<int, int>> GetNextVertices(int vertex) const override;

    std::vector<std::pair<int, int>> GetPrevVertices(int vertex) const override;
    int weight(int to, int from) const override;

 private:
    std::vector<std::vector<std::pair<int, int>>> adjacencyLists;
};