#ifndef PATHFINDING_BASEGAMEMODE_H
#define PATHFINDING_BASEGAMEMODE_H

#include <type_traits>
#include "BaseGameController.h"

namespace GameEngine {
    template <typename SceneNameEnum>
    class Game;
    template <typename SceneNameEnum, typename SceneType, typename GameModeType, typename GameControllerType>
    class BaseScene;

    template <typename SceneNameEnum, typename SceneType, typename GameModeType, typename GameControllerType>
    class BaseGameMode {
//        static_assert(std::is_base_of<BaseScene<SceneNameEnum, SceneType, GameModeType, GameControllerType>, SceneType>::value, "SceneType must inherit from BaseScene");
//        static_assert(std::is_base_of<BaseGameMode, GameModeType>::value,
//                      "GameModeType must inherit from BaseGameMode");
//        static_assert(
//                std::is_base_of<BaseGameController<SceneNameEnum, SceneType, GameModeType, GameControllerType>, GameControllerType>::value,
//                "GameControllerType must inherit from BaseGameController");

    public:
        explicit BaseGameMode(Game<SceneNameEnum>* Game, SceneType* Scene);
        virtual ~BaseGameMode();

        void ComputeInputs();
    protected:
        Game<SceneNameEnum>* m_Game;
        SceneType* m_Scene;
        GameControllerType* m_GameController;

        GameControllerType* InstanciateGameController();
    };
}

#include "BaseGameMode.tpp"

#endif //PATHFINDING_BASEGAMEMODE_H
