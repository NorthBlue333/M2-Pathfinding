#include "BaseGame.h"

namespace GameEngine {
    template<typename GameType, typename SceneNameEnum>
    BaseGame<GameType, SceneNameEnum>::BaseGame(SceneNameEnum DefaultSceneName, BaseGame<GameType, SceneNameEnum>::SceneFactoryConstructor SceneFactoryConstructor,
                              unsigned int WindowWidth, unsigned int WindowHeight,
                              int FixedRateInMillis) :
            m_SceneFactoryConstructor(SceneFactoryConstructor),
            m_CurrentScene(nullptr),
            m_Window(sf::RenderWindow(sf::VideoMode(WindowWidth, WindowHeight), "DragBox")),
            m_WindowWidth(WindowWidth),
            m_WindowHeight(WindowHeight),
            m_FixedRateInMillis(FixedRateInMillis)
    {
        m_CurrentSceneName = DefaultSceneName;
        m_SceneNameToLoad = DefaultSceneName;
        ExecuteLoadScene();
    }

    template<typename GameType, typename SceneNameEnum>
    int BaseGame<GameType, SceneNameEnum>::Run() {
        sf::Clock clock;
        while (m_Window.isOpen()) {
            sf::Time Elapsed = clock.restart();

            if (m_SceneNameToLoad != m_CurrentSceneName)
                ExecuteLoadScene();
            ComputeInputs();
            ExecuteCalculations(Elapsed);
            Render();

            const auto ElapsedMillis = Elapsed.asMilliseconds();
            if (ElapsedMillis < m_FixedRateInMillis) {
                sf::sleep(sf::milliseconds(m_FixedRateInMillis - ElapsedMillis));
            }
        }
        return 0;
    }

    template<typename GameType, typename SceneNameEnum>
    void BaseGame<GameType, SceneNameEnum>::ComputeInputs() {
        if (nullptr == m_CurrentScene)
            return;

        m_CurrentScene->ComputeInputs();
    }

    template<typename GameType, typename SceneNameEnum>
    void BaseGame<GameType, SceneNameEnum>::ExecuteCalculations(sf::Time Elapsed) {
        if (nullptr == m_CurrentScene)
            return;

        m_CurrentScene->ExecuteCalculations(Elapsed);
    }

    template<typename GameType, typename SceneNameEnum>
    void BaseGame<GameType, SceneNameEnum>::Render() {
        if (nullptr == m_CurrentScene)
            return;

        m_Window.clear();

        m_CurrentScene->Render();

        m_Window.display();
    }

    template<typename GameType, typename SceneNameEnum>
    sf::RenderWindow *BaseGame<GameType, SceneNameEnum>::GetWindow() {
        return &m_Window;
    }

    /// Will load scene at next tick
    template<typename GameType, typename SceneNameEnum>
    void BaseGame<GameType, SceneNameEnum>::LoadScene(SceneNameEnum SceneName) {
        m_SceneNameToLoad = SceneName;
    }

    template<typename GameType, typename SceneNameEnum>
    BaseGame<GameType, SceneNameEnum>::~BaseGame() {
        delete m_CurrentScene;
    }

    template<typename GameType, typename SceneNameEnum>
    void BaseGame<GameType, SceneNameEnum>::StopGame() {
        m_Window.close();
    }

    template<typename GameType, typename SceneNameEnum>
    void BaseGame<GameType, SceneNameEnum>::ExecuteLoadScene() {
        auto Factory = std::invoke(m_SceneFactoryConstructor, static_cast<GameType*>(this));
        auto newScene = Factory->CreateSceneFromName(m_SceneNameToLoad);
        newScene->Load();
        delete m_CurrentScene;
        m_CurrentScene = newScene;
        m_CurrentSceneName = m_SceneNameToLoad;
    }
}
