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
} // Scenes