#include "LevelEditorScene.h"

namespace GameEngineImpl::Scenes {
    template <typename DataHolderType>
    DataHolderType *LevelEditorScene::FillGridDataHolder(
            std::map<GridImpl::NodeType, sf::Texture *> &Textures,
            const Grid::RenderableCoordinates2D& RenderCoordinates,
            const Grid::RenderableSize2D& RenderSize
    ) {
        auto DataHolder = new DataHolderType();
        auto NewBtn = new GridNodeButton<DataHolderType>(
            Textures.at(DataHolder->GetCurrentNodeType()),
            RenderSize.Width,
            RenderSize.Height
        );
        // @todo correct position
        NewBtn->SetPosition(BUTTON_MARGIN + RenderCoordinates.X, 70 + RenderCoordinates.Y);
        NewBtn->SetOnClick([this](auto && Btn) {
            m_GameMode->GetGameController()->HandleOnGridButtonClick<DataHolderType>(Btn);
        });
        NewBtn->SetOnDragOver([this](auto && Btn) {
            m_GameMode->GetGameController()->HandleOnGridButtonClick<DataHolderType>(Btn);
        });
        NewBtn->SetOnHover(
            [this](auto && Btn) {
                m_GameMode->GetGameController()->HandleOnGridButtonHoverStart<DataHolderType>(Btn);
            },
            [this](auto && Btn) {
                m_GameMode->GetGameController()->HandleOnGridButtonHoverEnd<DataHolderType>(Btn);
            }
        );
        NewBtn->DataHolder = DataHolder;
        DataHolder->SetGridNodeButton(NewBtn);
        DataHolder->SetTextures(Textures);
        return DataHolder;
    }
}
