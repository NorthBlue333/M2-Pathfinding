#include "BaseGameController.h"

namespace GameEngine {
    template<typename SceneNameEnum, typename SceneType, typename GameModeType, typename GameControllerType>
    BaseGameController<SceneNameEnum, SceneType, GameModeType, GameControllerType>::BaseGameController(Game<SceneNameEnum> *Game, SceneType *Scene, GameModeType *GameMode)
            : m_Game(Game), m_Scene(Scene), m_GameMode(GameMode) {

    }
}
