#ifndef PATHFINDING_PLAYGAMESCENE_H
#define PATHFINDING_PLAYGAMESCENE_H

#include "../../../GameEngine/BaseScene.h"
#include "../../Game.h"
#include "PlayGameGameMode.h"
#include "../../../UserInterface/IButton.h"
#include "../Traits/HasFonts.h"
#include "../../../UserInterface/TextButton.h"
#include "common.h"
#include "Player.h"
#include "../Traits/HasTextures.h"
#include <vector>

namespace GameEngineImpl::Scenes::PlayGame {
    enum struct PlayGameTextureName {
        FilledSquare = 0,
        FilledHexagon,
        OutlinedSquare,
        OutlinedHexagon,
        PortalSquare,
        PortalHexagon,
        FlagSquare,
        FlagHexagon
    };
    
    enum struct PlayGameFont {
        AnekDevanagari = 0,
    };

    class PlayGameScene :
        public BaseSceneType<PlayGameScene, PlayGameGameMode, PlayGameGameController>, public Traits::HasFonts<PlayGameFont>,
        public Traits::HasTextures<PlayGameTextureName>
    {
        union GridType {
            SquareGridType* SquareGrid = nullptr;
            HexagonalGridType* HexagonalGrid;
        };
    public:
        explicit PlayGameScene(Game* Game);
        ~PlayGameScene() override;

        void Load() override;
        void ExecuteCalculations(sf::Time Elapsed) override;
        void Render() override;

        std::vector<UI::IButton*> GetButtons();

        const GameEngineImpl::GridType& GetCurrentGridType() const;
        HexagonalGridType* GetHexagonalGrid() const;
        SquareGridType* GetSquareGrid() const;

        Player* GetPlayer() const;
    protected:
        static int constexpr TITLE_TEXT_SIZE = 30;
        static int constexpr BUTTON_TEXT_SIZE = 30;
        static int constexpr BUTTON_WIDTH = 100;
        static int constexpr BUTTON_HEIGHT = 120;
        static int constexpr BUTTON_MARGIN = 10;

        GameEngineImpl::GridType m_CurrentGridType = GameEngineImpl::GridType::Square;
        GridType m_Grid;

        void CreateGrid();

        UI::TextButton* m_BackButton;
        Player* m_Player;

        HexagonalGridType::DataHolder_T * CreateHexagonalGridDataHolder(
            HexagonalGridType::GridNode_T * GridNode,
            const Grid::RenderableCoordinates2D& RenderCoordinates,
            const Grid::RenderableSize2D& RenderSize
        );
        SquareGridType::DataHolder_T * CreateSquareGridDataHolder(
            SquareGridType::GridNode_T * GridNode,
            const Grid::RenderableCoordinates2D& RenderCoordinates,
            const Grid::RenderableSize2D& RenderSize
        );
        template <typename DataHolderType>
        DataHolderType* FillGridDataHolder(
            std::map<GridImpl::NodeType, sf::Texture*>& Textures,
            const Grid::RenderableCoordinates2D& RenderCoordinates,
            const Grid::RenderableSize2D& RenderSize
        );

        void SetPlayerPositionFromCoordinates(Grid::RenderableCoordinates2D RenderCoordinates, Grid::RenderableSize2D NodeSize);
    };

} // Scenes

#include "PlayGameScene.tpp"

#endif //PATHFINDING_PLAYGAMESCENE_H
