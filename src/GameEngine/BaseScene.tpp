#include "BaseScene.h"

namespace GameEngine {
    template<typename GameType, typename SceneNameEnum, typename SceneType, typename GameModeType, typename GameControllerType>
    BaseScene<GameType, SceneNameEnum, SceneType, GameModeType, GameControllerType>::BaseScene(GameType *Game)
            : m_Game(Game), m_GameMode(nullptr) {
        m_GameMode = InstanciateGameMode();
    }

    template<typename GameType, typename SceneNameEnum, typename SceneType, typename GameModeType, typename GameControllerType>
    GameModeType *BaseScene<GameType, SceneNameEnum, SceneType, GameModeType, GameControllerType>::InstanciateGameMode() {
        return new GameModeType(m_Game, static_cast<SceneType*>(this));
    }

    template<typename GameType, typename SceneNameEnum, typename SceneType, typename GameModeType, typename GameControllerType>
    void BaseScene<GameType, SceneNameEnum, SceneType, GameModeType, GameControllerType>::ComputeInputs() {
        m_GameMode->ComputeInputs();
    }

    template<typename GameType, typename SceneNameEnum, typename SceneType, typename GameModeType, typename GameControllerType>
    BaseScene<GameType, SceneNameEnum, SceneType, GameModeType, GameControllerType>::~BaseScene() {
        delete m_GameMode;
    }
} // GameEngine