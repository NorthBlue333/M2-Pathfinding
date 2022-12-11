#include "BaseGrid.h"

namespace Grid {
    template<typename GridNodeType, template <typename NodeType> typename DataHolderNodeType>
    void BaseGrid<GridNodeType, DataHolderNodeType>::CreateNodes(
            unsigned int& Width,
            unsigned int& Height,
            std::function<DataHolderNodeType<GridNodeType>*(GridNodeType* GridNode, const Coordinates2D& Coordinates)> CreateDataHolderNode
    ) {
        m_Width = Width;
        m_Height = Height;
        m_Nodes = {};
        m_Nodes.reserve(Height * Width);
        for (int Y = 0; Y < Height; ++Y) {
            for (int X = 0; X < Width; ++X) {
                Coordinates2D Coordinates{X, Y};
                m_Nodes.emplace_back(Coordinates, nullptr);
                auto LastEl = m_Nodes.back();
                LastEl.DataHolder = CreateDataHolderNode(&LastEl, Coordinates);
            }
        }
        GenerateNeighbors();
    }

    template<typename GridNodeType, template <typename NodeType> typename DataHolderNodeType>
    std::vector<GridNodeType> const*BaseGrid<GridNodeType, DataHolderNodeType>::GetNodes() const {
        return &m_Nodes;
    }

    template<typename GridNodeType, template <typename NodeType> typename DataHolderNodeType>
    std::size_t BaseGrid<GridNodeType, DataHolderNodeType>::GetIndexFromCoordinates(const Coordinates2D &Coordinates) const {
        return Coordinates.Y * m_Width + Coordinates.X;
    }

    template<typename GridNodeType, template <typename NodeType> typename DataHolderNodeType>
    Coordinates2D BaseGrid<GridNodeType, DataHolderNodeType>::GetCoordinatesFromIndex(const int& Index) const {
        const auto X = Index % m_Width;
        return {X, (Index - X) / m_Width};
    }

    template<typename GridNodeType, template <typename NodeType> typename DataHolderNodeType>
    BaseGridNode<GridNodeType, DataHolderNodeType> &BaseGridNode<GridNodeType, DataHolderNodeType>::operator=(GridNodeType&& other) {
        DataHolder = other.DataHolder;
        other.DataHolder = nullptr;
        Coordinates = other.Coordinates;
        Neighbors = other.Neighbors;
        return *this;
    }

    template<typename GridNodeType, template <typename NodeType> typename DataHolderNodeType>
    std::vector<GridNodeType *> BaseGridNode<GridNodeType, DataHolderNodeType>::GetAdditionalNeighbors() const {
        return DataHolder->GetAdditionalNeighbors();
    }

    template<typename GridNodeType, template <typename NodeType> typename DataHolderNodeType>
    BaseGridNode<GridNodeType, DataHolderNodeType>::BaseGridNode(Coordinates2D &C, DataHolderNodeType<GridNodeType> *DH) : Coordinates(C), DataHolder(DH) {

    }

    template<typename GridNodeType,template <typename NodeType> typename DataHolderNodeType>
    BaseGridNode<GridNodeType, DataHolderNodeType>::~BaseGridNode() {
        delete DataHolder;
    }

    template<typename GridNodeType, template <typename NodeType> typename DataHolderNodeType>
    std::vector<Coordinates2D> BaseGrid<GridNodeType, DataHolderNodeType>::GetNeighborsCoordinates(GridNodeType &Node) {
        return GetNeighborsCoordinates(Node.Coordinates);
    }

    template<typename GridNodeType, template <typename NodeType> typename DataHolderNodeType>
    void BaseGrid<GridNodeType, DataHolderNodeType>::GenerateNeighbors() {
        for (auto & Node : m_Nodes) {
            Node.Neighbors = {};
            for (auto & NeighborCoordinates : GetNeighborsCoordinates(Node)) {
                if (!IsInMap(NeighborCoordinates))
                    continue;

                Node.Neighbors.push_back(&m_Nodes[GetIndexFromCoordinates(NeighborCoordinates)]);
            }
        }
    }

    template<typename GridNodeType, template <typename NodeType> typename DataHolderNodeType>
    bool BaseGrid<GridNodeType, DataHolderNodeType>::IsInMap(Coordinates2D &Coordinates) const {
        return Coordinates.X >= 0 && Coordinates.X < m_Width && Coordinates.Y >= 0 && Coordinates.Y < m_Height;
    }
} // Grid
