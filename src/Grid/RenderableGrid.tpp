#include "RenderableGrid.h"

namespace Grid {
    template<typename NodeType>
    void RenderableNode<NodeType>::Render(sf::RenderWindow *Window)  {
        this->DataHolder->Render(Window);
    }

    template<typename GridType, typename DataHolderNodeType>
    void RenderableGrid<GridType, DataHolderNodeType>::CreateNodes(
            unsigned int& Width,
            unsigned int& Height,
            const RenderableSize2D& ContainerSize,
            std::function<DataHolderNodeType*(const RenderableCoordinates2D& RenderCoordinates, const RenderableSize2D& RenderSize)> CreateDataHolderNode
    ) {
        this->m_Width = Width;
        this->m_Height = Height;
        this->m_Nodes = {};
        this->m_Nodes.reserve(Width * Height);
        const auto RenderSize = GetNodeRenderSize(ContainerSize);
        for (int Y = 0; Y < Height; ++Y) {
            for (int X = 0; X < Width; ++X) {
                Coordinates2D Coordinates{X, Y};
                this->m_Nodes.emplace_back(
                    Coordinates,
                    CreateDataHolderNode(GetNodeRenderCoordinates(Coordinates, RenderSize), RenderSize)
                );
            }
        }
    }

    template<typename GridType, typename DataHolderNodeType>
    void RenderableGrid<GridType, DataHolderNodeType>::Render(sf::RenderWindow *Window) {
        for (auto &node : this->m_Nodes) {
            node.Render(Window);
        }
    }
} // Grid
