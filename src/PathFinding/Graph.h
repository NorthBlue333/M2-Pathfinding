#pragma once
#include <functional>
#include <vector>

#include "Node.h"

namespace PathFinding
{
    class Graph
    {
    public:
        using NodeSet = std::vector<Node*>;
        using HeuristicFunction = std::function<int(Node*, Node*)>;

        Graph() = default;
        explicit Graph(NodeSet nodes, HeuristicFunction heuristic) : nodes(std::move(nodes)), heuristic(std::move(heuristic)) {}

        std::vector<Node*> Path(Node* source, Node* target);

        std::vector<Node*> nodes;
        HeuristicFunction heuristic;
    };
}
