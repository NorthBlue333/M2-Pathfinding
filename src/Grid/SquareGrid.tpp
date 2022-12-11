#include "SquareGrid.h"

namespace Grid {
    template<typename DataHolderNodeType>
    RenderableCoordinates2D
    RenderableSquareGrid<DataHolderNodeType>::GetNodeRenderCoordinates(const Coordinates2D &Coordinates,
                                                                const RenderableSize2D &RenderSize) const {
        return {
            Coordinates.X * (RenderSize.Width + 1),
            Coordinates.Y * (RenderSize.Height + 1),
        };
    }

    template<typename DataHolderNodeType>
    RenderableSize2D RenderableSquareGrid<DataHolderNodeType>::GetNodeRenderSize(const RenderableSize2D &ContainerSize) const {
        const auto Size = std::min(ContainerSize.Width / this->m_Width, ContainerSize.Height / this->m_Height);
        return {
            Size,
            Size,
        };
    }
} // Grid