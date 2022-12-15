#include "SquareGrid.h"

namespace Grid {
    template<typename BaseSquareGridNodeType, template <typename NodeType, bool WD> typename DataHolderNodeType, bool WithDiagonals>
    bool
    BaseSquareGridNode<BaseSquareGridNodeType, DataHolderNodeType, WithDiagonals>::IsDiagonalFrom(BaseSquareGridNodeType *Neighbor) const {
        return this->Coordinates.X != Neighbor->Coordinates.X && this->Coordinates.Y != Neighbor->Coordinates.Y;
    }

    template<template <typename NodeType, bool WD> typename DataHolderNodeType, bool WithDiagonals>
    RenderableCoordinates2D
    RenderableSquareGrid<DataHolderNodeType, WithDiagonals>::GetNodeRenderCoordinates(const Coordinates2D &Coordinates,
                                                                const RenderableSize2D &RenderSize) const {
        return {
            Coordinates.X * (RenderSize.Width + MARGIN_BETWEEN_NODES),
            Coordinates.Y * (RenderSize.Height + MARGIN_BETWEEN_NODES),
        };
    }

    template<template <typename NodeType, bool WD> typename DataHolderNodeType, bool WithDiagonals>
    RenderableSize2D RenderableSquareGrid<DataHolderNodeType, WithDiagonals>::GetNodeRenderSize(const RenderableSize2D &ContainerSize) const {
        const auto Size = std::min(
            (ContainerSize.Width - this->m_Width * MARGIN_BETWEEN_NODES) / this->m_Width,
            (ContainerSize.Height - this->m_Height * MARGIN_BETWEEN_NODES) / this->m_Height
        );
        return {
            Size,
            Size,
        };
    }

    template<template <typename NodeType, bool WD> typename DataHolderNodeType, bool WithDiagonals>
    RenderableSize2D RenderableSquareGrid<DataHolderNodeType, WithDiagonals>::GetGridRenderSize(
        const RenderableSize2D &ContainerSize) const {
        const auto NodeSize = GetNodeRenderSize(ContainerSize);
        return {
            (NodeSize.Width + MARGIN_BETWEEN_NODES) * this->m_Width,
            (NodeSize.Height + MARGIN_BETWEEN_NODES) * this->m_Height,
        };
    }

    template<typename GridNodeType, template <typename NodeType, bool WD> typename DataHolderNodeType, bool WithDiagonals>
    std::vector<Coordinates2D>
    BaseSquareGrid<GridNodeType, DataHolderNodeType, WithDiagonals>::GetNeighborsCoordinates(Coordinates2D &Coordinates) {
        std::vector<Coordinates2D> Neighbors = {};
        if constexpr (WithDiagonals) {
            Neighbors.reserve(8);
        } else {
            Neighbors.reserve(4);
        }

        // row before
        if constexpr (WithDiagonals) {
            Neighbors.push_back({Coordinates.X - 1, Coordinates.Y - 1});
        }

        Neighbors.push_back({Coordinates.X, Coordinates.Y - 1});

        if constexpr (WithDiagonals) {
            Neighbors.push_back({Coordinates.X + 1, Coordinates.Y - 1});
        }

        // same row
        Neighbors.push_back({Coordinates.X - 1, Coordinates.Y});
        Neighbors.push_back({Coordinates.X + 1, Coordinates.Y});

        // row after
        if constexpr (WithDiagonals) {
            Neighbors.push_back({Coordinates.X - 1, Coordinates.Y + 1});
        }

        Neighbors.push_back({Coordinates.X, Coordinates.Y + 1});

        if constexpr (WithDiagonals) {
            Neighbors.push_back({Coordinates.X + 1, Coordinates.Y + 1});
        }

        return Neighbors;
    }
} // Grid