#ifndef PATHFINDING_RENDERABLEGRID_H
#define PATHFINDING_RENDERABLEGRID_H

#include "BaseGrid.h"
#include <cstdlib>
#include <vector>
#include <functional>
#include <SFML/Graphics.hpp>

namespace Grid {
    template <typename NodeType>
    struct RenderableNode : public NodeType {
        using NodeType::NodeType;

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

    template<typename GridType, typename DataHolderNodeType>
    class RenderableGrid : public GridType {
    public:
        void CreateNodes(
                unsigned int& Width,
                unsigned int& Height,
                const RenderableSize2D& ContainerSize,
                std::function<DataHolderNodeType*(const RenderableCoordinates2D& RenderCoordinates, const RenderableSize2D& RenderSize)> CreateDataHolderNode = [](const RenderableCoordinates2D&, const RenderableSize2D&) {return nullptr;}
        );

        virtual RenderableSize2D GetNodeRenderSize(const RenderableSize2D& ContainerSize) const = 0;
        virtual RenderableCoordinates2D GetNodeRenderCoordinates(
                const Coordinates2D& Coordinates,
                const RenderableSize2D& RenderSize
        ) const = 0;

        void Render(sf::RenderWindow *Window);
    };

} // Grid

#include "RenderableGrid.tpp"

#endif //PATHFINDING_RENDERABLEGRID_H
