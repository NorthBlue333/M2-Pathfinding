#ifndef PATHFINDING_SQUAREGRID_H
#define PATHFINDING_SQUAREGRID_H

#include "BaseGrid.h"
#include "RenderableGrid.h"

namespace Grid {
    template <typename BaseSquareGridNodeType, template <typename NodeType, bool WD> typename DataHolderNodeType, bool WithDiagonals>
    struct BaseSquareGridNode : public BaseGridNode<BaseSquareGridNodeType, DataHolderNodeType, WithDiagonals> {
        using BaseGridNode<BaseSquareGridNodeType, DataHolderNodeType, WithDiagonals>::BaseGridNode;

        bool IsDiagonalFrom(BaseSquareGridNodeType *Neighbor) const override;
    };

    template <template <typename NodeType, bool WD> typename DataHolderNodeType, bool WithDiagonals>
    struct SquareGridNode : public BaseSquareGridNode<SquareGridNode<DataHolderNodeType, WithDiagonals>, DataHolderNodeType, WithDiagonals>
    {
        using BaseSquareGridNode<SquareGridNode<DataHolderNodeType, WithDiagonals>, DataHolderNodeType, WithDiagonals>::BaseSquareGridNode;
    };

    template <typename GridNodeType, template <typename NodeType, bool WD> typename DataHolderNodeType, bool WithDiagonals>
    class BaseSquareGrid : public BaseGrid<GridNodeType, DataHolderNodeType, WithDiagonals>
    {
    public:
        BaseSquareGrid(
                unsigned int& Width,
                unsigned int& Height,
                std::function<DataHolderNodeType<GridNodeType, WithDiagonals>*(const Coordinates2D& Coordinates)> CreateDataHolderNode = [](const Coordinates2D&) {return nullptr;}
        ) {
            this->CreateNodes(Width, Height, CreateDataHolderNode);
        };

        std::vector<Coordinates2D> GetNeighborsCoordinates(Coordinates2D& Coordinates) override;
    protected:
        explicit BaseSquareGrid() = default;
    };

    template <template <typename NodeType, bool WD> typename DataHolderNodeType, bool WithDiagonals>
    using SquareGrid = BaseSquareGrid<SquareGridNode<DataHolderNodeType, WithDiagonals>, DataHolderNodeType, WithDiagonals>;

    template <template <typename NodeType, bool WD> typename DataHolderNodeType, bool WithDiagonals>
    using RenderableSquareGridNode = RenderableNode<BaseSquareGridNode, DataHolderNodeType, WithDiagonals>;

    template <template <typename NodeType, bool WD> typename DataHolderNodeType, bool WithDiagonals>
    class RenderableSquareGrid :
            public RenderableGrid<BaseSquareGrid<RenderableSquareGridNode<DataHolderNodeType, WithDiagonals>, DataHolderNodeType, WithDiagonals>, RenderableSquareGridNode<DataHolderNodeType, WithDiagonals>, DataHolderNodeType, WithDiagonals>
    {
        static int constexpr MARGIN_BETWEEN_NODES = 1;
    public:
        using GridNode_T = RenderableSquareGridNode<DataHolderNodeType, WithDiagonals>;
        using DataHolder_T = DataHolderNodeType<GridNode_T, WithDiagonals>;

        RenderableSquareGrid(
                unsigned int& Width,
                unsigned int& Height,
                const RenderableSize2D& ContainerSize,
                std::function<DataHolderNodeType<GridNode_T, WithDiagonals>*(GridNode_T* GridNode, const RenderableCoordinates2D& RenderCoordinates, const RenderableSize2D& RenderSize)> CreateDataHolderNode = [](const RenderableCoordinates2D&, const RenderableSize2D&) {return nullptr;}
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

#include "SquareGrid.tpp"

#endif //PATHFINDING_SQUAREGRID_H
