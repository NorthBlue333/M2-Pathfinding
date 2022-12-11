#ifndef PATHFINDING_SQUAREGRID_H
#define PATHFINDING_SQUAREGRID_H

#include "BaseGrid.h"
#include "RenderableGrid.h"

namespace Grid {
    template <typename DataHolderNodeType>
    struct BaseSquareGridNode : public BaseGridNode<DataHolderNodeType> {
        using BaseGridNode<DataHolderNodeType>::BaseGridNode;
    };

    template <typename GridNodeType, typename DataHolderNodeType>
    class BaseSquareGrid : public BaseGrid<GridNodeType, DataHolderNodeType>
    {
    public:
        BaseSquareGrid(
                unsigned int& Width,
                unsigned int& Height,
                std::function<DataHolderNodeType*(const Coordinates2D& Coordinates)> CreateDataHolderNode = [](const Coordinates2D&) {return nullptr;}
        ) : BaseGrid<GridNodeType, DataHolderNodeType>(Width, Height, CreateDataHolderNode) {};
    protected:
        explicit BaseSquareGrid() = default;
    };

    template <typename DataHolderNodeType>
    using SquareGrid = BaseSquareGrid<BaseSquareGridNode<DataHolderNodeType>, DataHolderNodeType>;

    template <typename DataHolderNodeType>
    using RenderableSquareGridNode = RenderableNode<BaseSquareGridNode<DataHolderNodeType>>;

    template <typename DataHolderNodeType>
    class RenderableSquareGrid : public RenderableGrid<BaseSquareGrid<RenderableSquareGridNode<DataHolderNodeType>, DataHolderNodeType>, DataHolderNodeType>
    {
    public:
        RenderableSquareGrid(
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

#include "SquareGrid.tpp"

#endif //PATHFINDING_SQUAREGRID_H
