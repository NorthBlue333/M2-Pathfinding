#include "ISceneFactory.h"

namespace GameEngine {
    template<typename SceneNameEnum>
    ISceneFactory<SceneNameEnum>::ISceneFactory(Game<SceneNameEnum> *Game) : m_Game(Game) {

    }
} // GameEngine