#ifndef PATHFINDING_PLAYGAMEGAMECONTROLLER_H
#define PATHFINDING_PLAYGAMEGAMECONTROLLER_H

#include "../../Game.h"
#include "../Traits/HasMouseEvents.h"
#include "../../../Grid/BaseGrid.h"

namespace GameEngineImpl::Scenes::PlayGame {
    class PlayGameScene;
    class PlayGameGameMode;

    class PlayGameGameController :
        public BaseGameControllerType<PlayGameScene, PlayGameGameMode, PlayGameGameController>,
        public Traits::HasMouseEvents
    {
    public:
        PlayGameGameController(Game* Game, PlayGameScene* Scene, PlayGameGameMode* GameMode);
        ~PlayGameGameController() override = default;

        void ComputeInputs() override;

        void HandleOnGridButtonClick(Grid::Coordinates2D& TargetNodeCoordinates, UI::IButton* Btn);

        void SaveNodes();

    };

} // Scenes

#endif //PATHFINDING_PLAYGAMEGAMECONTROLLER_H
