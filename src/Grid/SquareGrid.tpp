#include "SquareGrid.h"

namespace Grid {
    template<template <typename NodeType> typename DataHolderNodeType>
    RenderableCoordinates2D
    RenderableSquareGrid<DataHolderNodeType>::GetNodeRenderCoordinates(const Coordinates2D &Coordinates,
                                                                const RenderableSize2D &RenderSize) const {
        return {
            Coordinates.X * (RenderSize.Width + MARGIN_BETWEEN_NODES),
            Coordinates.Y * (RenderSize.Height + MARGIN_BETWEEN_NODES),
        };
    }

    template<template <typename NodeType> typename DataHolderNodeType>
    RenderableSize2D RenderableSquareGrid<DataHolderNodeType>::GetNodeRenderSize(const RenderableSize2D &ContainerSize) const {
        const auto Size = std::min(
            (ContainerSize.Width - this->m_Width * MARGIN_BETWEEN_NODES) / this->m_Width,
            (ContainerSize.Height - this->m_Height * MARGIN_BETWEEN_NODES) / this->m_Height
        );
        return {
            Size,
            Size,
        };
    }

    template<typename GridNodeType, template <typename NodeType> typename DataHolderNodeType>
    std::vector<Coordinates2D>
    BaseSquareGrid<GridNodeType, DataHolderNodeType>::GetNeighborsCoordinates(Coordinates2D &Coordinates) {
        return {
                // row before
                {Coordinates.X, Coordinates.Y - 1},
                // same row
                {Coordinates.X - 1, Coordinates.Y},
                {Coordinates.X + 1, Coordinates.Y},
                // row after
                {Coordinates.X, Coordinates.Y + 1},
        };
    }
} // Grid