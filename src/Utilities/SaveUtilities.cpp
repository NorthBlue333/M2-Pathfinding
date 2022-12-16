
#include "SaveUtilities.h"

namespace Utilities {
    SaveUtilities::SaveUtilities() = default;

    SaveUtilities::~SaveUtilities() = default;

/*
    void SaveUtilities::SaveGame(GameEngineImpl::Scenes::PlayGame::PlayGameGridType typeGrid,
                                 GridImpl::NodeType typeNode, Grid::Coordinates2D coordinatesNode) {
*/
    void SaveUtilities::SaveGame() {
        checkFolder();
        std::ofstream saveFile;
        saveFile.open(saveFolderPath + "/save.txt");
        if (!saveFile) {
            std::ofstream Save(saveFolderPath + "/save.txt");
            saveFile.open(saveFolderPath + "/save.txt");
        }
        saveFile << "";
        saveFile.close();
        std::cout << "Game saved" << std::endl;
    }


    void SaveUtilities::checkFolder() {
        if (!std::filesystem::is_directory(saveFolderPath) || !std::filesystem::exists(saveFolderPath)) {
            std::filesystem::create_directory(saveFolderPath);
        }
    }

    std::vector<std::string> SaveUtilities::getSavesFileList() {
        checkFolder();
        std::vector<std::string> savesList;
        for (const auto &entry: std::filesystem::directory_iterator(saveFolderPath)) {
            savesList.emplace_back(entry.path().string());
        }
        return savesList;
    }

    void SaveUtilities::getSaveInformation(const std::string &pathFile) {
        std::string information;
        std::ifstream saveFile(pathFile);
        while (getline(saveFile, information)) {
            std::cout << information;
        }
    }

    void SaveUtilities::takeScreenshot() {
        //Screenshot = .Capture();
        //Screenshot.saveToFile(saveFolderPath + "/1.png");
    }

    sf::Image SaveUtilities::getScreenshotResult(const std::string &saveName) {

        return sf::Image();
    }
}

