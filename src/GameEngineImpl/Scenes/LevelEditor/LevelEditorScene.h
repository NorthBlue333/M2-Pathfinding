#ifndef PATHFINDING_LEVELEDITORSCENE_H
#define PATHFINDING_LEVELEDITORSCENE_H

#include "../../../GameEngine/BaseScene.h"
#include "../../common_types.h"
#include "LevelEditorGameMode.h"
#include "../../../UserInterface/IButton.h"
#include "../../../UserInterface/TextButton.h"
#include "../Traits/HasTextures.h"
#include "../Traits/HasFonts.h"
#include "../../../Grid/HexagonalGrid.h"
#include "../../../Grid/SquareGrid.h"
#include "../../../UserInterface/GridNodeButton.h"
#include "../../../UserInterface/SquareSpriteButton.h"
#include "../../../GridImpl/GridsWithPortals.h"
#include <vector>
#include <map>

namespace GameEngineImpl::Scenes {
    enum struct LevelEditorTextureName {
        FilledSquare = 0,
        FilledHexagon,
        OutlinedSquare,
        OutlinedHexagon,
        PortalSquare,
        PortalHexagon
    };

    enum struct LevelEditorFont {
        AnekDevanagari = 0,
    };

    enum struct LevelEditorGridType {
        Square = 0,
        Hexagonal,
    };

    class LevelEditorScene :
            public BaseSceneType<LevelEditorScene, LevelEditorGameMode, LevelEditorGameController>,
            public Traits::HasTextures<LevelEditorTextureName>,
            public Traits::HasFonts<LevelEditorFont>
    {
        template <typename DataHolderType>
        class GridNodeButton : public UI::GridNodeButton {
            using UI::GridNodeButton::GridNodeButton;

            sf::RectangleShape* Overlay = nullptr;

        public:
            void ShowOverlay();
            void HideOverlay();
            void Render(sf::RenderWindow *Window) override;
            ~GridNodeButton() override;
            DataHolderType* DataHolder;
        };

        template <typename GridNodeType>
        class GridDataHolder : public GridImpl::GridDataHolder<GridDataHolder, GridNodeType> {
        public:
            using GridNodeButtonType = GridNodeButton<GridDataHolder>;
            GridDataHolder() = default;
            explicit GridDataHolder(GridNodeButtonType* Btn) : m_GridNodeButton(Btn) {};
            ~GridDataHolder() override;

            void SetGridNodeButton(GridNodeButtonType* Btn);
            GridNodeButtonType* GetGridNodeButton() const;

            void Render(sf::RenderWindow *Window) override;
        protected:
            void SetTextureFromNodeType() override;
            GridNodeButton<GridDataHolder>* m_GridNodeButton = nullptr;
        };

        using HexagonalGridType = Grid::RenderableHexagonalGrid<GridDataHolder>;
        using SquareGridType = Grid::RenderableSquareGrid<GridDataHolder>;

        union GridType {
            SquareGridType* SquareGrid = nullptr;
            HexagonalGridType* HexagonalGrid;
        };

        class NodeTypeButton : public UI::SquareSpriteButton {
            using UI::SquareSpriteButton::SquareSpriteButton;

        public:
            GridImpl::NodeType TargetNodeType;
        };

    public:
        explicit LevelEditorScene(GameType* Game);
        ~LevelEditorScene() override;

        void Load() override;
        void ExecuteCalculations(sf::Time Elapsed) override;
        void Render() override;
        void SetCurrentGridType(LevelEditorGridType NewGridType);

        std::vector<UI::IButton*> GetButtons();
    protected:
        static int constexpr BUTTON_TEXT_SIZE = 30;
        static int constexpr BUTTON_WIDTH = 100;
        static int constexpr BUTTON_HEIGHT = 120;
        static int constexpr BUTTON_MARGIN = 10;

        sf::Text Title;
        UI::TextButton* m_BackButton;
        std::vector<UI::TextButton*> m_GridTypeButtons;
        std::vector<UI::IButton*> m_EditorButtons;
        NodeTypeButton* m_CurrentNodeTypeButton = nullptr;
        GridImpl::IGridDataHolder * m_LastPortal = nullptr;

        LevelEditorGridType m_CurrentGridType = LevelEditorGridType::Square;
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
