#ifndef PATHFINDING_ISCENE_H
#define PATHFINDING_ISCENE_H

#include <SFML/Graphics.hpp>

namespace GameEngine {
    template <typename GameType, typename SceneNameEnum>
    class IScene {
    public:
        virtual ~IScene() = default;

        virtual void Load() = 0;
        virtual void ComputeInputs() = 0;
        virtual void ExecuteCalculations(sf::Time Elapsed) = 0;
        virtual void Render() = 0;
    };

} // GameEngine

#include "IScene.tpp"

#endif //PATHFINDING_ISCENE_H
