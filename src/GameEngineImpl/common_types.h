#ifndef PATHFINDING_COMMON_TYPES_H
#define PATHFINDING_COMMON_TYPES_H

#include "../GameEngine/Game.h"
#include "../GameEngine/BaseScene.h"

namespace GameEngineImpl {
    enum GameSceneName {
        MainMenu = 0,
        LevelPlayer,
        LevelEditor,
    };

    using GameType = GameEngine::Game<GameSceneName>;
    using ISceneType = GameEngine::IScene<GameSceneName>;

    template <typename SceneType, typename GameModeType, typename GameControllerType>
    using BaseSceneType = GameEngine::BaseScene<GameSceneName, SceneType, GameModeType, GameControllerType>;

    template <typename SceneType, typename GameModeType, typename GameControllerType>
    using BaseGameModeType = GameEngine::BaseGameMode<GameSceneName, SceneType, GameModeType, GameControllerType>;

    template <typename SceneType, typename GameModeType, typename GameControllerType>
    using BaseGameControllerType = GameEngine::BaseGameController<GameSceneName, SceneType, GameModeType, GameControllerType>;
}

#endif //PATHFINDING_COMMON_TYPES_H
