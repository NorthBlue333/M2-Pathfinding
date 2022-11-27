#include "LevelEditorGameController.h"
#include "LevelEditorGameController.h"
#include "LevelEditorScene.h"

namespace GameEngineImpl {
    namespace Scenes {
        LevelEditorGameController::LevelEditorGameController(
                GameType *Game,
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

                if (
                        sf::Event::MouseButtonPressed == event.type
                        && sf::Mouse::Button::Left == event.mouseButton.button
                )
                    HandleOnMouseLeft(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
            }

            HandleOnMouseHover(Window->mapPixelToCoords(sf::Mouse::getPosition(*Window)));
        }

        void LevelEditorGameController::HandleOnMouseLeft(sf::Vector2f MousePosition) {
            for (auto & button : m_Scene->GetButtons()) {
                if (!button->GetGlobalBounds().contains(MousePosition))
                    continue;

                button->Click();
            }
        }

        void LevelEditorGameController::HandleOnMouseHover(sf::Vector2f MousePosition) {
            for (auto & button : m_Scene->GetButtons()) {
                button->Hover(button->GetGlobalBounds().contains(MousePosition));
            }
        }
    } // GameEngineImpl
} // Scenes