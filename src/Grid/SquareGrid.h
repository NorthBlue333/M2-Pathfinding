#ifndef PATHFINDING_SQUAREGRID_H
#define PATHFINDING_SQUAREGRID_H

#include "BaseGrid.h"
#include "RenderableGrid.h"

namespace Grid {
    template <typename BaseSquareGridNodeType, template <typename NodeType> typename DataHolderNodeType>
    struct BaseSquareGridNode : public BaseGridNode<BaseSquareGridNodeType, DataHolderNodeType> {
        using BaseGridNode<BaseSquareGridNodeType, DataHolderNodeType>::BaseGridNode;
    };

    template <template <typename NodeType> typename DataHolderNodeType>
    struct SquareGridNode : public BaseSquareGridNode<SquareGridNode<DataHolderNodeType>, DataHolderNodeType>
    {
        using BaseSquareGridNode<SquareGridNode<DataHolderNodeType>, DataHolderNodeType>::BaseSquareGridNode;
    };

    template <typename GridNodeType, template <typename NodeType> typename DataHolderNodeType>
    class BaseSquareGrid : public BaseGrid<GridNodeType, DataHolderNodeType>
    {
    public:
        BaseSquareGrid(
                unsigned int& Width,
                unsigned int& Height,
                std::function<DataHolderNodeType<GridNodeType>*(const Coordinates2D& Coordinates)> CreateDataHolderNode = [](const Coordinates2D&) {return nullptr;}
        ) {
            this->CreateNodes(Width, Height, CreateDataHolderNode);
        };

        std::vector<Coordinates2D> GetNeighborsCoordinates(Coordinates2D& Coordinates) override;
    protected:
        explicit BaseSquareGrid() = default;
    };

    template <template <typename NodeType> typename DataHolderNodeType>
    using SquareGrid = BaseSquareGrid<SquareGridNode<DataHolderNodeType>, DataHolderNodeType>;

    template <template <typename NodeType> typename DataHolderNodeType>
    using RenderableSquareGridNode = RenderableNode<BaseSquareGridNode, DataHolderNodeType>;

    template <template <typename NodeType> typename DataHolderNodeType>
    class RenderableSquareGrid :
            public RenderableGrid<BaseSquareGrid<RenderableSquareGridNode<DataHolderNodeType>, DataHolderNodeType>, RenderableSquareGridNode<DataHolderNodeType>, DataHolderNodeType>
    {
        static int constexpr MARGIN_BETWEEN_NODES = 1;
    public:
        using GridNode_T = RenderableSquareGridNode<DataHolderNodeType>;
        using DataHolder_T = DataHolderNodeType<GridNode_T>;

        RenderableSquareGrid(
                unsigned int& Width,
                unsigned int& Height,
                const RenderableSize2D& ContainerSize,
                std::function<DataHolderNodeType<GridNode_T>*(GridNode_T* GridNode, const RenderableCoordinates2D& RenderCoordinates, const RenderableSize2D& RenderSize)> CreateDataHolderNode = [](const RenderableCoordinates2D&, const RenderableSize2D&) {return nullptr;}
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
