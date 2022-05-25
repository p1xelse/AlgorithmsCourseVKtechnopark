//
// Created by dmitry on 25.05.22.
//

#ifndef UNTITLED_IGRAPH_H
#define UNTITLED_IGRAPH_H

#include <vector>

struct IGraph {
    virtual ~IGraph() {}

    virtual void AddEdge(int from, int to) = 0;
    virtual int VerticesCount() const = 0;

    virtual std::vector<int> GetNextVertices(int vertex) const = 0;
    virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};

#endif  // UNTITLED_IGRAPH_H
