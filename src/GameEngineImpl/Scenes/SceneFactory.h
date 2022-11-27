#ifndef PATHFINDING_SCENEFACTORY_H
#define PATHFINDING_SCENEFACTORY_H

#include "../../GameEngine/ISceneFactory.h"
#include "../common_types.h"

namespace GameEngineImpl {
    namespace Scenes {
        class SceneFactory : public GameEngine::ISceneFactory<GameSceneName> {
        public:
            explicit SceneFactory(GameType* Game);
            ~SceneFactory() override = default;

            GameEngine::IScene<GameSceneName>* CreateSceneFromName(GameSceneName Name) override;
        };

        SceneFactory* NewFactory(GameType* Game);
    }

} // GameEngineImpl

#endif //PATHFINDING_SCENEFACTORY_H
