#include "Algorithm.h"

namespace PathFinding {
    template<typename GridType, typename NodeType>
    Algorithm<GridType, NodeType>::Algorithm(const GridType *Grid) : m_Grid(Grid) {

    }

    template<typename GridType, typename NodeType>
    bool Algorithm<GridType, NodeType>::IsNodeBlocked(NodeType* Node) const {
        return Node->IsBlocked();
    }
}