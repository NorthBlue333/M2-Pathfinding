#include "BaseGrid.h"

namespace Grid {
    template<typename GridNodeType, typename DataHolderNodeType>
    void BaseGrid<GridNodeType, DataHolderNodeType>::CreateNodes(
            unsigned int& Width,
            unsigned int& Height,
            std::function<DataHolderNodeType*(const Coordinates2D& Coordinates)> CreateDataHolderNode
    ) {
        m_Width = Width;
        m_Height = Height;
        m_Nodes = {};
        // if no reserve the program fails as it tries to delete DataHolder
        m_Nodes.reserve(Height * Width);
        for (int Y = 0; Y < Height; ++Y) {
            for (int X = 0; X < Width; ++X) {
                Coordinates2D Coordinates{X, Y};
                m_Nodes.emplace_back(Coordinates, CreateDataHolderNode(Coordinates));
            }
        }
    }

    template<typename GridNodeType, typename DataHolderNodeType>
    std::vector<GridNodeType> const*BaseGrid<GridNodeType, DataHolderNodeType>::GetNodes() const {
        return &m_Nodes;
    }

    template<typename GridNodeType, typename DataHolderNodeType>
    std::size_t BaseGrid<GridNodeType, DataHolderNodeType>::GetIndexFromCoordinates(const Coordinates2D &Coordinates) const {
        return Coordinates.Y * m_Width + Coordinates.X;
    }

    template<typename GridNodeType, typename DataHolderNodeType>
    Coordinates2D BaseGrid<GridNodeType, DataHolderNodeType>::GetCoordinatesFromIndex(const int& Index) const {
        const auto X = Index % m_Width;
        return {X, (Index - X) / m_Width};
    }

    template<typename DataHolderNodeType>
    BaseGridNode<DataHolderNodeType>::BaseGridNode(Coordinates2D &C, DataHolderNodeType *DH) : Coordinates(C), DataHolder(DH) {

    }

    template<typename DataHolderNodeType>
    BaseGridNode<DataHolderNodeType>::~BaseGridNode() {
        delete DataHolder;
    }
} // Grid
