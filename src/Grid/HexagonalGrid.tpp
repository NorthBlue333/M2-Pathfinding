#include "HexagonalGrid.h"

namespace Grid {
    template<typename GridNodeType, typename DataHolderNodeType>
    int BaseHexagonalGrid<GridNodeType, DataHolderNodeType>::GetRowOffset(const Coordinates2D &Coordinates) const {
        return GetRowOffset(Coordinates.Y);
    }

    template<typename GridNodeType, typename DataHolderNodeType>
    int BaseHexagonalGrid<GridNodeType, DataHolderNodeType>::GetRowOffset(const int& Y) const {
        return Y&1;
    }

    template<typename DataHolderNodeType>
    RenderableCoordinates2D
    RenderableHexagonalGrid<DataHolderNodeType>::GetNodeRenderCoordinates(const Coordinates2D &Coordinates,
                                                                const RenderableSize2D &RenderSize) const {
        return {
                Coordinates.X * RenderSize.Width + (this->GetRowOffset(Coordinates.Y) * RenderSize.Width / 2),
                Coordinates.Y * RenderSize.Height,
        };
    }

    template<typename DataHolderNodeType>
    RenderableSize2D RenderableHexagonalGrid<DataHolderNodeType>::GetNodeRenderSize(const RenderableSize2D &ContainerSize) const {
        const auto Size = std::min(ContainerSize.Width / this->m_Width, ContainerSize.Height / this->m_Height);
        return {
            Size,
            Size,
        };
    }
} // Grid