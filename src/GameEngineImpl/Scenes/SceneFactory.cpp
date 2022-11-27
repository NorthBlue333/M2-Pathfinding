#include "SceneFactory.h"
#include "MainMenu/MainMenuScene.h"
#include "LevelEditor/LevelEditorScene.h"
#include <stdexcept>

namespace GameEngineImpl {
    namespace Scenes {
        SceneFactory::SceneFactory(GameType *Game) : ISceneFactory(Game) {

        }

        GameEngine::IScene<GameSceneName>* SceneFactory::CreateSceneFromName(GameSceneName Name) {
            switch (Name) {
                case GameSceneName::MainMenu:
                    return new MainMenuScene(m_Game);
                case GameSceneName::LevelEditor:
                    return new LevelEditorScene(m_Game);
                default:
                    throw std::runtime_error("Unknown GameSceneName");
            }
        }

        SceneFactory* NewFactory(GameType *Game) {
            return new SceneFactory(Game);
        }
    }
} // GameEngineImpl