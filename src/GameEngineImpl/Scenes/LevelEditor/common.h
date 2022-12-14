#ifndef PATHFINDING_LEVELEDITOR_COMMON_H
#define PATHFINDING_LEVELEDITOR_COMMON_H

#include "../../../UserInterface/GridNodeButton.h"
#include "../../../Grid/HexagonalGrid.h"
#include "../../../Grid/SquareGrid.h"
#include "../../../GridImpl/GridsWithPortals.h"
#include "../../../UserInterface/SquareSpriteButton.h"

namespace GameEngineImpl::Scenes::LevelEditor {
    class NodeTypeButton : public UI::SquareSpriteButton {
        using UI::SquareSpriteButton::SquareSpriteButton;

    public:
        GridImpl::NodeType TargetNodeType;
    };

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

    template <typename GridNodeType, bool WithDiagonals>
    class GridDataHolder : public GridImpl::GridDataHolder<GridDataHolder, GridNodeType, WithDiagonals> {
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

    using HexagonalGridType = Grid::RenderableHexagonalGrid<GridDataHolder, false>;
    // @todo add SquareGridTypeWithDiagonals
    using SquareGridType = Grid::RenderableSquareGrid<GridDataHolder, false>;
}

#include "common.tpp"

#endif //PATHFINDING_LEVELEDITOR_COMMON_H
