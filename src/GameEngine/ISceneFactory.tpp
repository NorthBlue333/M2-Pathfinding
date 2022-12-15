#include "ISceneFactory.h"

namespace GameEngine {
    template<typename GameType, typename SceneNameEnum>
    ISceneFactory<GameType, SceneNameEnum>::ISceneFactory(GameType *Game) : m_Game(Game) {

    }
} // GameEngine