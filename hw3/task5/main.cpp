#include <limits.h>

#include <cassert>
#include <deque>
#include <iostream>
#include <queue>
#include <vector>

#include "ListGraph.h"

int primMST(IGraph &graph) {
    using intPait = std::pair<int, int>;
    std::priority_queue<intPait, std::vector<intPait>, std::greater<intPait>>
        pq;

    int beginVertex = 0;

    std::vector<int> key(graph.VerticesCount(), INT_MAX);

    std::vector<int> parent(graph.VerticesCount(), -1);

    std::vector<bool> inMST(graph.VerticesCount(), false);

    pq.push(std::make_pair(0, beginVertex));
    key[beginVertex] = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (inMST[u] == true) {
            continue;
        }

        inMST[u] = true;

        for (auto &el : graph.GetNextVertices(u)) {
            int v = el.first;
            int weight = el.second;

            if (inMST[v] == false && key[v] > weight) {
                key[v] = weight;
                pq.push(std::make_pair(key[v], v));
                parent[v] = u;
            }
        }
    }

    int pathLen = 0;
    for (int i = 1; i < graph.VerticesCount(); ++i)
        pathLen += graph.weight(parent[i], i);

    return pathLen;
}

void task(std::istream &input, std::ostream &output) {
    int countCities, countRoads;
    input >> countCities >> countRoads;

    ListGraph graph(countCities);

    for (int i = 0; i < countRoads; ++i) {
        int from, to, weight;
        input >> from >> to >> weight;

        graph.addEdge(from - 1, to - 1, weight);
    }

    int len = primMST(graph);
    output << len << std::endl;
}

int main() {
    task(std::cin, std::cout);
    return 0;
}