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

    template <typename DataHolderNodeType>
    struct BaseHexagonalGridNode : public BaseGridNode<DataHolderNodeType> {
        using BaseGridNode<DataHolderNodeType>::BaseGridNode;
    };

    // use Odd-R coordinates 2D
    template <typename GridNodeType, typename DataHolderNodeType>
    class BaseHexagonalGrid : public BaseGrid<GridNodeType, DataHolderNodeType>
    {
    public:
        BaseHexagonalGrid(
                unsigned int& Width,
                unsigned int& Height,
                std::function<DataHolderNodeType*(const Coordinates2D& Coordinates)> CreateDataHolderNode = [](const Coordinates2D&) {return nullptr;}
        ) {
            this->CreateNodes(Width, Height, CreateDataHolderNode);
        };

        int GetRowOffset(const Coordinates2D& Coordinates) const;
        int GetRowOffset(const int& Y) const;

    protected:
        explicit BaseHexagonalGrid() = default;
    };

    template <typename DataHolderNodeType>
    using HexagonalGrid = BaseHexagonalGrid<BaseHexagonalGridNode<DataHolderNodeType>, DataHolderNodeType>;

    template <typename DataHolderNodeType>
    using RenderableHexagonalGridNode = RenderableNode<BaseHexagonalGridNode<DataHolderNodeType>>;

    template <typename DataHolderNodeType>
    class RenderableHexagonalGrid :
            public RenderableGrid<BaseHexagonalGrid<RenderableHexagonalGridNode<DataHolderNodeType>, DataHolderNodeType>, DataHolderNodeType>
    {
    public:
        RenderableHexagonalGrid(
                unsigned int& Width,
                unsigned int& Height,
                const RenderableSize2D& ContainerSize,
                std::function<DataHolderNodeType*(const RenderableCoordinates2D& RenderCoordinates, const RenderableSize2D& RenderSize)> CreateDataHolderNode = [](const RenderableCoordinates2D&, const RenderableSize2D&) {return nullptr;}
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
