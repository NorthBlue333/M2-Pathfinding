#ifndef PATHFINDING_MAINMENUGAMEMODE_H
#define PATHFINDING_MAINMENUGAMEMODE_H

#include "../../Game.h"
#include "MainMenuGameController.h"

namespace GameEngineImpl::Scenes::MainMenu {
    class MainMenuScene;

    class MainMenuGameMode : public BaseGameModeType<MainMenuScene, MainMenuGameMode, MainMenuGameController> {
    public:
        MainMenuGameMode(Game* Game, MainMenuScene* Scene);
        ~MainMenuGameMode() override = default;
    };

} // Scenes

#endif //PATHFINDING_MAINMENUGAMEMODE_H
