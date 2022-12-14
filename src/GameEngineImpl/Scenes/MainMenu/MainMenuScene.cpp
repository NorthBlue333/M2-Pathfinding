#include "MainMenuScene.h"
#include "../../../UserInterface/TextButton.h"
#include <iostream>

namespace GameEngineImpl::Scenes::MainMenu {
    MainMenuScene::MainMenuScene(Game *Game) : BaseScene(Game), m_Title(sf::Text()) {

    }

    void MainMenuScene::ExecuteCalculations(sf::Time Elapsed) {

    }

    void MainMenuScene::Render() {
        auto Window = m_Game->GetWindow();
        Window->draw(m_Title);
        for (auto &button : m_Buttons) {
            button->Render(Window);
        }
    }

    void MainMenuScene::Load() {
        auto newFont = new sf::Font;
        newFont->loadFromFile("./assets/anek_devanagari/static/AnekDevanagari/AnekDevanagari-Bold.ttf");
        m_Fonts.insert({MainMenuFont::AnekDevanagari, newFont});

        // initial state
        ChangeCurrentState(m_CurrentState);
    }

    MainMenuScene::~MainMenuScene() {
        for (auto & Button : m_Buttons) {
            delete Button;
        }
    }

    void MainMenuScene::SetTitle(const sf::String &Text) {
        m_Title = sf::Text(Text, *m_Fonts.at(MainMenuFont::AnekDevanagari), TITLE_TEXT_SIZE);
        m_Title.setPosition(200, 30);
    }

    void MainMenuScene::AddButton(
            const sf::String &Text,
            const UI::TextButton::EventType& OnClick
    ) {
        auto YOffset = TITLE_TEXT_SIZE + 60 + (m_Buttons.size() * (BUTTON_TEXT_SIZE + 50));
        auto NewButton = new UI::TextButton(Text, *m_Fonts.at(MainMenuFont::AnekDevanagari), BUTTON_TEXT_SIZE);
        m_Buttons.push_back(NewButton);
        NewButton->SetPosition(30, YOffset);

        if (nullptr != OnClick)
            NewButton->SetOnClick(OnClick);
    }

    void MainMenuScene::ChangeCurrentState(MainMenuState NewState) {
        m_CurrentState = NewState;
        m_Buttons.clear();
        switch (m_CurrentState) {
            case MainMenuState::LevelSelect:
                ShowLevelSelectState();
                break;
            case MainMenuState::Main:
            default:
                ShowMainState();
                break;
        }
    }

    void MainMenuScene::ShowMainState() {
        SetTitle("Main menu");
        // @todo add multiple levels
//        AddButton("Select level", [this](auto && Btn) { ChangeCurrentState(MainMenuState::LevelSelect); });
        AddButton("Select level", [this](auto && Btn) {
            m_GameMode->GetGameController()->LoadSave();
            m_Game->LoadScene(GameSceneName::PlayGame);
            // testing
//            m_Game->LoadedSavedData = {
//                {Grid::Coordinates2D{2, 6}, GridImpl::NodeType::PlayerStart},
//                {Grid::Coordinates2D{4, 8}, GridImpl::NodeType::Portal, {9, 13}},
//                {Grid::Coordinates2D{9, 13}, GridImpl::NodeType::Portal, {4, 8}},
//                {Grid::Coordinates2D{7, 4}, GridImpl::NodeType::Empty},
//                {Grid::Coordinates2D{8, 2}, GridImpl::NodeType::Empty},
//                {Grid::Coordinates2D{15, 15}, GridImpl::NodeType::Empty},
//                {Grid::Coordinates2D{21, 19}, GridImpl::NodeType::Empty},
//                {Grid::Coordinates2D{30, 10}, GridImpl::NodeType::Empty},
//                {Grid::Coordinates2D{18, 15}, GridImpl::NodeType::Empty}
//            };
        });
        AddButton("Level editor", [this](auto && Btn) { m_Game->LoadScene(GameSceneName::LevelEditor); });
        AddButton("Quit", [this](auto && Btn) { m_Game->StopGame(); });
    }

    void MainMenuScene::ShowLevelSelectState() {
        SetTitle("Select level");
        AddButton("Back to main menu", [this](auto && Btn) { ChangeCurrentState(MainMenuState::Main); });
    }

    std::vector<UI::IButton*>& MainMenuScene::GetButtons() {
        return m_Buttons;
    }
} // Scenes