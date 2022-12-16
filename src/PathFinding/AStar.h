#ifndef PATHFINDING_ASTAR_H
#define PATHFINDING_ASTAR_H

#include "Algorithm.h"
#include <map>

namespace PathFinding {
    template <typename NodeType>
    struct AStarNode : public Node {
        int G = 0;
        int H = 0;

        bool Visited = false;
        NodeType* ParentInPath = nullptr;

        int GetScore() const;
    };

    template <typename GridType, typename NodeType>
    class AStar : public Algorithm<GridType, NodeType> {
    public:
        using Algorithm<GridType, NodeType>::Algorithm;

        std::vector<NodeType*> GetPath(NodeType* Start, NodeType* Target) override;
        AStarNode<NodeType>& GetOrCreateAStarNodeInMap(std::map<NodeType*, AStarNode<NodeType>>& Map, NodeType* Node) const;
    };
}

#include "AStar.tpp"

#endif //PATHFINDING_ASTAR_H
