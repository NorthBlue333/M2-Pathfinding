#ifndef PATHFINDING_MAINMENUGAMEMODE_H
#define PATHFINDING_MAINMENUGAMEMODE_H

#include "../../common_types.h"
#include "MainMenuGameController.h"

namespace GameEngineImpl {
    namespace Scenes {
        class MainMenuScene;

        class MainMenuGameMode : public BaseGameModeType<MainMenuScene, MainMenuGameMode, MainMenuGameController> {
        public:
            MainMenuGameMode(GameType* Game, MainMenuScene* Scene);
            ~MainMenuGameMode() override = default;
        };

    } // GameEngineImpl
} // Scenes

#endif //PATHFINDING_MAINMENUGAMEMODE_H
