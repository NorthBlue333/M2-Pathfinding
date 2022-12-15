#ifndef PATHFINDING_BASEGAMECONTROLLER_H
#define PATHFINDING_BASEGAMECONTROLLER_H

#include <type_traits>

namespace GameEngine {
    template<typename GameType, typename SceneNameEnum, typename SceneType, typename GameModeType, typename GameControllerType>
    class BaseGameController {
    public:
        BaseGameController(GameType *Game, SceneType *Scene, GameModeType *GameMode);
        virtual ~BaseGameController() = default;

        virtual void ComputeInputs() = 0;

    protected:
        GameType *m_Game;
        SceneType *m_Scene;
        GameModeType *m_GameMode;
    };
}

#include "BaseGameController.tpp"

#endif //PATHFINDING_BASEGAMECONTROLLER_H
