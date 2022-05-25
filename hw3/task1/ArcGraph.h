//
// Created by dmitry on 25.05.22.
//

#ifndef UNTITLED_ARCGRAPH_H
#define UNTITLED_ARCGRAPH_H


#include "IGraph.h"
#include <cassert>
#include <set>
#include <cstddef>


class ArcGraph: public IGraph
{
public:
    ArcGraph(int size);

    ArcGraph(const IGraph &graph);

    ~ArcGraph();

    void AddEdge(int from, int to) override;

    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;

    std::vector<int> GetPrevVertices(int vertex) const override;

private:
    std::vector<std::pair<int, int>> edges;
    size_t count;
};


#endif //UNTITLED_ARCGRAPH_H
