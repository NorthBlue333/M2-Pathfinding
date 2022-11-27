#ifndef PATHFINDING_ISCENEFACTORY_H
#define PATHFINDING_ISCENEFACTORY_H

#include <type_traits>
#include "IScene.h"

namespace GameEngine {
    template <typename SceneNameEnum>
    class Game;

    template <typename SceneNameEnum>
    class ISceneFactory {
        static_assert(std::is_enum<SceneNameEnum>::value, "SceneNameEnum must be enum");
    public:
        explicit ISceneFactory(Game<SceneNameEnum>* Game);
        virtual ~ISceneFactory() = default;

        virtual IScene<SceneNameEnum>* CreateSceneFromName(SceneNameEnum Name) = 0;
    protected:
        Game<SceneNameEnum>* m_Game;
    };

} // GameEngine

#include "ISceneFactory.tpp"

#endif //PATHFINDING_ISCENEFACTORY_H
