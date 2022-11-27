#ifndef PATHFINDING_LEVELEDITORGAMEMODE_H
#define PATHFINDING_LEVELEDITORGAMEMODE_H

#include "../../common_types.h"
#include "LevelEditorGameController.h"

namespace GameEngineImpl {
    namespace Scenes {
        class LevelEditorScene;

        class LevelEditorGameMode : public BaseGameModeType<LevelEditorScene, LevelEditorGameMode, LevelEditorGameController> {
        public:
            LevelEditorGameMode(GameType* Game, LevelEditorScene* Scene);
            ~LevelEditorGameMode() override = default;
        };

    } // GameEngineImpl
} // Scenes

#endif //PATHFINDING_LEVELEDITORGAMEMODE_H
