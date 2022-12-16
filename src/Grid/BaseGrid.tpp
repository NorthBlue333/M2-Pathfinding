#include "BaseGrid.h"

namespace Grid {
    template<typename GridNodeType, template <typename NodeType, bool WD> typename DataHolderNodeType, bool WithDiagonals>
    bool BaseGridNode<GridNodeType, DataHolderNodeType, WithDiagonals>::IsBlocked() const {
        return DataHolder->IsBlocked();
    }

    template<typename DataHolderType, typename GridNodeType, bool WithDiagonals>
    bool BaseDataHolderType<DataHolderType, GridNodeType, WithDiagonals>::IsBlocked() const {
        return false;
    }

    template<typename GridNodeType, template <typename NodeType, bool WD> typename DataHolderNodeType, bool WithDiagonals>
    void BaseGrid<GridNodeType, DataHolderNodeType, WithDiagonals>::CreateNodes(
            unsigned int& Width,
            unsigned int& Height,
            std::function<DataHolderNodeType<GridNodeType, WithDiagonals>*(GridNodeType* GridNode, const Coordinates2D& Coordinates)> CreateDataHolderNode
    ) {
        m_Width = Width;
        m_Height = Height;
        m_Nodes = {};
        m_Nodes.reserve(Height * Width);
        for (int Y = 0; Y < Height; ++Y) {
            for (int X = 0; X < Width; ++X) {
                Coordinates2D Coordinates{X, Y};
                m_Nodes.emplace_back(Coordinates, nullptr);
                auto LastEl = &m_Nodes.back();
                LastEl->DataHolder = CreateDataHolderNode(&LastEl, Coordinates);
                LastEl->DataHolder->Node = LastEl;
            }
        }
        GenerateNeighbors();
    }

    template<typename GridNodeType, template <typename NodeType, bool WD> typename DataHolderNodeType, bool WithDiagonals>
    std::vector<GridNodeType> const*BaseGrid<GridNodeType, DataHolderNodeType, WithDiagonals>::GetNodes() const {
        return &m_Nodes;
    }

    template<typename GridNodeType, template <typename NodeType, bool WD> typename DataHolderNodeType, bool WithDiagonals>
    GridNodeType *
    BaseGrid<GridNodeType, DataHolderNodeType, WithDiagonals>::GetNodeAtCoordinates(const Coordinates2D &Coordinates) {
        return &m_Nodes[GetIndexFromCoordinates(Coordinates)];
    }

    template<typename GridNodeType, template <typename NodeType, bool WD> typename DataHolderNodeType, bool WithDiagonals>
    std::size_t BaseGrid<GridNodeType, DataHolderNodeType, WithDiagonals>::GetIndexFromCoordinates(const Coordinates2D &Coordinates) const {
        return Coordinates.Y * m_Width + Coordinates.X;
    }

    template<typename GridNodeType, template <typename NodeType, bool WD> typename DataHolderNodeType, bool WithDiagonals>
    Coordinates2D BaseGrid<GridNodeType, DataHolderNodeType, WithDiagonals>::GetCoordinatesFromIndex(const int& Index) const {
        const auto X = Index % m_Width;
        return {X, (Index - X) / m_Width};
    }

    template<typename GridNodeType, template <typename NodeType, bool WD> typename DataHolderNodeType, bool WithDiagonals>
    BaseGridNode<GridNodeType, DataHolderNodeType, WithDiagonals> &BaseGridNode<GridNodeType, DataHolderNodeType, WithDiagonals>::operator=(GridNodeType&& other) {
        DataHolder = other.DataHolder;
        other.DataHolder = nullptr;
        Coordinates = other.Coordinates;
        Neighbors = other.Neighbors;
        return *this;
    }

    template<typename GridNodeType, template <typename NodeType, bool WD> typename DataHolderNodeType, bool WithDiagonals>
    std::vector<GridNodeType *> BaseGridNode<GridNodeType, DataHolderNodeType, WithDiagonals>::GetAdditionalNeighbors() const {
        return DataHolder->GetAdditionalNeighbors();
    }

    template<typename GridNodeType, template <typename NodeType, bool WD> typename DataHolderNodeType, bool WithDiagonals>
    BaseGridNode<GridNodeType, DataHolderNodeType, WithDiagonals>::BaseGridNode(Coordinates2D &C, DataHolderNodeType<GridNodeType, WithDiagonals> *DH) : Coordinates(C), DataHolder(DH) {

    }

    template<typename GridNodeType,template <typename NodeType, bool WD> typename DataHolderNodeType, bool WithDiagonals>
    BaseGridNode<GridNodeType, DataHolderNodeType, WithDiagonals>::~BaseGridNode() {
        delete DataHolder;
    }

    template<typename GridNodeType, template <typename NodeType, bool WD> typename DataHolderNodeType, bool WithDiagonals>
    std::vector<Coordinates2D> BaseGrid<GridNodeType, DataHolderNodeType, WithDiagonals>::GetNeighborsCoordinates(GridNodeType &Node) {
        return GetNeighborsCoordinates(Node.Coordinates);
    }

    template<typename GridNodeType, template <typename NodeType, bool WD> typename DataHolderNodeType, bool WithDiagonals>
    void BaseGrid<GridNodeType, DataHolderNodeType, WithDiagonals>::GenerateNeighbors() {
        for (auto & Node : m_Nodes) {
            Node.Neighbors = {};
            for (auto & NeighborCoordinates : GetNeighborsCoordinates(Node)) {
                if (!IsInMap(NeighborCoordinates))
                    continue;

                Node.Neighbors.push_back(&m_Nodes[GetIndexFromCoordinates(NeighborCoordinates)]);
            }
            for (auto & AdditionalNeighbor : Node.GetAdditionalNeighbors()) {
                Node.Neighbors.push_back(AdditionalNeighbor);
            }
        }
    }

    template<typename GridNodeType, template <typename NodeType, bool WD> typename DataHolderNodeType, bool WithDiagonals>
    bool BaseGrid<GridNodeType, DataHolderNodeType, WithDiagonals>::IsInMap(Coordinates2D &Coordinates) const {
        return Coordinates.X >= 0 && Coordinates.X < m_Width && Coordinates.Y >= 0 && Coordinates.Y < m_Height;
    }
} // Grid
