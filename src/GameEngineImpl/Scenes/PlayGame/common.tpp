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

    template<typename GridNodeType, bool WithDiagonals>
    bool GridDataHolder<GridNodeType, WithDiagonals>::IsBlocked() const {
        return this->CurrentNodeType == GridImpl::NodeType::Empty;
    }

    template <typename GridNodeType, bool WithDiagonals>
    typename GridDataHolder<GridNodeType, WithDiagonals>::GridNodeButtonType *GridDataHolder<GridNodeType, WithDiagonals>::GetGridNodeButton() const {
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

    template<typename DataHolderType>
    void GridNodeButton<DataHolderType>::HideOverlay() {
        if (Overlay != nullptr) {
			delete Overlay;
			Overlay = nullptr;
        }
    }

    template<typename DataHolderType>
    void GridNodeButton<DataHolderType>::ShowOverlay() {
        if (Overlay != nullptr)
            return;
        Overlay = new sf::RectangleShape({m_Width, m_Height});
        Overlay->setFillColor({255, 0, 0, 100});
        Overlay->setPosition(UI::GridNodeButton::GetPosition());
    }

    template<typename DataHolderType>
    void GridNodeButton<DataHolderType>::Render(sf::RenderWindow *Window) {
        UI::GridNodeButton::Render(Window);
        if (nullptr != Overlay) {
            Window->draw(*Overlay);
        }
    }

    template<typename DataHolderType>
    GridNodeButton<DataHolderType>::~GridNodeButton() {
        delete Overlay;
        Overlay = nullptr;
    }
}