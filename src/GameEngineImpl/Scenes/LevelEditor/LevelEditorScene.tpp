#include "LevelEditorScene.h"

namespace GameEngineImpl::Scenes {
    template <typename GridNodeType>
    void LevelEditorScene::GridDataHolder<GridNodeType>::Render(sf::RenderWindow *Window) {
        m_GridNodeButton->Render(Window);
    }

    template <typename GridNodeType>
    LevelEditorScene::GridDataHolder<GridNodeType>::~GridDataHolder()  {
        delete m_GridNodeButton;
    }

    template <typename GridNodeType>
    LevelEditorScene::GridDataHolder<GridNodeType>::GridNodeButtonType *LevelEditorScene::GridDataHolder<GridNodeType>::GetGridNodeButton() const {
        return m_GridNodeButton;
    }

    template <typename GridNodeType>
    void LevelEditorScene::GridDataHolder<GridNodeType>::SetGridNodeButton(LevelEditorScene::GridDataHolder<GridNodeType>::GridNodeButtonType *Btn) {
        m_GridNodeButton = Btn;
    }

    template <typename GridNodeType>
    void LevelEditorScene::GridDataHolder<GridNodeType>::SetTextureFromNodeType() {
        m_GridNodeButton->SetTexture(this->Textures.at(this->CurrentNodeType));
        m_GridNodeButton->HideOverlay();
    }

    template<typename DataHolderType>
    void LevelEditorScene::GridNodeButton<DataHolderType>::HideOverlay() {
        delete Overlay;
        Overlay = nullptr;
    }

    template<typename DataHolderType>
    void LevelEditorScene::GridNodeButton<DataHolderType>::ShowOverlay() {
        if (Overlay != nullptr)
            return;
        Overlay = new sf::RectangleShape({m_Width, m_Height});
        Overlay->setFillColor({255, 0, 0, 100});
        Overlay->setPosition(UI::GridNodeButton::GetPosition());
    }

    template<typename DataHolderType>
    void LevelEditorScene::GridNodeButton<DataHolderType>::Render(sf::RenderWindow *Window) {
        UI::GridNodeButton::Render(Window);
        if (nullptr != Overlay) {
            Window->draw(*Overlay);
        }
    }

    template<typename DataHolderType>
    LevelEditorScene::GridNodeButton<DataHolderType>::~GridNodeButton() {
        delete Overlay;
        Overlay = nullptr;
    }

    template <typename DataHolderType>
    DataHolderType *LevelEditorScene::FillGridDataHolder(
            std::map<GridImpl::NodeType, sf::Texture *> &Textures,
            const Grid::RenderableCoordinates2D& RenderCoordinates,
            const Grid::RenderableSize2D& RenderSize
    ) {
        auto DataHolder = new DataHolderType();
        auto NewBtn = new GridNodeButton<DataHolderType>(
                Textures.at(GridImpl::NodeType::Empty),
                RenderSize.Width,
                RenderSize.Height
        );
        NewBtn->SetPosition(BUTTON_MARGIN + RenderCoordinates.X, 50 + RenderCoordinates.Y);
        NewBtn->SetOnClick([this](auto && Btn) {
            // @todo extract to method
            if (nullptr == m_CurrentNodeTypeButton)
                return;

            auto CastedBtn = static_cast<GridNodeButton<DataHolderType>*>(Btn);
            if (nullptr == CastedBtn->DataHolder)
                return;
            CastedBtn->DataHolder->SetCurrentNodeType(m_CurrentNodeTypeButton->TargetNodeType);
            if (nullptr == m_LastPortal && m_CurrentNodeTypeButton->TargetNodeType == GridImpl::NodeType::Portal) {
                m_LastPortal = CastedBtn->DataHolder;
                return;
            }
            auto LastPortal = dynamic_cast<DataHolderType*>(m_LastPortal);
            if (nullptr != LastPortal) {
                if (m_CurrentNodeTypeButton->TargetNodeType == GridImpl::NodeType::Portal) {
                    LastPortal->SetLinkedPortal(CastedBtn->DataHolder);
                    m_LastPortal = nullptr;
                } else {
                    LastPortal->SetCurrentNodeType(GridImpl::NodeType::Empty);
                    m_LastPortal = nullptr;
                }
            }
        });
        NewBtn->SetOnHover(
                [this](auto && Btn) {
                    auto CastedBtn = static_cast<GridNodeButton<DataHolderType>*>(Btn);
                    if (
                        nullptr == CastedBtn->DataHolder
                        || CastedBtn->DataHolder->GetCurrentNodeType() != GridImpl::NodeType::Portal
                        || nullptr == CastedBtn->DataHolder->GetLinkedPortal()
                    )
                        return;

                    CastedBtn->ShowOverlay();
                    CastedBtn->DataHolder->GetLinkedPortal()->GetGridNodeButton()->ShowOverlay();
                },
                [this](auto && Btn) {
                    auto CastedBtn = static_cast<GridNodeButton<DataHolderType>*>(Btn);
                    CastedBtn->HideOverlay();

                    if (
                        nullptr == CastedBtn->DataHolder
                        || CastedBtn->DataHolder->GetCurrentNodeType() != GridImpl::NodeType::Portal
                        || nullptr == CastedBtn->DataHolder->GetLinkedPortal()
                    )
                        return;

                    CastedBtn->DataHolder->GetLinkedPortal()->GetGridNodeButton()->HideOverlay();
                }
        );
        NewBtn->DataHolder = DataHolder;
        DataHolder->SetGridNodeButton(NewBtn);
        DataHolder->SetTextures(Textures);
        return DataHolder;
    }
}
