#ifndef PATHFINDING_MAINMENUGAMECONTROLLER_H
#define PATHFINDING_MAINMENUGAMECONTROLLER_H

#include "../../common_types.h"
#include "../Traits/HasMouseEvents.h"

namespace GameEngineImpl {
    namespace Scenes {
        class MainMenuScene;
        class MainMenuGameMode;

        class MainMenuGameController :
            public BaseGameControllerType<MainMenuScene, MainMenuGameMode, MainMenuGameController>,
            public Traits::HasMouseEvents
        {
        public:
            MainMenuGameController(GameType* Game, MainMenuScene* Scene, MainMenuGameMode* GameMode);
            ~MainMenuGameController() override = default;

            void ComputeInputs() override;
        };

    } // GameEngineImpl
} // Scenes

#endif //PATHFINDING_MAINMENUGAMECONTROLLER_H
