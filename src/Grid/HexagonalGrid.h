#ifndef PATHFINDING_HEXAGONALGRID_H
#define PATHFINDING_HEXAGONALGRID_H

#include "BaseGrid.h"
#include "RenderableGrid.h"

namespace Grid {
    struct HexagonalGridCubeCoordinates {
        int Q = 0;
        int R = 0;
        int CalculateS() const;
    };

    template <typename BaseHexagonalGridNodeType, template <typename NodeType> typename DataHolderNodeType>
    struct BaseHexagonalGridNode : public BaseGridNode<BaseHexagonalGridNodeType, DataHolderNodeType> {
        using BaseGridNode<BaseHexagonalGridNodeType, DataHolderNodeType>::BaseGridNode;
    };

    template <template <typename NodeType> typename DataHolderNodeType>
    struct HexagonalGridNode : public BaseHexagonalGridNode<HexagonalGridNode<DataHolderNodeType>, DataHolderNodeType>
    {
        using BaseHexagonalGridNode<HexagonalGridNode<DataHolderNodeType>, DataHolderNodeType>::BaseHexagonalGridNode;
    };

    // use Odd-R coordinates 2D
    template <typename GridNodeType, template <typename NodeType> typename DataHolderNodeType>
    class BaseHexagonalGrid : public BaseGrid<GridNodeType, DataHolderNodeType>
    {
    public:
        BaseHexagonalGrid(
                unsigned int& Width,
                unsigned int& Height,
                std::function<DataHolderNodeType<GridNodeType>*(const Coordinates2D& Coordinates)> CreateDataHolderNode = [](const Coordinates2D&) {return nullptr;}
        ) {
            this->CreateNodes(Width, Height, CreateDataHolderNode);
        };

        int GetRowOffset(const Coordinates2D& Coordinates) const;
        int GetRowOffset(const int& Y) const;

        std::vector<Coordinates2D> GetNeighborsCoordinates(Coordinates2D& Coordinates) override;
    protected:
        explicit BaseHexagonalGrid() = default;
    };

    template <template <typename NodeType> typename DataHolderNodeType>
    using HexagonalGrid = BaseHexagonalGrid<HexagonalGridNode<DataHolderNodeType>, DataHolderNodeType>;

    template <template <typename NodeType> typename DataHolderNodeType>
    using RenderableHexagonalGridNode = RenderableNode<BaseHexagonalGridNode, DataHolderNodeType>;

    template <template <typename NodeType> typename DataHolderNodeType>
    class RenderableHexagonalGrid :
            public RenderableGrid<BaseHexagonalGrid<RenderableHexagonalGridNode<DataHolderNodeType>, DataHolderNodeType>, RenderableHexagonalGridNode<DataHolderNodeType>, DataHolderNodeType>
    {
    public:
        using GridNode_T = RenderableHexagonalGridNode<DataHolderNodeType>;
        using DataHolder_T = DataHolderNodeType<GridNode_T>;

        RenderableHexagonalGrid(
                unsigned int& Width,
                unsigned int& Height,
                const RenderableSize2D& ContainerSize,
                std::function<DataHolderNodeType<GridNode_T >*(GridNode_T* GridNode, const RenderableCoordinates2D& RenderCoordinates, const RenderableSize2D& RenderSize)> CreateDataHolderNode = [](GridNode_T* GridNode, const RenderableCoordinates2D&, const RenderableSize2D&) {return nullptr;}
        ) {
            this->CreateNodes(Width, Height, ContainerSize, CreateDataHolderNode);
        };

        RenderableSize2D GetNodeRenderSize(const RenderableSize2D& ContainerSize) const override;
        RenderableCoordinates2D GetNodeRenderCoordinates(
                const Coordinates2D& Coordinates,
                const RenderableSize2D& RenderSize
        ) const override;
    };

} // Grid

#include "HexagonalGrid.tpp"

#endif //PATHFINDING_HEXAGONALGRID_H
