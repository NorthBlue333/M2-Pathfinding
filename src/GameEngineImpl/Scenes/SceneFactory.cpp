#include "SceneFactory.h"
#include "MainMenu/MainMenuScene.h"
#include "LevelEditor/LevelEditorScene.h"
#include "PlayGame/PlayGameScene.h"
#include <stdexcept>

namespace GameEngineImpl::Scenes {
    SceneFactory::SceneFactory(Game *Game) : ISceneFactory(Game) {

    }

    ISceneType * SceneFactory::CreateSceneFromName(GameSceneName Name) {
        switch (Name) {
            case GameSceneName::MainMenu:
                return new MainMenu::MainMenuScene(m_Game);
            case GameSceneName::LevelEditor:
                return new LevelEditor::LevelEditorScene(m_Game);
            case GameSceneName::PlayGame:
                return new PlayGame::PlayGameScene(m_Game);
            default:
                throw std::runtime_error("Unknown GameSceneName");
        }
    }

    SceneFactory* NewFactory(Game *Game) {
        return new SceneFactory(Game);
    }
} // GameEngineImpl