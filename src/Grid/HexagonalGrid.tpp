#include "HexagonalGrid.h"

namespace Grid {
    template<typename GridNodeType, template <typename NodeType> typename DataHolderNodeType>
    int BaseHexagonalGrid<GridNodeType, DataHolderNodeType>::GetRowOffset(const Coordinates2D &Coordinates) const {
        return GetRowOffset(Coordinates.Y);
    }

    template<typename GridNodeType, template <typename NodeType> typename DataHolderNodeType>
    int BaseHexagonalGrid<GridNodeType, DataHolderNodeType>::GetRowOffset(const int& Y) const {
        return Y&1;
    }

    template<template <typename NodeType> typename DataHolderNodeType>
    RenderableCoordinates2D
    RenderableHexagonalGrid<DataHolderNodeType>::GetNodeRenderCoordinates(const Coordinates2D &Coordinates,
                                                                const RenderableSize2D &RenderSize) const {
        return {
                Coordinates.X * RenderSize.Width + (this->GetRowOffset(Coordinates.Y) * RenderSize.Width / 2),
                Coordinates.Y * RenderSize.Height,
        };
    }

    template<template <typename NodeType> typename DataHolderNodeType>
    RenderableSize2D RenderableHexagonalGrid<DataHolderNodeType>::GetNodeRenderSize(const RenderableSize2D &ContainerSize) const {
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

    template<typename GridNodeType, template <typename NodeType> typename DataHolderNodeType>
    std::vector<Coordinates2D>
    BaseHexagonalGrid<GridNodeType, DataHolderNodeType>::GetNeighborsCoordinates(Coordinates2D &Coordinates) {
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