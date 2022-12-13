#include "MainMenuScene.h"
#include "MainMenuGameMode.h"
#include "MainMenuGameController.h"

namespace GameEngineImpl {
    namespace Scenes {
        MainMenuGameController::MainMenuGameController(
                GameType *Game,
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
        }
    } // GameEngineImpl
} // Scenes