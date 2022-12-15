#ifndef PATHFINDING_PLAYGAMEGAMEMODE_H
#define PATHFINDING_PLAYGAMEGAMEMODE_H

#include "../../Game.h"
#include "PlayGameGameController.h"

namespace GameEngineImpl::Scenes::PlayGame {
    class PlayGameScene;

    class PlayGameGameMode : public BaseGameModeType<PlayGameScene, PlayGameGameMode, PlayGameGameController> {
    public:
        PlayGameGameMode(Game* Game, PlayGameScene* Scene);
        ~PlayGameGameMode() override = default;
    };

} // Scenes

#endif //PATHFINDING_PLAYGAMEGAMEMODE_H
