#include "common.h"

namespace GameEngineImpl::Scenes {
    template <typename GridNodeType>
    void GridDataHolder<GridNodeType>::Render(sf::RenderWindow *Window) {
        m_GridNodeButton->Render(Window);
    }

    template <typename GridNodeType>
    GridDataHolder<GridNodeType>::~GridDataHolder()  {
        delete m_GridNodeButton;
    }

    template <typename GridNodeType>
    GridDataHolder<GridNodeType>::GridNodeButtonType *GridDataHolder<GridNodeType>::GetGridNodeButton() const {
        return m_GridNodeButton;
    }

    template <typename GridNodeType>
    void GridDataHolder<GridNodeType>::SetGridNodeButton(GridDataHolder<GridNodeType>::GridNodeButtonType *Btn) {
        m_GridNodeButton = Btn;
    }

    template <typename GridNodeType>
    void GridDataHolder<GridNodeType>::SetTextureFromNodeType() {
        m_GridNodeButton->SetTexture(this->Textures.at(this->CurrentNodeType));
        m_GridNodeButton->HideOverlay();
    }

    template<typename DataHolderType>
    void GridNodeButton<DataHolderType>::HideOverlay() {
        delete Overlay;
        Overlay = nullptr;
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