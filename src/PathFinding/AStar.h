#ifndef PATHFINDING_ASTAR_H
#define PATHFINDING_ASTAR_H

#include "Algorithm.h"

namespace PathFinding {
    template <typename NodeType>
    struct AStartNode : public Node<NodeType> {
        int G = 0;
        int H = 0;

        AStartNode* ParentInPath = nullptr;
    };

    template <typename GridType, typename NodeType>
    class AStar : public Algorithm<GridType, NodeType> {
    };
}

#include "Algorithm.tpp"

#endif //PATHFINDING_ASTAR_H
