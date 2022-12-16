#include "SaveUtilities.h"

namespace Utilities {

    std::string GetStrFromNodeType(GridImpl::NodeType value) {
        static std::map<GridImpl::NodeType, std::string> strings;
        if (strings.empty()){
            #define INSERT_ELEMENT(p) strings[p] = #p
            INSERT_ELEMENT(GridImpl::NodeType::Empty);
            INSERT_ELEMENT(GridImpl::NodeType::Plain);
            INSERT_ELEMENT(GridImpl::NodeType::Portal);
            INSERT_ELEMENT(GridImpl::NodeType::PlayerStart);
            #undef INSERT_ELEMENT
        }

        return strings[value];
    }

    std::string GetStrFromGridType(GameEngineImpl::GridType value) {
        static std::map<GameEngineImpl::GridType, std::string> strings;
        if (strings.empty()){
            #define INSERT_ELEMENT(p) strings[p] = #p
            INSERT_ELEMENT(GameEngineImpl::GridType::Hexagonal);
            INSERT_ELEMENT(GameEngineImpl::GridType::Square);
            #undef INSERT_ELEMENT
        }

        return strings[value];
    }

    std::ostream& operator<<(std::ostream& out, const GridImpl::NodeType value){
        return out << GetStrFromNodeType(value);
    }
    std::ostream& operator<<(std::ostream& out, const GameEngineImpl::GridType value){
        return out << GetStrFromGridType(value);
    }

    std::ostream& operator<<(std::ostream& os, const GameEngineImpl::SavedData& dt)
    {
        os << dt.Coordinates.X << ',' << dt.Coordinates.Y << ',' << dt.NodeType;

        if (dt.NodeType == GridImpl::NodeType::Portal) {
            os << ',' << dt.LinkedPortal.X << ',' << dt.LinkedPortal.Y;
        }
        return os;
    }

    SaveUtilities::SaveUtilities() = default;

    SaveUtilities::~SaveUtilities() = default;

    void SaveUtilities::SaveGame() {
        CheckFolder();
        std::ofstream saveFile;
        saveFile.open(saveFolderPath + "/save.txt");
        if (!saveFile) {
            std::ofstream Save(saveFolderPath + "/save.txt");
            saveFile.open(saveFolderPath + "/save.txt");
        }
        saveFile << GridType;
        for (const auto & Data : DataToSave) {
            saveFile << "\n" << Data;
        }
        saveFile.close();
        std::cout << "Game saved" << std::endl;
    }


    void SaveUtilities::CheckFolder() {
        if (!std::filesystem::is_directory(saveFolderPath) || !std::filesystem::exists(saveFolderPath)) {
            std::filesystem::create_directory(saveFolderPath);
        }
    }

    std::vector<std::string> SaveUtilities::GetSavesFileList() {
        CheckFolder();
        std::vector<std::string> savesList;
        for (const auto &entry: std::filesystem::directory_iterator(saveFolderPath)) {
            savesList.emplace_back(entry.path().string());
        }
        return savesList;
    }

    std::vector<GameEngineImpl::SavedData> SaveUtilities::LoadSave(const std::string &pathFile, GameEngineImpl::GridType& GridType) {
        std::string Data;
        std::ifstream saveFile(pathFile);

        std::vector<GameEngineImpl::SavedData> Datas;
        std::map<std::string, GameEngineImpl::GridType> AvailableGridTypes = {
            {GetStrFromGridType(GameEngineImpl::GridType::Hexagonal), GameEngineImpl::GridType::Hexagonal},
            {GetStrFromGridType(GameEngineImpl::GridType::Square), GameEngineImpl::GridType::Square},
        };
        std::map<std::string, GridImpl::NodeType> AvailableNodeTypes = {
            {GetStrFromNodeType(GridImpl::NodeType::Empty), GridImpl::NodeType::Empty},
            {GetStrFromNodeType(GridImpl::NodeType::Plain), GridImpl::NodeType::Plain},
            {GetStrFromNodeType(GridImpl::NodeType::Portal), GridImpl::NodeType::Portal},
            {GetStrFromNodeType(GridImpl::NodeType::PlayerStart), GridImpl::NodeType::PlayerStart},
        };
        GridType = GameEngineImpl::GridType::Square;
        bool firstLine = true;
        while (getline(saveFile, Data)) {
            // @todo we could extract this to avoid if on each loop
            if (firstLine) {
                GridType = AvailableGridTypes.contains(Data) ? AvailableGridTypes[Data] : GameEngineImpl::GridType::Square;
                firstLine = false;
                continue;
            }
            std::istringstream DataAsStream{Data};
            std::string DataValue;
            int pos = 0;
            Grid::Coordinates2D Coords;
            Grid::Coordinates2D LinkedPortal;
            GridImpl::NodeType NodeType = GridImpl::NodeType::Plain;
            while (std::getline(DataAsStream, DataValue, ',')) {
                if (pos == 0) {
                    Coords.X = std::stoi(DataValue);
                } else if (pos == 1) {
                    Coords.Y = std::stoi(DataValue);
                } else if (pos == 2) {
                    NodeType = AvailableNodeTypes.contains(DataValue) ? AvailableNodeTypes[DataValue] : GridImpl::NodeType::Plain;
                    if (NodeType != GridImpl::NodeType::Portal) {
                        break;
                    }
                } else if (pos == 3) {
                    LinkedPortal.X = std::stoi(DataValue);
                } else if (pos == 4) {
                    LinkedPortal.Y = std::stoi(DataValue);
                }

                ++pos;
            }
            Datas.push_back({Coords, NodeType, LinkedPortal});
        }

        return Datas;
    }

    void SaveUtilities::TakeScreenshot() {
        //Screenshot = .Capture();
        //Screenshot.saveToFile(saveFolderPath + "/1.png");
    }

    sf::Image SaveUtilities::GetScreenshotResult(const std::string &saveName) {

        return sf::Image();
    }
}

