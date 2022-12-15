#include "common.h"

namespace GameEngineImpl::Scenes::PlayGame {
    template <typename GridNodeType, bool WithDiagonals>
    void GridDataHolder<GridNodeType, WithDiagonals>::Render(sf::RenderWindow *Window) {
        m_GridNodeButton->Render(Window);
    }

    template <typename GridNodeType, bool WithDiagonals>
    GridDataHolder<GridNodeType, WithDiagonals>::~GridDataHolder()  {
        delete m_GridNodeButton;
    }

    template <typename GridNodeType, bool WithDiagonals>
    GridDataHolder<GridNodeType, WithDiagonals>::GridNodeButtonType *GridDataHolder<GridNodeType, WithDiagonals>::GetGridNodeButton() const {
        return m_GridNodeButton;
    }

    template <typename GridNodeType, bool WithDiagonals>
    void GridDataHolder<GridNodeType, WithDiagonals>::SetGridNodeButton(GridDataHolder<GridNodeType, WithDiagonals>::GridNodeButtonType *Btn) {
        m_GridNodeButton = Btn;
    }

    template <typename GridNodeType, bool WithDiagonals>
    void GridDataHolder<GridNodeType, WithDiagonals>::SetTextureFromNodeType() {
        m_GridNodeButton->SetTexture(this->Textures.at(this->CurrentNodeType));
    }
}