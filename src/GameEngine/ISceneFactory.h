#ifndef PATHFINDING_ISCENEFACTORY_H
#define PATHFINDING_ISCENEFACTORY_H

#include <type_traits>
#include "IScene.h"

namespace GameEngine {
    template <typename GameType, typename SceneNameEnum>
    class ISceneFactory {
        static_assert(std::is_enum<SceneNameEnum>::value, "SceneNameEnum must be enum");
    public:
        explicit ISceneFactory(GameType* Game);
        virtual ~ISceneFactory() = default;

        virtual IScene<GameType, SceneNameEnum>* CreateSceneFromName(SceneNameEnum Name) = 0;
    protected:
        GameType* m_Game;
    };

} // GameEngine

#include "ISceneFactory.tpp"

#endif //PATHFINDING_ISCENEFACTORY_H
