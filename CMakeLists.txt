cmake_minimum_required(VERSION 3.16)
project(pathfinding)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        pathfinding
        src/main.cpp
        src/GameEngine/Game.h
        src/GameEngine/Game.tpp
        src/GameEngine/BaseGameMode.h
        src/GameEngine/BaseGameMode.tpp
        src/GameEngine/BaseGameController.h
        src/GameEngine/BaseGameController.tpp
        src/GameEngine/BaseScene.h
        src/GameEngine/BaseScene.tpp
        src/GameEngine/ISceneFactory.h
        src/GameEngine/ISceneFactory.tpp
        src/GameEngine/IScene.h
        src/GameEngine/IScene.tpp
        src/GameEngineImpl/Scenes/SceneFactory.h
        src/GameEngineImpl/Scenes/SceneFactory.cpp
        src/GameEngineImpl/common_types.h
        src/GameEngineImpl/Scenes/MainMenu/MainMenuScene.cpp
        src/GameEngineImpl/Scenes/MainMenu/MainMenuScene.h
        src/GameEngineImpl/Scenes/MainMenu/MainMenuGameController.cpp
        src/GameEngineImpl/Scenes/MainMenu/MainMenuGameController.h
        src/GameEngineImpl/Scenes/MainMenu/MainMenuGameMode.cpp
        src/GameEngineImpl/Scenes/MainMenu/MainMenuGameMode.h
        src/UserInterface/IButton.cpp
        src/UserInterface/IButton.h
        src/UserInterface/TextButton.cpp
        src/UserInterface/TextButton.h
        src/GameEngineImpl/Scenes/LevelEditor/LevelEditorScene.cpp
        src/GameEngineImpl/Scenes/LevelEditor/LevelEditorScene.h
        src/GameEngineImpl/Scenes/LevelEditor/LevelEditorGameController.cpp
        src/GameEngineImpl/Scenes/LevelEditor/LevelEditorGameController.h
        src/GameEngineImpl/Scenes/LevelEditor/LevelEditorGameMode.cpp
        src/GameEngineImpl/Scenes/LevelEditor/LevelEditorGameMode.h
        src/UserInterface/TextButton.cpp
        src/UserInterface/TextButton.h src/UserInterface/TextButton.cpp
        src/UserInterface/TextButton.h src/UserInterface/SquareSpriteButton.cpp
        src/UserInterface/SquareSpriteButton.h src/Utilities/PositionUtilities.cpp
        src/Utilities/PositionUtilities.h src/GameEngineImpl/Scenes/Traits/HasTextures.tpp
        src/GameEngineImpl/Scenes/Traits/HasTextures.h src/Grid/BaseGrid.tpp
        src/Grid/BaseGrid.h src/Grid/RenderableGrid.h src/Grid/RenderableGrid.tpp
        src/Grid/HexagonalGrid.tpp
        src/Grid/HexagonalGrid.h src/Grid/SquareGrid.h src/Grid/SquareGrid.tpp
        src/Grid/HexagonalGrid.cpp
        src/UserInterface/GridNodeButton.h src/UserInterface/GridNodeButton.cpp src/PathFinding/Graph.cpp src/PathFinding/Graph.h src/PathFinding/GraphFactory.cpp src/PathFinding/GraphFactory.h src/PathFinding/Heuristic.h src/PathFinding/Node.cpp src/PathFinding/Node.h src/GameEngineImpl/Scenes/LevelEditor/LevelEditorScene.tpp src/GridImpl/GridsWithPortals.tpp src/GridImpl/GridsWithPortals.h src/GridImpl/GridWithPortals.cpp src/PathFinding/Algorithm.tpp src/PathFinding/Algorithm.h src/PathFinding/AStar.h)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
target_link_libraries(pathfinding PRIVATE sfml-system sfml-network sfml-graphics sfml-window)
