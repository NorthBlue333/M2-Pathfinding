#ifndef PATHFINDING_SAVEUTILITIES_H
#define PATHFINDING_SAVEUTILITIES_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <SFML/Graphics/Image.hpp>
#include "../GameEngineImpl/common_types.h"
#include "../Grid/BaseGrid.h"
#include "../GridImpl/GridsWithPortals.h"

namespace Utilities {
    class SaveUtilities {
    public:
        SaveUtilities();

        ~SaveUtilities();

        void SaveGame();
        void TakeScreenshot();
        std::vector<GameEngineImpl::SavedData> LoadSave(const std::string &pathFile, GameEngineImpl::GridType& GridType);
        sf::Image GetScreenshotResult(const std::string &saveName);
        std::vector<std::string> GetSavesFileList();

        GameEngineImpl::GridType GridType;
        std::vector<GameEngineImpl::SavedData> DataToSave;
    private:
        void CheckFolder();
        std::string saveFolderPath = "../Saves";
        sf::Image Screenshot;
    };
}

#endif //PATHFINDING_SAVEUTILITIES_H
