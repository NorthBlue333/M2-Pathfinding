#include "HexagonalGrid.h"

namespace Grid {
    template<typename BaseHexagonalGridNodeType, template <typename NodeType, bool WD> typename DataHolderNodeType, bool WithDiagonals>
    bool
    BaseHexagonalGridNode<BaseHexagonalGridNodeType, DataHolderNodeType, WithDiagonals>::IsDiagonalFrom(BaseHexagonalGridNodeType *Neighbor) const {
        // hexa does not have diagonals
        return false;
    }

    template<typename GridNodeType, template <typename NodeType, bool WD> typename DataHolderNodeType, bool WithDiagonals>
    int BaseHexagonalGrid<GridNodeType, DataHolderNodeType, WithDiagonals>::GetRowOffset(const Coordinates2D &Coordinates) const {
        return GetRowOffset(Coordinates.Y);
    }

    template<typename GridNodeType, template <typename NodeType, bool WD> typename DataHolderNodeType, bool WithDiagonals>
    int BaseHexagonalGrid<GridNodeType, DataHolderNodeType, WithDiagonals>::GetRowOffset(const int& Y) const {
        return Y&1;
    }

    template<template <typename NodeType, bool WD> typename DataHolderNodeType, bool WithDiagonals>
    RenderableSize2D RenderableHexagonalGrid<DataHolderNodeType, WithDiagonals>::GetGridRenderSize(
        const RenderableSize2D &ContainerSize) const {
        const auto NodeSize = GetNodeRenderSize(ContainerSize);
        return {
            // +1 for row offset
            NodeSize.Width * this->m_Width + 1,
            NodeSize.Height * this->m_Height,
        };
    }

    template<template <typename NodeType, bool WD> typename DataHolderNodeType, bool WithDiagonals>
    RenderableCoordinates2D
    RenderableHexagonalGrid<DataHolderNodeType, WithDiagonals>::GetNodeRenderCoordinates(const Coordinates2D &Coordinates,
                                                                const RenderableSize2D &RenderSize) const {
        return {
                Coordinates.X * RenderSize.Width + (this->GetRowOffset(Coordinates.Y) * RenderSize.Width / 2),
                Coordinates.Y * RenderSize.Height,
        };
    }

    template<template <typename NodeType, bool WD> typename DataHolderNodeType, bool WithDiagonals>
    RenderableSize2D RenderableHexagonalGrid<DataHolderNodeType, WithDiagonals>::GetNodeRenderSize(const RenderableSize2D &ContainerSize) const {
        const auto Size = std::min(
            // +1 for row offset
            ContainerSize.Width / (this->m_Width + 1),
            ContainerSize.Height / this->m_Height
        );
        return {
            Size,
            Size,
        };
    }

    template<typename GridNodeType, template <typename NodeType, bool WD> typename DataHolderNodeType, bool WithDiagonals>
    std::vector<Coordinates2D>
    BaseHexagonalGrid<GridNodeType, DataHolderNodeType, WithDiagonals>::GetNeighborsCoordinates(Coordinates2D &Coordinates) {
        auto RowOffset = GetRowOffset(Coordinates);
        return {
            // row before
            {Coordinates.X - 1 + RowOffset, Coordinates.Y - 1},
            {Coordinates.X + RowOffset, Coordinates.Y - 1},
            // same row
            {Coordinates.X - 1, Coordinates.Y},
            {Coordinates.X + 1, Coordinates.Y},
            // row after
            {Coordinates.X - 1 + RowOffset, Coordinates.Y + 1},
            {Coordinates.X + RowOffset, Coordinates.Y + 1},
        };
    }
} // Grid