//
// Created by dmitry on 25.05.22.
//

#ifndef UNTITLED_MATRIXGRAPH_H
#define UNTITLED_MATRIXGRAPH_H


#include "IGraph.h"
#include <cassert>

class MatrixGraph: public IGraph
{
public:
    MatrixGraph(int size);

    MatrixGraph(const IGraph &graph);

    ~MatrixGraph();

    void AddEdge(int from, int to) override;

    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;

    std::vector<int> GetPrevVertices(int vertex) const override;

private:
    std::vector<std::vector<int>> adjacencyMatrix;
};


#endif //UNTITLED_MATRIXGRAPH_H
