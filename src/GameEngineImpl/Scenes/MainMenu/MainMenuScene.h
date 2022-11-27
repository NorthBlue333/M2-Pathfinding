#ifndef PATHFINDING_MAINMENUSCENE_H
#define PATHFINDING_MAINMENUSCENE_H

#include "../../../GameEngine/BaseScene.h"
#include "../../common_types.h"
#include "MainMenuGameMode.h"
#include "../../../UserInterface/IButton.h"
#include <vector>

namespace GameEngineImpl {
    namespace Scenes {
        enum MainMenuState {
            Main = 0,
            LevelSelect,
        };

        class MainMenuScene : public BaseSceneType<MainMenuScene, MainMenuGameMode, MainMenuGameController> {
        public:
            explicit MainMenuScene(GameType* Game);
            ~MainMenuScene() override;

            void Load() override;
            void ExecuteCalculations(sf::Time Elapsed) override;
            void Render() override;

            std::vector<UI::IButton*>& GetButtons();
        protected:
            MainMenuState m_CurrentState = MainMenuState::Main;

            static int constexpr TITLE_TEXT_SIZE = 30;
            static int constexpr BUTTON_TEXT_SIZE = 30;
            sf::Font* m_MainMenuFont;

            sf::Text m_Title;
            std::vector<UI::IButton*> m_Buttons;

            void SetTitle(const sf::String &Text);
            void AddButton(
                    const sf::String &Text,
                    const UI::IButton::EventType& OnClick = nullptr
            );

            void ChangeCurrentState(MainMenuState NewState);
            void ShowMainState();
            void ShowLevelSelectState();
        };

    } // GameEngineImpl
} // Scenes

#endif //PATHFINDING_MAINMENUSCENE_H
