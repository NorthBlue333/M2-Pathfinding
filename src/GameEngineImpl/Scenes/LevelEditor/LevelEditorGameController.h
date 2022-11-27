#ifndef PATHFINDING_LEVELEDITORGAMECONTROLLER_H
#define PATHFINDING_LEVELEDITORGAMECONTROLLER_H

#include "../../common_types.h"

namespace GameEngineImpl {
    namespace Scenes {
        class LevelEditorScene;
        class LevelEditorGameMode;

        class LevelEditorGameController : public BaseGameControllerType<LevelEditorScene, LevelEditorGameMode, LevelEditorGameController> {
        public:
            LevelEditorGameController(GameType* Game, LevelEditorScene* Scene, LevelEditorGameMode* GameMode);
            ~LevelEditorGameController() override = default;

            void ComputeInputs() override;

        protected:
            void HandleOnMouseHover(sf::Vector2f MousePosition);
            void HandleOnMouseLeft(sf::Vector2f MousePosition);
        };

    } // GameEngineImpl
} // Scenes

#endif //PATHFINDING_LEVELEDITORGAMECONTROLLER_H
