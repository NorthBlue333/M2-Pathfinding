#ifndef PATHFINDING_BASESCENE_H
#define PATHFINDING_BASESCENE_H

#include "BaseGameMode.h"
#include "IScene.h"

namespace GameEngine {
    template <typename SceneNameEnum, typename SceneType, typename GameModeType, typename GameControllerType>
    class BaseGameMode;

    template <typename SceneNameEnum, typename SceneType, typename GameModeType, typename GameControllerType>
    class BaseGameController;

    template <typename SceneNameEnum, typename SceneType, typename GameModeType, typename GameControllerType>
    class BaseScene : public IScene<SceneNameEnum> {
        // static_assert(std::is_base_of<BaseScene, SceneType>::value, "SceneType must inherit from BaseScene");
//        static_assert(std::is_base_of<BaseGameMode<SceneNameEnum, SceneType, GameModeType, GameControllerType>, GameModeType>::value,
//                      "GameModeType must inherit from BaseGameMode");
//        static_assert(
//                std::is_base_of<BaseGameController<SceneNameEnum, SceneType, GameModeType, GameControllerType>, GameControllerType>::value,
//                "GameControllerType must inherit from BaseGameController");
    public:
        explicit BaseScene(Game<SceneNameEnum> *Game);
        ~BaseScene() override;

        void ComputeInputs() override;
    protected:
        Game<SceneNameEnum>* m_Game;
        GameModeType* m_GameMode;

        GameModeType* InstanciateGameMode();
    };

} // GameEngine

#include "BaseScene.tpp"

#endif //PATHFINDING_BASESCENE_H
