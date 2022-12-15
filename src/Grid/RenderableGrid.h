#ifndef PATHFINDING_RENDERABLEGRID_H
#define PATHFINDING_RENDERABLEGRID_H

#include "BaseGrid.h"
#include <cstdlib>
#include <vector>
#include <functional>
#include <SFML/Graphics.hpp>

namespace Grid {
    template <
        template <typename NodeType, template <typename NT, bool WD> typename DataHolderNodeType, bool WithDiagonals> typename GridNodeType,
        template <typename NodeType, bool WD> typename DataHolderType,
        bool WithDiagonals
    >
    struct RenderableNode : public GridNodeType<RenderableNode<GridNodeType, DataHolderType, WithDiagonals>, DataHolderType, WithDiagonals> {
        using GridNodeType<RenderableNode<GridNodeType, DataHolderType, WithDiagonals>, DataHolderType, WithDiagonals>::GridNodeType;

        void Render(sf::RenderWindow *Window);
    };

    struct RenderableCoordinates2D {
        unsigned int X = 0.f;
        unsigned int Y = 0.f;
    };
    struct RenderableSize2D {
        unsigned int Width = 0.f;
        unsigned int Height = 0.f;
    };

    template<typename GridType, typename GridNodeType, template <typename NodeType, bool WD> typename DataHolderNodeType, bool WithDiagonals>
    class RenderableGrid : public GridType {
    public:
        void CreateNodes(
                unsigned int& Width,
                unsigned int& Height,
                const RenderableSize2D ContainerSize,
                std::function<DataHolderNodeType<GridNodeType, WithDiagonals>*(GridNodeType* GridNode, const RenderableCoordinates2D& RenderCoordinates, const RenderableSize2D& RenderSize)> CreateDataHolderNode = [](const RenderableCoordinates2D&, const RenderableSize2D&) {return nullptr;}
        );

        virtual RenderableSize2D GetGridRenderSize(const RenderableSize2D& ContainerSize) const = 0;
        virtual RenderableSize2D GetNodeRenderSize(const RenderableSize2D& ContainerSize) const = 0;
        virtual RenderableCoordinates2D GetNodeRenderCoordinates(
                const Coordinates2D& Coordinates,
                const RenderableSize2D& RenderSize
        ) const = 0;

        const RenderableSize2D& GetContainerSize() const;
        void Render(sf::RenderWindow *Window);
    protected:
        RenderableSize2D m_ContainerSize;
    };

} // Grid

#include "RenderableGrid.tpp"

#endif //PATHFINDING_RENDERABLEGRID_H
