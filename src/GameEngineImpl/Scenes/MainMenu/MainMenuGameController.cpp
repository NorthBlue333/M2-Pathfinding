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

                if (
                        sf::Event::MouseButtonPressed == event.type
                        && sf::Mouse::Button::Left == event.mouseButton.button
                )
                    HandleOnMouseLeft(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
            }
        }

        void MainMenuGameController::HandleOnMouseLeft(sf::Vector2f MousePosition) {
            for (auto & button : m_Scene->GetButtons()) {
                if (!button->GetGlobalBounds().contains(MousePosition))
                    continue;

                button->Click();
            }
        }
    } // GameEngineImpl
} // Scenes