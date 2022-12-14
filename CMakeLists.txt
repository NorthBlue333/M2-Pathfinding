cmake_minimum_required(VERSION 3.16)
project(pathfinding)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        pathfinding
        src/main.cpp
        src/GameEngine/BaseGame.h
        src/GameEngine/BaseGame.tpp
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
        src/UserInterface/GridNodeButton.h src/UserInterface/GridNodeButton.cpp
        src/PathFinding/Heuristic.h
        src/GameEngineImpl/Scenes/LevelEditor/LevelEditorScene.tpp src/GridImpl/GridsWithPortals.tpp src/GridImpl/GridsWithPortals.h src/GridImpl/GridWithPortals.cpp
        src/PathFinding/Algorithm.tpp src/PathFinding/Algorithm.h src/PathFinding/AStar.h src/GameEngineImpl/Scenes/Traits/HasMouseEvents.cpp
        src/GameEngineImpl/Scenes/Traits/HasMouseEvents.h
        src/GameEngineImpl/Scenes/LevelEditor/common.h src/GameEngineImpl/Scenes/LevelEditor/common.tpp
        src/GameEngineImpl/Scenes/LevelEditor/LevelEditorGameController.tpp src/PathFinding/AStar.tpp src/GameEngineImpl/Scenes/PlayGame/PlayGameGameController.cpp src/GameEngineImpl/Scenes/PlayGame/PlayGameGameController.h src/GameEngineImpl/Scenes/PlayGame/PlayGameGameMode.cpp src/GameEngineImpl/Scenes/PlayGame/PlayGameGameMode.h src/GameEngineImpl/Scenes/PlayGame/PlayGameScene.cpp src/GameEngineImpl/Scenes/PlayGame/PlayGameScene.h src/GameEngineImpl/Game.cpp src/GameEngineImpl/Game.h src/GameEngineImpl/Scenes/PlayGame/common.h src/GameEngineImpl/Scenes/PlayGame/common.tpp src/GameEngineImpl/Scenes/PlayGame/Player.cpp src/GameEngineImpl/Scenes/PlayGame/Player.h src/GameEngineImpl/Scenes/PlayGame/PlayGameScene.tpp src/Utilities/SaveUtilities.cpp)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
target_link_libraries(pathfinding PRIVATE sfml-system sfml-network sfml-graphics sfml-window)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# uncomment this line to show warnings
# set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
