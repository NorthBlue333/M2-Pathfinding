#ifndef PATHFINDING_ALGORITHM_H
#define PATHFINDING_ALGORITHM_H

#include <vector>

namespace PathFinding {
    struct Node {
        virtual ~Node() = default;
    };

    template <typename GridType, typename NodeType>
    class Algorithm {
    public:
        explicit Algorithm(const GridType* Grid);
        virtual ~Algorithm() = default;

        virtual std::vector<NodeType*> GetPath(NodeType* Start, NodeType* Target) = 0;

        virtual bool IsNodeBlocked(NodeType* Node) const;
    protected:
        const GridType* m_Grid;
    };
}

#include "Algorithm.tpp"

#endif //PATHFINDING_ALGORITHM_H
