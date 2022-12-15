#ifndef PATHFINDING_BASESCENE_H
#define PATHFINDING_BASESCENE_H

#include "BaseGameMode.h"
#include "IScene.h"

namespace GameEngine {
    template <typename GameType, typename SceneNameEnum, typename SceneType, typename GameModeType, typename GameControllerType>
    class BaseScene : public IScene<GameType, SceneNameEnum> {
    public:
        explicit BaseScene(GameType *Game);
        ~BaseScene() override;

        void ComputeInputs() override;
    protected:
        GameType* m_Game;
        GameModeType* m_GameMode;

        GameModeType* InstanciateGameMode();
    };

} // GameEngine

#include "BaseScene.tpp"

#endif //PATHFINDING_BASESCENE_H
