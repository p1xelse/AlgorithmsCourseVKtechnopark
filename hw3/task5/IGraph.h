#include <vector>

struct IGraph {
    virtual ~IGraph() {}

    virtual void addEdge(int from, int to, int weight) = 0;
    virtual int VerticesCount() const = 0;

    virtual std::vector<std::pair<int, int>> GetNextVertices(
        int vertex) const = 0;
    virtual std::vector<std::pair<int, int>> GetPrevVertices(
        int vertex) const = 0;

    virtual int weight(int to, int from) const = 0;
};