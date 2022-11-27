#include "BaseGameMode.h"

namespace GameEngine {
    template <typename SceneNameEnum, typename SceneType, typename GameModeType, typename GameControllerType>
    BaseGameMode<SceneNameEnum, SceneType, GameModeType, GameControllerType>::BaseGameMode(Game<SceneNameEnum> *Game, SceneType *Scene) : m_Game(Game), m_Scene(Scene) {
        m_GameController = InstanciateGameController();
    }

    template <typename SceneNameEnum, typename SceneType, typename GameModeType, typename GameControllerType>
    void BaseGameMode<SceneNameEnum, SceneType, GameModeType, GameControllerType>::ComputeInputs() {
        m_GameController->ComputeInputs();
    }

    template<typename SceneNameEnum, typename SceneType, typename GameModeType, typename GameControllerType>
    GameControllerType *
    BaseGameMode<SceneNameEnum, SceneType, GameModeType, GameControllerType>::InstanciateGameController() {
        return new GameControllerType(m_Game, m_Scene, static_cast<GameModeType*>(this));
    }
}
