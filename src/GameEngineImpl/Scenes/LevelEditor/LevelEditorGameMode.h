#ifndef PATHFINDING_LEVELEDITORGAMEMODE_H
#define PATHFINDING_LEVELEDITORGAMEMODE_H

#include "../../Game.h"
// @todo / @toask I do not understand why importing this class here overrides full class declaration
// of LevelEditorGameMode in LevelEditorScene
//#include "LevelEditorGameController.h"

namespace GameEngineImpl::Scenes::LevelEditor {
    class LevelEditorScene;
    class LevelEditorGameController;

    class LevelEditorGameMode : public BaseGameModeType<LevelEditorScene, LevelEditorGameMode, LevelEditorGameController> {
    public:
        LevelEditorGameMode(Game* Game, LevelEditorScene* Scene);
        ~LevelEditorGameMode() override = default;
    };

} // Scenes

#endif //PATHFINDING_LEVELEDITORGAMEMODE_H
