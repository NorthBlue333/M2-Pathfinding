#ifndef PATHFINDING_GAME_H
#define PATHFINDING_GAME_H

#include "../GameEngine/BaseGame.h"
#include "common_types.h"

namespace GameEngineImpl {
    class Game : public GameEngine::BaseGame<Game, GameSceneName> {
        using GameEngine::BaseGame<Game, GameSceneName>::BaseGame;

        // @todo add current level to load
    };

    using ISceneType = GameEngine::IScene<Game, GameSceneName>;

    template <typename SceneType, typename GameModeType, typename GameControllerType>
    using BaseSceneType = GameEngine::BaseScene<Game, GameSceneName, SceneType, GameModeType, GameControllerType>;

    template <typename SceneType, typename GameModeType, typename GameControllerType>
    using BaseGameModeType = GameEngine::BaseGameMode<Game, GameSceneName, SceneType, GameModeType, GameControllerType>;

    template <typename SceneType, typename GameModeType, typename GameControllerType>
    using BaseGameControllerType = GameEngine::BaseGameController<Game, GameSceneName, SceneType, GameModeType, GameControllerType>;

} // GameEngineImpl

#endif //PATHFINDING_GAME_H
