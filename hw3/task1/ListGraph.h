//
// Created by dmitry on 25.05.22.
//

#ifndef UNTITLED_LISTGRAPH_H
#define UNTITLED_LISTGRAPH_H

#include "IGraph.h"
#include <cassert>

class ListGraph: public IGraph
{
public:
    ListGraph(int size);

    ListGraph(const IGraph &graph);

    ~ListGraph();

    void AddEdge(int from, int to) override;

    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;

    std::vector<int> GetPrevVertices(int vertex) const override;

private:
    std::vector<std::vector<int>> adjacencyLists;
};

#endif //UNTITLED_LISTGRAPH_H
