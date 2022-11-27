#ifndef PATHFINDING_BASEGAMECONTROLLER_H
#define PATHFINDING_BASEGAMECONTROLLER_H

#include <type_traits>

namespace GameEngine {
    template<typename SceneNameEnum>
    class Game;

    template<typename SceneNameEnum, typename SceneType, typename GameModeType, typename GameControllerType>
    class BaseGameMode;

    template<typename SceneNameEnum, typename SceneType, typename GameModeType, typename GameControllerType>
    class BaseScene;

    template<typename SceneNameEnum, typename SceneType, typename GameModeType, typename GameControllerType>
    class BaseGameController {
//        static_assert(
//                std::is_base_of<BaseScene<SceneNameEnum, SceneType, GameModeType, GameControllerType>, SceneType>::value,
//                "SceneType must inherit from BaseScene");
//        static_assert(
//                std::is_base_of<BaseGameMode<SceneNameEnum, SceneType, GameModeType, GameControllerType>, GameModeType>::value,
//                "GameModeType must inherit from BaseGameMode");
//        static_assert(std::is_base_of<BaseGameController, GameControllerType>::value,
//                      "GameControllerType must inherit from BaseGameController");

    public:
        BaseGameController(Game<SceneNameEnum> *Game, SceneType *Scene, GameModeType *GameMode);
        virtual ~BaseGameController() = default;

        virtual void ComputeInputs() = 0;

    protected:
        Game<SceneNameEnum> *m_Game;
        SceneType *m_Scene;
        GameModeType *m_GameMode;
    };
}

#include "BaseGameController.tpp"

#endif //PATHFINDING_BASEGAMECONTROLLER_H
