#ifndef PATHFINDING_LEVELEDITORSCENE_H
#define PATHFINDING_LEVELEDITORSCENE_H

#include "../../../GameEngine/BaseScene.h"
#include "../../Game.h"
#include "../../../UserInterface/IButton.h"
#include "../../../UserInterface/TextButton.h"
#include "../Traits/HasTextures.h"
#include "../Traits/HasFonts.h"
#include "../../../UserInterface/SquareSpriteButton.h"
#include "../../../GridImpl/GridsWithPortals.h"
#include "LevelEditorGameMode.h"
#include "LevelEditorGameController.h"
#include "common.h"
#include <vector>
#include <map>

namespace GameEngineImpl::Scenes::LevelEditor {
    enum struct LevelEditorTextureName {
        FilledSquare = 0,
        FilledHexagon,
        OutlinedSquare,
        OutlinedHexagon,
        PortalSquare,
        PortalHexagon,
        FlagSquare,
        FlagHexagon
    };

    enum struct LevelEditorFont {
        AnekDevanagari = 0,
    };

    class LevelEditorScene :
            public BaseSceneType<LevelEditorScene, LevelEditorGameMode, LevelEditorGameController>,
            public Traits::HasTextures<LevelEditorTextureName>,
            public Traits::HasFonts<LevelEditorFont>
    {
        union GridType {
            SquareGridType* SquareGrid = nullptr;
            HexagonalGridType* HexagonalGrid;
        };

    public:
        explicit LevelEditorScene(Game* Game);
        ~LevelEditorScene() override;

        void Load() override;
        void ExecuteCalculations(sf::Time Elapsed) override;
        void Render() override;
        void SetCurrentGridType(GameEngineImpl::GridType NewGridType);

        std::vector<UI::IButton*> GetButtons();

        const GameEngineImpl::GridType& GetCurrentGridType() const;
        HexagonalGridType* GetHexagonalGrid() const;
        SquareGridType* GetSquareGrid() const;
    protected:
        static int constexpr BUTTON_TEXT_SIZE = 30;
        static int constexpr BUTTON_WIDTH = 100;
        static int constexpr BUTTON_HEIGHT = 120;
        static int constexpr BUTTON_MARGIN = 10;

        sf::Text Title;
        UI::TextButton* m_BackButton;
        UI::TextButton* m_SaveButton{};
        std::vector<UI::TextButton*> m_GridTypeButtons;
        std::vector<UI::IButton*> m_EditorButtons;

        GameEngineImpl::GridType m_CurrentGridType = GameEngineImpl::GridType::Square;
        GridType m_Grid;

        void CreateGrid();

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

        void ResetNodeTypeButtons();

        NodeTypeButton* AddButton(
                const sf::Texture *Texture,
                const sf::String& Name,
                GridImpl::NodeType
        );
    };

} // Scenes

#include "LevelEditorScene.tpp"

#endif //PATHFINDING_LEVELEDITORSCENE_H
