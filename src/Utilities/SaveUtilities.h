#ifndef PATHFINDING_SAVEUTILITIES_H
#define PATHFINDING_SAVEUTILITIES_H


#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <SFML/Graphics/Image.hpp>
#include "../GameEngineImpl/Scenes/PlayGame/PlayGameScene.h"

namespace Utilities {
    class SaveUtilities {
    public:
        SaveUtilities();

        ~SaveUtilities();

        void SaveGame();

        //void SaveGame(GameEngineImpl::Scenes::PlayGame::PlayGameGridType typeGrid, GridImpl::NodeType typeNode,
        //              Grid::Coordinates2D coordinatesNode);

        void takeScreenshot();

        void getSaveInformation(const std::string &pathFile);

        sf::Image getScreenshotResult(const std::string &saveName);

        std::vector<std::string> getSavesFileList();


    private:
        void checkFolder();

    protected:
        std::string saveFolderPath = "../src/Saves";
        sf::Image Screenshot;
    };
}

#endif //PATHFINDING_SAVEUTILITIES_H
