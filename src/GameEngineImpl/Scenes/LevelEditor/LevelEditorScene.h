#ifndef PATHFINDING_LEVELEDITORSCENE_H
#define PATHFINDING_LEVELEDITORSCENE_H

#include "../../../GameEngine/BaseScene.h"
#include "../../common_types.h"
#include "LevelEditorGameMode.h"
#include "../../../UserInterface/IButton.h"
#include "../../../UserInterface/TextButton.h"
#include <vector>
#include <map>

namespace GameEngineImpl {
    namespace Scenes {
        enum LevelEditorTextureName {
            Square = 0,
        };

        class LevelEditorScene : public BaseSceneType<LevelEditorScene, LevelEditorGameMode, LevelEditorGameController> {
        public:
            explicit LevelEditorScene(GameType* Game);
            ~LevelEditorScene() override;

            void Load() override;
            void ExecuteCalculations(sf::Time Elapsed) override;
            void Render() override;

            std::vector<UI::IButton*> GetButtons();
        protected:
            static int constexpr BUTTON_TEXT_SIZE = 30;
            sf::Font* m_LevelEditorFont;
            std::map<LevelEditorTextureName, sf::Texture*> m_Textures;

            sf::Text Title;
            UI::TextButton* m_BackButton;
            std::vector<UI::IButton*> m_EditorButtons;

            void AddButton(
                    const sf::Texture *Texture,
                    const sf::String& Name
            );
        };

    } // GameEngineImpl
} // Scenes

#endif //PATHFINDING_LEVELEDITORSCENE_H
