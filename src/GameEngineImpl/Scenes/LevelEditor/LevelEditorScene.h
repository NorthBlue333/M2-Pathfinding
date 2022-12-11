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
        class GridNodeButton;

        class GridDataHolder {
        public:
            enum struct NodeType {
                Empty = 0,
                Plain,
                Portal
            };

            void Render(sf::RenderWindow *Window);

            explicit GridDataHolder(GridNodeButton* Btn) : m_GridNodeButton(Btn) {};
            ~GridDataHolder();

            void SetGridNodeButton(GridNodeButton* Btn);
            GridNodeButton* GetGridNodeButton() const;

            void SetCurrentNodeType(NodeType NewType);
            const NodeType& GetCurrentNodeType() const;

            const GridDataHolder* GetLinkedPortal() const;
            void SetLinkedPortal(GridDataHolder* Linked);

            void SetTextures(std::map<NodeType, sf::Texture*>& NewTextures);
        private:
            void SetTextureFromNodeType();

            std::map<NodeType, sf::Texture*> Textures;
            GridNodeButton* m_GridNodeButton;
            NodeType CurrentNodeType = NodeType::Empty;

            GridDataHolder* LinkedPortal = nullptr;
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
            GridDataHolder::NodeType NodeType;
        };

        class GridNodeButton : public UI::GridNodeButton {
            using UI::GridNodeButton::GridNodeButton;

            sf::RectangleShape* Overlay = nullptr;

        public:
            void ShowOverlay();
            void HideOverlay();
            void Render(sf::RenderWindow *Window) override;
            ~GridNodeButton() override;
            GridDataHolder* DataHolder;
        };

    public:
        explicit LevelEditorScene(GameType* Game);
        ~LevelEditorScene() override;

        void Load() override;
        void ExecuteCalculations(sf::Time Elapsed) override;
        void Render() override;

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
        GridDataHolder* m_LastPortal = nullptr;

        LevelEditorGridType m_CurrentGridType = LevelEditorGridType::Square;
        GridType m_Grid;

        void CreateGrid();
        void SetCurrentGridType(LevelEditorGridType NewGridType);
        GridDataHolder* CreateHexagonalGridDataHolder(
            const Grid::RenderableCoordinates2D& RenderCoordinates,
            const Grid::RenderableSize2D& RenderSize
        );
        GridDataHolder* CreateSquareGridDataHolder(
            const Grid::RenderableCoordinates2D& RenderCoordinates,
            const Grid::RenderableSize2D& RenderSize
        );
        GridDataHolder* CreateGridDataHolder(
            std::map<GridDataHolder::NodeType, sf::Texture*>& Textures,
            const Grid::RenderableCoordinates2D& RenderCoordinates,
            const Grid::RenderableSize2D& RenderSize
        );

        void ResetNodeTypeButtons();

        NodeTypeButton* AddButton(
                const sf::Texture *Texture,
                const sf::String& Name,
                LevelEditorScene::GridDataHolder::NodeType
        );
    };

} // Scenes

#endif //PATHFINDING_LEVELEDITORSCENE_H
