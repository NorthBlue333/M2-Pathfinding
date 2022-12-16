#ifndef PATHFINDING_COMMON_TYPES_H
#define PATHFINDING_COMMON_TYPES_H

#include "../GameEngine/BaseGame.h"
#include "../GameEngine/BaseScene.h"
#include "../Grid/BaseGrid.h"
#include "../GridImpl/GridsWithPortals.h"

namespace GameEngineImpl {
    enum GameSceneName {
        MainMenu = 0,
        PlayGame,
        LevelEditor,
    };

    enum struct GridType {
        Square = 0,
        Hexagonal,
    };

    struct SavedData {
        Grid::Coordinates2D Coordinates;
        GridImpl::NodeType NodeType = GridImpl::NodeType::Empty;

        Grid::Coordinates2D LinkedPortal;
    };
}

#endif //PATHFINDING_COMMON_TYPES_H
