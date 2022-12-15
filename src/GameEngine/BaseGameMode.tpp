#include "BaseGameMode.h"

namespace GameEngine {
    template <typename GameType, typename SceneNameEnum, typename SceneType, typename GameModeType, typename GameControllerType>
    BaseGameMode<GameType, SceneNameEnum, SceneType, GameModeType, GameControllerType>::BaseGameMode(GameType *Game, SceneType *Scene) : m_Game(Game), m_Scene(Scene) {
        m_GameController = InstanciateGameController();
    }

    template <typename GameType, typename SceneNameEnum, typename SceneType, typename GameModeType, typename GameControllerType>
    void BaseGameMode<GameType, SceneNameEnum, SceneType, GameModeType, GameControllerType>::ComputeInputs() {
        m_GameController->ComputeInputs();
    }

    template<typename GameType, typename SceneNameEnum, typename SceneType, typename GameModeType, typename GameControllerType>
    GameControllerType *
    BaseGameMode<GameType, SceneNameEnum, SceneType, GameModeType, GameControllerType>::InstanciateGameController() {
        return new GameControllerType(m_Game, m_Scene, static_cast<GameModeType*>(this));
    }
    template <typename GameType, typename SceneNameEnum, typename SceneType, typename GameModeType, typename GameControllerType>
    BaseGameMode<GameType, SceneNameEnum, SceneType, GameModeType, GameControllerType>::~BaseGameMode()
    {
        delete m_GameController;
    }

    template<typename GameType, typename SceneNameEnum, typename SceneType, typename GameModeType, typename GameControllerType>
    GameControllerType *
    BaseGameMode<GameType, SceneNameEnum, SceneType, GameModeType, GameControllerType>::GetGameController() const {
        return m_GameController;
    }
}
