#include <iostream>
#include "PlayGameScene.h"
#include "PlayGameGameMode.h"
#include "PlayGameGameController.h"
#include "../../../PathFinding/AStar.h"

namespace GameEngineImpl::Scenes::PlayGame {
    PlayGameGameController::PlayGameGameController(
            Game *Game,
            PlayGameScene* Scene,
            PlayGameGameMode *GameMode
    ) : BaseGameController(
            Game,
            Scene,
            GameMode
    ) {

    }

    void PlayGameGameController::ComputeInputs() {
        sf::Event event{};
        auto Window = m_Game->GetWindow();
        while(Window->pollEvent( event ))
        {
            if (sf::Event::Closed == event.type) {
                m_Game->StopGame();
                continue;
            }

            auto Buttons = m_Scene->GetButtons();
            HandleOnMouseLeft(event, Buttons);
        }
    }

    void PlayGameGameController::HandleOnGridButtonClick(Grid::Coordinates2D& TargetNodeCoordinates, UI::IButton *Btn) {
        auto PlayerCoordinates = m_Scene->GetPlayer()->GetCoordinates();
        // @todo maybe do this compile time but conflict with ForwardRef of Scene
        if (m_Scene->GetCurrentGridType() == PlayGameGridType::Square) {
            auto Grid = m_Scene->GetSquareGrid();
            PathFinding::AStar<SquareGridType, SquareGridType::GridNode_T> AStar(Grid);
            auto Path = AStar.GetPath(Grid->GetNodeAtCoordinates(PlayerCoordinates), Grid->GetNodeAtCoordinates(TargetNodeCoordinates));
            for (const auto & Node : Path) {
                std::cout << Node->Coordinates.X << " " << Node->Coordinates.Y << std::endl;
            }
        } else {
            auto Grid = m_Scene->GetHexagonalGrid();
            PathFinding::AStar<HexagonalGridType, HexagonalGridType::GridNode_T> AStar(Grid);
            auto Path = AStar.GetPath(Grid->GetNodeAtCoordinates(PlayerCoordinates), Grid->GetNodeAtCoordinates(TargetNodeCoordinates));
            for (const auto & Node : Path) {
                std::cout << Node->Coordinates.X << " " << Node->Coordinates.Y << std::endl;
            }
        }
    }
} // Scenes