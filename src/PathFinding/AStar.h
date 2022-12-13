#ifndef PATHFINDING_ASTAR_H
#define PATHFINDING_ASTAR_H

#include "Algorithm.h"

namespace PathFinding {
    template <typename NodeType>
    // maybe copy coordinates in order to have data in memory? But OriginalNodes are already next to each other?
    struct AStarNode : public Node<NodeType> {
        int G = 0;
        int H = 0;

//        bool Visited = false;
        AStarNode* ParentInPath = nullptr;

        int GetScore() const;

        bool operator ==(const AStarNode<NodeType>& Other);
    };

    template <typename GridType, typename NodeType>
    class AStar : public Algorithm<GridType, NodeType> {
    public:
        std::vector<NodeType*> GetPath(NodeType* Start, NodeType* Target) override;
    };
}

#include "AStar.tpp"

#endif //PATHFINDING_ASTAR_H
