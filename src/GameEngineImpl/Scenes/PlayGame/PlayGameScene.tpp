#include "PlayGameScene.h"

namespace GameEngineImpl::Scenes::PlayGame {
    template <typename DataHolderType>
    DataHolderType *PlayGameScene::FillGridDataHolder(
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
            m_GameMode->GetGameController()->HandleOnGridButtonClick(static_cast<GridNodeButton<DataHolderType>*>(Btn)->DataHolder->Node->Coordinates, Btn);
        });
        NewBtn->DataHolder = DataHolder;
        DataHolder->SetGridNodeButton(NewBtn);
        DataHolder->SetTextures(Textures);
        return DataHolder;
    }
}
