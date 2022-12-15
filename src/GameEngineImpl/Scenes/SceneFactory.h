#ifndef PATHFINDING_SCENEFACTORY_H
#define PATHFINDING_SCENEFACTORY_H

#include "../../GameEngine/ISceneFactory.h"
#include "../Game.h"

namespace GameEngineImpl {
    namespace Scenes {
        class SceneFactory : public GameEngine::ISceneFactory<Game, GameSceneName> {
        public:
            explicit SceneFactory(Game* Game);
            ~SceneFactory() override = default;

            ISceneType * CreateSceneFromName(GameSceneName Name) override;
        };

        SceneFactory* NewFactory(Game* Game);
    }

} // GameEngineImpl

#endif //PATHFINDING_SCENEFACTORY_H
