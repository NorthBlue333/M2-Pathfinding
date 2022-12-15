#include "RenderableGrid.h"

namespace Grid {
    template <
        template <typename NodeType, template <typename NT, bool WD> typename DataHolderNodeType, bool WithDiagonals> typename GridNodeType,
        template <typename NodeType, bool WD> typename DataHolderType,
        bool WithDiagonals
    >
    void RenderableNode<GridNodeType, DataHolderType, WithDiagonals>::Render(sf::RenderWindow *Window)  {
        this->DataHolder->Render(Window);
    }

    template<typename GridType, typename GridNodeType, template <typename NodeType, bool WD> typename DataHolderNodeType, bool WithDiagonals>
    void RenderableGrid<GridType, GridNodeType, DataHolderNodeType, WithDiagonals>::CreateNodes(
            unsigned int& Width,
            unsigned int& Height,
            const RenderableSize2D ContainerSize,
            std::function<DataHolderNodeType<GridNodeType, WithDiagonals>*(GridNodeType* GridNode, const RenderableCoordinates2D& RenderCoordinates, const RenderableSize2D& RenderSize)> CreateDataHolderNode
    ) {
        this->m_Width = Width;
        this->m_Height = Height;
        this->m_Nodes = {};
        this->m_Nodes.reserve(Width * Height);
        m_ContainerSize = ContainerSize;
        const auto RenderSize = GetNodeRenderSize(m_ContainerSize);
        for (int Y = 0; Y < Height; ++Y) {
            for (int X = 0; X < Width; ++X) {
                Coordinates2D Coordinates{X, Y};
                this->m_Nodes.emplace_back(
                    Coordinates,
                    nullptr
                );
                auto LastEl = &this->m_Nodes.back();
                LastEl->DataHolder = CreateDataHolderNode(LastEl, GetNodeRenderCoordinates(Coordinates, RenderSize), RenderSize);
                LastEl->DataHolder->Node = LastEl;
            }
        }

        this->GenerateNeighbors();
    }

    template<typename GridType, typename GridNodeType, template <typename NodeType, bool WD> typename DataHolderNodeType, bool WithDiagonals>
    void RenderableGrid<GridType, GridNodeType, DataHolderNodeType, WithDiagonals>::Render(sf::RenderWindow *Window) {
        for (auto &node : this->m_Nodes) {
            node.Render(Window);
        }
    }

    template<typename GridType, typename GridNodeType, template <typename NodeType, bool WD> typename DataHolderNodeType, bool WithDiagonals>
    const RenderableSize2D &
    RenderableGrid<GridType, GridNodeType, DataHolderNodeType, WithDiagonals>::GetContainerSize() const {
        return m_ContainerSize;
    }
} // Grid
