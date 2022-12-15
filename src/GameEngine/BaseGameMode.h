#ifndef PATHFINDING_BASEGAMEMODE_H
#define PATHFINDING_BASEGAMEMODE_H

#include <type_traits>
#include "BaseGameController.h"

namespace GameEngine {
    template <typename GameType, typename SceneNameEnum, typename SceneType, typename GameModeType, typename GameControllerType>
    class BaseGameMode {
    public:
        explicit BaseGameMode(GameType* Game, SceneType* Scene);
        virtual ~BaseGameMode();

        void ComputeInputs();

        GameControllerType* GetGameController() const;
    protected:
        GameType* m_Game;
        SceneType* m_Scene;
        GameControllerType* m_GameController;

        GameControllerType* InstanciateGameController();
    };
}

#include "BaseGameMode.tpp"

#endif //PATHFINDING_BASEGAMEMODE_H
