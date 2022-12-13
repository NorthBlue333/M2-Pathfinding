#ifndef PATHFINDING_GAME_H
#define PATHFINDING_GAME_H

#include <SFML/Graphics.hpp>
#include "IScene.h"
#include "ISceneFactory.h"
#include <functional>

namespace GameEngine {
    template <typename SceneNameEnum>
    class Game {
        static_assert(std::is_enum<SceneNameEnum>::value, "SceneNameEnum must be enum");
    private:
        using SceneFactoryConstructor = std::function<ISceneFactory<SceneNameEnum>*(Game*)>;
    public:
        Game(
            SceneNameEnum DefaultSceneName,
            SceneFactoryConstructor SceneFactoryConstructor,
            unsigned int WindowWidth = 1200,
            unsigned int WindowHeight = 1000,
            int FixedRateInMillis = 10
        );
        ~Game();

        int Run();
        void LoadScene(SceneNameEnum SceneName);

        void StopGame();

        sf::RenderWindow* GetWindow();
    private:
        SceneFactoryConstructor m_SceneFactoryConstructor;
        SceneNameEnum m_CurrentSceneName;
        SceneNameEnum m_SceneNameToLoad;
        IScene<SceneNameEnum>* m_CurrentScene;

        unsigned int m_WindowWidth;
        unsigned int m_WindowHeight;
        int m_FixedRateInMillis;
        sf::RenderWindow m_Window;

        void ExecuteLoadScene();

        void ComputeInputs();
        void ExecuteCalculations(sf::Time Elapsed);
        void Render();
    };
}

#include "Game.tpp"

#endif //PATHFINDING_GAME_H
