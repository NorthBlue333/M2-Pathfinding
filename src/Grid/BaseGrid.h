#ifndef PATHFINDING_BASEGRID_H
#define PATHFINDING_BASEGRID_H

#include <cstdlib>
#include <vector>
#include <functional>

namespace Grid {
    struct Coordinates2D {
        int X = 0;
        int Y = 0;
    };

    template <typename DataHolderNodeType>
    struct BaseGridNode {
        Coordinates2D Coordinates;
        DataHolderNodeType* DataHolder = nullptr;

        BaseGridNode(Coordinates2D& C, DataHolderNodeType* DH);
        virtual ~BaseGridNode();
    };

    // @todo maybe add templated number of nodes for fixed size array instead of vector
    template<typename GridNodeType, typename DataHolderNodeType>
    class BaseGrid {
    public:
        void CreateNodes(
                unsigned int& Width,
                unsigned int& Height,
                std::function<DataHolderNodeType*(const Coordinates2D& Coordinates)> CreateDataHolderNode = [](const Coordinates2D&) {return nullptr;}
        );
        virtual ~BaseGrid() = default;

        std::vector<GridNodeType> const* GetNodes() const;
    protected:
        unsigned int m_Width = 0;
        unsigned int m_Height = 0;

        std::vector<GridNodeType> m_Nodes;

        std::size_t GetIndexFromCoordinates(const Coordinates2D& Coordinates) const;
        Coordinates2D GetCoordinatesFromIndex(const int& Index) const;

        explicit BaseGrid() = default;
    };

} // Grid

#include "BaseGrid.tpp"

#endif //PATHFINDING_BASEGRID_H
