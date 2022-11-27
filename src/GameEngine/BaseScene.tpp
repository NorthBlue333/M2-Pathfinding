#include "BaseScene.h"

namespace GameEngine {
    template<typename SceneNameEnum, typename SceneType, typename GameModeType, typename GameControllerType>
    BaseScene<SceneNameEnum, SceneType, GameModeType, GameControllerType>::BaseScene(Game<SceneNameEnum> *Game)
            : m_Game(Game), m_GameMode(nullptr) {
        m_GameMode = InstanciateGameMode();
    }

    template<typename SceneNameEnum, typename SceneType, typename GameModeType, typename GameControllerType>
    GameModeType *BaseScene<SceneNameEnum, SceneType, GameModeType, GameControllerType>::InstanciateGameMode() {
        return new GameModeType(m_Game, static_cast<SceneType*>(this));
    }

    template<typename SceneNameEnum, typename SceneType, typename GameModeType, typename GameControllerType>
    void BaseScene<SceneNameEnum, SceneType, GameModeType, GameControllerType>::ComputeInputs() {
        m_GameMode->ComputeInputs();
    }

    template<typename SceneNameEnum, typename SceneType, typename GameModeType, typename GameControllerType>
    BaseScene<SceneNameEnum, SceneType, GameModeType, GameControllerType>::~BaseScene() {
        delete m_GameMode;
    }
} // GameEngine