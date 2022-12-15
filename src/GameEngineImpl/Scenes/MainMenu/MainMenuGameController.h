#ifndef PATHFINDING_MAINMENUGAMECONTROLLER_H
#define PATHFINDING_MAINMENUGAMECONTROLLER_H

#include "../../Game.h"
#include "../Traits/HasMouseEvents.h"

namespace GameEngineImpl::Scenes::MainMenu {
    class MainMenuScene;
    class MainMenuGameMode;

    class MainMenuGameController :
        public BaseGameControllerType<MainMenuScene, MainMenuGameMode, MainMenuGameController>,
        public Traits::HasMouseEvents
    {
    public:
        MainMenuGameController(Game* Game, MainMenuScene* Scene, MainMenuGameMode* GameMode);
        ~MainMenuGameController() override = default;

        void ComputeInputs() override;
    };

} // Scenes

#endif //PATHFINDING_MAINMENUGAMECONTROLLER_H
