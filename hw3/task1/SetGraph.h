//
// Created by dmitry on 25.05.22.
//

#ifndef UNTITLED_SETGRAPH_H
#define UNTITLED_SETGRAPH_H


#include "IGraph.h"
#include <cassert>
#include <set>

class SetGraph: public IGraph
{
public:
    SetGraph(int size);

    SetGraph(const IGraph &graph);

    ~SetGraph();

    void AddEdge(int from, int to) override;

    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;

    std::vector<int> GetPrevVertices(int vertex) const override;

private:
    std::vector<std::set<int>> adjacencySets;
};


#endif //UNTITLED_SETGRAPH_H
