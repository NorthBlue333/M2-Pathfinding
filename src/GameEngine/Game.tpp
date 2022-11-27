#include "Game.h"

namespace GameEngine {
    template<typename SceneNameEnum>
    Game<SceneNameEnum>::Game(SceneNameEnum DefaultSceneName, Game::SceneFactoryConstructor SceneFactoryConstructor,
                              unsigned int WindowWidth, unsigned int WindowHeight) :
            m_SceneFactoryConstructor(SceneFactoryConstructor),
            m_CurrentScene(nullptr),
            m_Window(sf::RenderWindow(sf::VideoMode(WindowWidth, WindowHeight), "DragBox")),
            m_WindowWidth(WindowWidth),
            m_WindowHeight(WindowHeight)
    {
        LoadScene(DefaultSceneName);
    }

    template<typename SceneNameEnum>
    int Game<SceneNameEnum>::Run() {
        sf::Clock clock;
        while (m_Window.isOpen()) {
            sf::Time Elapsed = clock.restart();
            if (m_SceneNameToLoad != m_CurrentSceneName)
                ExecuteLoadScene();
            ComputeInputs();
            ExecuteCalculations(Elapsed);
            Render();
        }
        return 0;
    }

    template<typename SceneNameEnum>
    void Game<SceneNameEnum>::ComputeInputs() {
        if (nullptr == m_CurrentScene)
            return;

        m_CurrentScene->ComputeInputs();
    }

    template<typename SceneNameEnum>
    void Game<SceneNameEnum>::ExecuteCalculations(sf::Time Elapsed) {
        if (nullptr == m_CurrentScene)
            return;

        m_CurrentScene->ExecuteCalculations(Elapsed);
    }

    template<typename SceneNameEnum>
    void Game<SceneNameEnum>::Render() {
        if (nullptr == m_CurrentScene)
            return;

        m_Window.clear();

        m_CurrentScene->Render();

        m_Window.display();
    }

    template<typename SceneNameEnum>
    sf::RenderWindow *Game<SceneNameEnum>::GetWindow() {
        return &m_Window;
    }

    /// Will load scene at next tick
    template<typename SceneNameEnum>
    void Game<SceneNameEnum>::LoadScene(SceneNameEnum SceneName) {
        m_SceneNameToLoad = SceneName;
    }

    template<typename SceneNameEnum>
    Game<SceneNameEnum>::~Game() {
        delete m_CurrentScene;
    }

    template<typename SceneNameEnum>
    void Game<SceneNameEnum>::StopGame() {
        m_Window.close();
    }

    template<typename SceneNameEnum>
    void Game<SceneNameEnum>::ExecuteLoadScene() {
        auto Factory = std::invoke(m_SceneFactoryConstructor, this);
        auto newScene = Factory->CreateSceneFromName(m_SceneNameToLoad);
        newScene->Load();
        delete m_CurrentScene;
        m_CurrentScene = newScene;
        m_CurrentSceneName = m_SceneNameToLoad;
    }
}
