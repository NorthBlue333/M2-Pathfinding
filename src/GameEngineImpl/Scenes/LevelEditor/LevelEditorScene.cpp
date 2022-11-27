#include "LevelEditorScene.h"
#include "../../../UserInterface/SquareSpriteButton.h"

namespace GameEngineImpl::Scenes {
        LevelEditorScene::LevelEditorScene(GameType *Game) : BaseScene(Game), m_LevelEditorFont(nullptr), m_BackButton(nullptr) {

        }

        void LevelEditorScene::ExecuteCalculations(sf::Time Elapsed) {

        }

        void LevelEditorScene::Render() {
            auto Window = m_Game->GetWindow();
            m_BackButton->Render(Window);
            for (auto &button : m_EditorButtons) {
                button->Render(Window);
            }
        }

        void LevelEditorScene::Load() {
            auto newFont = new sf::Font;
            newFont->loadFromFile("../assets/anek_devanagari/static/AnekDevanagari/AnekDevanagari-Bold.ttf");
            m_LevelEditorFont = newFont;

            auto squareTexture = new sf::Texture;
            squareTexture->loadFromFile("../assets/textures/square.png");
            m_Textures.insert({LevelEditorTextureName::Square, squareTexture});

            m_BackButton = new UI::TextButton("Back to main menu", *m_LevelEditorFont);
            m_BackButton->SetPosition(10, 10);
            m_BackButton->SetOnClick([this](auto && Btn) { m_Game->LoadScene(GameSceneName::MainMenu); });

            AddButton(squareTexture, "Square");
            AddButton(squareTexture, "Squara");
        }

        LevelEditorScene::~LevelEditorScene() {
            delete m_LevelEditorFont;

            for (auto & Texture : m_Textures) {
                delete Texture.second;
            }
        }

        std::vector<UI::IButton*> LevelEditorScene::GetButtons() {
            std::vector<UI::IButton*> buttons{m_EditorButtons};
            buttons.push_back(m_BackButton);
            return buttons;
        }

        void LevelEditorScene::AddButton(const sf::Texture *Texture, const sf::String &Name) {
            auto width = 100.f;
            auto height = 120.f;
            auto margin = 10.f;
            auto newButton = new UI::SquareSpriteButton(Texture, Name, *m_LevelEditorFont, width, height, 14.f);
            auto WindowSize = m_Game->GetWindow()->getSize();
            newButton->SetPosition(margin + ((margin + width) * (float) m_EditorButtons.size()), WindowSize.y - height - margin);
            m_EditorButtons.push_back(newButton);
        }

} // Scenes