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

    template <typename BaseHexagonalGridNodeType, template <typename NodeType, bool WD> typename DataHolderNodeType, bool WithDiagonals>
    struct BaseHexagonalGridNode : public BaseGridNode<BaseHexagonalGridNodeType, DataHolderNodeType, WithDiagonals> {
        using BaseGridNode<BaseHexagonalGridNodeType, DataHolderNodeType, WithDiagonals>::BaseGridNode;

        bool IsDiagonalFrom(BaseHexagonalGridNodeType *Neighbor) const override;
    };

    template <template <typename NodeType, bool WD> typename DataHolderNodeType, bool WithDiagonals>
    struct HexagonalGridNode : public BaseHexagonalGridNode<HexagonalGridNode<DataHolderNodeType, WithDiagonals>, DataHolderNodeType, WithDiagonals>
    {
        using BaseHexagonalGridNode<HexagonalGridNode<DataHolderNodeType, WithDiagonals>, DataHolderNodeType, WithDiagonals>::BaseHexagonalGridNode;
    };

    // use Odd-R coordinates 2D
    template <typename GridNodeType, template <typename NodeType, bool WD> typename DataHolderNodeType, bool WithDiagonals>
    class BaseHexagonalGrid : public BaseGrid<GridNodeType, DataHolderNodeType, WithDiagonals>
    {
    public:
        BaseHexagonalGrid(
                unsigned int& Width,
                unsigned int& Height,
                std::function<DataHolderNodeType<GridNodeType, WithDiagonals>*(const Coordinates2D& Coordinates)> CreateDataHolderNode = [](const Coordinates2D&) {return nullptr;}
        ) {
            this->CreateNodes(Width, Height, CreateDataHolderNode);
        };

        int GetRowOffset(const Coordinates2D& Coordinates) const;
        int GetRowOffset(const int& Y) const;

        std::vector<Coordinates2D> GetNeighborsCoordinates(Coordinates2D& Coordinates) override;
    protected:
        explicit BaseHexagonalGrid() = default;
    };

    template <template <typename NodeType, bool WD> typename DataHolderNodeType, bool WithDiagonals>
    using HexagonalGrid = BaseHexagonalGrid<HexagonalGridNode<DataHolderNodeType, WithDiagonals>, DataHolderNodeType, WithDiagonals>;

    template <template <typename NodeType, bool WD> typename DataHolderNodeType, bool WithDiagonals>
    using RenderableHexagonalGridNode = RenderableNode<BaseHexagonalGridNode, DataHolderNodeType, WithDiagonals>;

    template <template <typename NodeType, bool WD> typename DataHolderNodeType, bool WithDiagonals>
    class RenderableHexagonalGrid :
            public RenderableGrid<BaseHexagonalGrid<RenderableHexagonalGridNode<DataHolderNodeType, WithDiagonals>, DataHolderNodeType, WithDiagonals>, RenderableHexagonalGridNode<DataHolderNodeType, WithDiagonals>, DataHolderNodeType, WithDiagonals>
    {
    public:
        using GridNode_T = RenderableHexagonalGridNode<DataHolderNodeType, WithDiagonals>;
        using DataHolder_T = DataHolderNodeType<GridNode_T, WithDiagonals>;

        RenderableHexagonalGrid(
                unsigned int& Width,
                unsigned int& Height,
                const RenderableSize2D& ContainerSize,
                std::function<DataHolderNodeType<GridNode_T, WithDiagonals>*(GridNode_T* GridNode, const RenderableCoordinates2D& RenderCoordinates, const RenderableSize2D& RenderSize)> CreateDataHolderNode = [](GridNode_T* GridNode, const RenderableCoordinates2D&, const RenderableSize2D&) {return nullptr;}
        ) {
            this->CreateNodes(Width, Height, ContainerSize, CreateDataHolderNode);
        };

        RenderableSize2D GetGridRenderSize(const RenderableSize2D& ContainerSize) const override;
        RenderableSize2D GetNodeRenderSize(const RenderableSize2D& ContainerSize) const override;
        RenderableCoordinates2D GetNodeRenderCoordinates(
                const Coordinates2D& Coordinates,
                const RenderableSize2D& RenderSize
        ) const override;
    };

} // Grid

#include "HexagonalGrid.tpp"

#endif //PATHFINDING_HEXAGONALGRID_H
