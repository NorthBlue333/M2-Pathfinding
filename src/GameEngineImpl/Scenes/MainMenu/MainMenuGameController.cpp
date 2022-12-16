#include "MainMenuScene.h"
#include "MainMenuGameMode.h"
#include "MainMenuGameController.h"

namespace GameEngineImpl::Scenes::MainMenu {
    MainMenuGameController::MainMenuGameController(
            Game *Game,
            MainMenuScene* Scene,
            MainMenuGameMode *GameMode
    ) : BaseGameController(
            Game,
            Scene,
            GameMode
    ) {

    }

    void MainMenuGameController::ComputeInputs() {
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
        auto MouseCoords = Window->mapPixelToCoords(sf::Mouse::getPosition(*Window));
        auto Buttons = m_Scene->GetButtons();
        HandleOnMouseHover(MouseCoords, Buttons);
    }

    void MainMenuGameController::LoadSave() {
        GameEngineImpl::GridType SavedType;
        auto Data = SaveUtils.LoadSave("../Saves/save.txt", SavedType);
        m_Game->LoadedGridType = SavedType;
        m_Game->LoadedSavedData = Data;
    }
} // Scenes