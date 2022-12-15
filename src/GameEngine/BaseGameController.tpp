#include "BaseGameController.h"

namespace GameEngine {
    template<typename GameType, typename SceneNameEnum, typename SceneType, typename GameModeType, typename GameControllerType>
    BaseGameController<GameType, SceneNameEnum, SceneType, GameModeType, GameControllerType>::BaseGameController(GameType *Game, SceneType *Scene, GameModeType *GameMode)
            : m_Game(Game), m_Scene(Scene), m_GameMode(GameMode) {

    }
}
