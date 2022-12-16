#include "LevelEditorGameController.h"
#include "LevelEditorGameController.h"
#include "LevelEditorScene.h"

namespace GameEngineImpl::Scenes::LevelEditor {
    LevelEditorGameController::LevelEditorGameController(
            Game *Game,
            LevelEditorScene* Scene,
            LevelEditorGameMode *GameMode
    ) : BaseGameController(
            Game,
            Scene,
            GameMode
    ) {

    }

    void LevelEditorGameController::ComputeInputs() {
        sf::Event event{};
        auto Window = m_Game->GetWindow();

        while(Window->pollEvent( event ))
        {
            if (sf::Event::Closed == event.type) {
                m_Game->StopGame();
                continue;
            }

            SetMousePressed(event);
            auto Buttons = m_Scene->GetButtons();
            HandleOnMouseLeft(event, Buttons);
        }

        auto MouseCoords = Window->mapPixelToCoords(sf::Mouse::getPosition(*Window));
        // refetch buttons each time because they may have changed
        auto Buttons = m_Scene->GetButtons();
        HandleOnMouseDragOver(MouseCoords, Buttons);
        Buttons = m_Scene->GetButtons();
        HandleOnMouseHover(MouseCoords, Buttons);
    }

    void LevelEditorGameController::ResetNodeTypeButtons() {
        m_CurrentNodeTypeButton = nullptr;
        m_LastPortal = nullptr;
        m_PlayerStart = nullptr;
    }

    void LevelEditorGameController::HandleOnNodeTypeButtonClick(UI::IButton *Btn) {
        if (m_CurrentNodeTypeButton != nullptr) {
            m_CurrentNodeTypeButton->ToggleActive(false);
        }
        auto CastedBtn = dynamic_cast<NodeTypeButton*>(Btn);
        if (nullptr == CastedBtn)
            return;

        if (m_CurrentNodeTypeButton == CastedBtn) {
            m_CurrentNodeTypeButton = nullptr;
            return;
        }
        CastedBtn->ToggleActive(true);
        m_CurrentNodeTypeButton = CastedBtn;
    }

    void LevelEditorGameController::SaveNodes() {
        SaveUtils.DataToSave = {};
        SaveUtils.GridType = m_Scene->GetCurrentGridType();
        if (m_Scene->GetCurrentGridType() == GameEngineImpl::GridType::Square) {
            auto Grid = m_Scene->GetSquareGrid();
            auto Nodes = Grid->GetNodes();
            for (auto &node: *Nodes) {
                if (node.DataHolder->GetCurrentNodeType() == GridImpl::NodeType::Portal) {
                    SaveUtils.DataToSave.push_back({node.Coordinates, node.DataHolder->GetCurrentNodeType(), node.DataHolder->GetLinkedPortal()->Node->Coordinates});
                } else {
                    SaveUtils.DataToSave.push_back({node.Coordinates, node.DataHolder->GetCurrentNodeType()});
                }
            }
        } else if (m_Scene->GetCurrentGridType() == GameEngineImpl::GridType::Hexagonal) {
            auto Grid = m_Scene->GetHexagonalGrid();
            auto Nodes = Grid->GetNodes();
            for (auto &node: *Nodes) {
                if (node.DataHolder->GetCurrentNodeType() == GridImpl::NodeType::Portal) {
                    SaveUtils.DataToSave.push_back({node.Coordinates, node.DataHolder->GetCurrentNodeType(), node.DataHolder->GetLinkedPortal()->Node->Coordinates});
                } else {
                    SaveUtils.DataToSave.push_back({node.Coordinates, node.DataHolder->GetCurrentNodeType()});
                }
            }
        }
        SaveUtils.SaveGame();
    }
} // Scenes