#include "LevelEditorScene.h"

namespace GameEngineImpl::Scenes::LevelEditor {
    LevelEditorScene::LevelEditorScene(Game *Game) : BaseScene(Game), m_BackButton(nullptr) {
    }

    void LevelEditorScene::ExecuteCalculations(sf::Time Elapsed) {

    }

    void LevelEditorScene::Render() {
        auto Window = m_Game->GetWindow();
        m_BackButton->Render(Window);
        m_SaveButton->Render(Window);
        for (auto &button : m_EditorButtons) {
            button->Render(Window);
        }
        for (auto &button : m_GridTypeButtons) {
            button->Render(Window);
        }

        if (m_CurrentGridType == GameEngineImpl::GridType::Square) {
            m_Grid.SquareGrid->Render(Window);
        } else if (m_CurrentGridType == GameEngineImpl::GridType::Hexagonal) {
            m_Grid.HexagonalGrid->Render(Window);
        }
    }

    void LevelEditorScene::Load() {
        auto newFont = new sf::Font;
        newFont->loadFromFile("./assets/anek_devanagari/static/AnekDevanagari/AnekDevanagari-Bold.ttf");
        m_Fonts.insert({LevelEditorFont::AnekDevanagari, newFont});

        std::map<LevelEditorTextureName, std::string> TexturesToLoad = {
            {LevelEditorTextureName::FilledSquare, "./assets/textures/WhiteSquare.png"},
            {LevelEditorTextureName::FilledHexagon, "./assets/textures/WhiteHexagon.png"},
            {LevelEditorTextureName::OutlinedSquare, "./assets/textures/OutlinedWhiteSquare.png"},
            {LevelEditorTextureName::OutlinedHexagon, "./assets/textures/OutlinedWhiteHexagon.png"},
            {LevelEditorTextureName::PortalSquare, "./assets/textures/PortalSquare.png"},
            {LevelEditorTextureName::PortalHexagon, "./assets/textures/PortalHexagon.png"},
            {LevelEditorTextureName::FlagSquare, "./assets/textures/FlagSquare.png"},
            {LevelEditorTextureName::FlagHexagon, "./assets/textures/FlagHexagon.png"},
        };

        for (const auto &Pair : TexturesToLoad) {
            auto texture = new sf::Texture;
            texture->loadFromFile(Pair.second);
            m_Textures.insert({Pair.first, texture});
        }

        m_BackButton = new UI::TextButton("Back to main menu", *newFont);
        m_BackButton->SetPosition(10, 10);
        m_BackButton->SetOnClick([this](auto && Btn) { m_Game->LoadScene(GameSceneName::MainMenu); });

        m_SaveButton = new UI::TextButton("Save game", *newFont);
        m_SaveButton->SetPosition(m_SaveButton->GetPosition().x + 300, m_SaveButton->GetPosition().y + 10);
        m_SaveButton->SetOnClick([this](auto && Btn) { m_GameMode->GetGameController()->SaveNodes(); });

        const auto WindowSize = m_Game->GetWindow()->getSize();
        auto hexaTypeButton = new UI::TextButton("HexaType", *newFont);
        // @todo compute position correctly maybe
        hexaTypeButton->SetPosition(WindowSize.x - 200, WindowSize.y - 50);
        hexaTypeButton->SetOnClick([this](auto && Btn) { SetCurrentGridType(GameEngineImpl::GridType::Hexagonal); });
        m_GridTypeButtons.push_back(hexaTypeButton);
        auto squareTypeButton = new UI::TextButton("SquareType", *newFont);
        squareTypeButton->SetPosition(WindowSize.x - 200, WindowSize.y - 100);
        squareTypeButton->SetOnClick([this](auto && Btn) { SetCurrentGridType(GameEngineImpl::GridType::Square); });
        m_GridTypeButtons.push_back(squareTypeButton);

        SetCurrentGridType(GameEngineImpl::GridType::Square);
    }

    LevelEditorScene::~LevelEditorScene() {
        delete m_BackButton;
        delete m_SaveButton;

        for (auto & Btn : m_EditorButtons) {
            delete Btn;
        }
        m_EditorButtons = {};

        for (auto & Btn : m_GridTypeButtons) {
            delete Btn;
        }
        m_GridTypeButtons = {};

        if (m_CurrentGridType == GameEngineImpl::GridType::Hexagonal) {
            delete m_Grid.HexagonalGrid;
            m_Grid.HexagonalGrid = nullptr;
        } else if (m_CurrentGridType == GameEngineImpl::GridType::Square) {
            delete m_Grid.SquareGrid;
            m_Grid.SquareGrid = nullptr;
        }
    }

    std::vector<UI::IButton*> LevelEditorScene::GetButtons() {
        std::vector<UI::IButton*> buttons{m_EditorButtons};
        buttons.push_back(m_BackButton);
        buttons.push_back(m_SaveButton);
        for (auto Btn : m_GridTypeButtons) {
            buttons.push_back(Btn);
        }
        if (m_CurrentGridType == GameEngineImpl::GridType::Square) {
            auto Nodes = m_Grid.SquareGrid->GetNodes();
            for (auto & Node : *Nodes) {
                buttons.push_back(Node.DataHolder->GetGridNodeButton());
            }
        } else if (m_CurrentGridType == GameEngineImpl::GridType::Hexagonal) {
            auto Nodes = m_Grid.HexagonalGrid->GetNodes();
            for (auto & Node : *Nodes) {
                buttons.push_back(Node.DataHolder->GetGridNodeButton());
            }
        }
        return buttons;
    }

    NodeTypeButton* LevelEditorScene::AddButton(
            const sf::Texture *Texture,
            const sf::String &Name,
            GridImpl::NodeType NodeType
    ) {
        auto newButton = new NodeTypeButton(Texture, Name, *m_Fonts.at(LevelEditorFont::AnekDevanagari), BUTTON_WIDTH, BUTTON_HEIGHT, 14.f);
        auto WindowSize = m_Game->GetWindow()->getSize();
        newButton->TargetNodeType = NodeType;
        newButton->SetOnClick([this](auto && Btn) {
            m_GameMode->GetGameController()->HandleOnNodeTypeButtonClick(Btn);
        });
        newButton->SetPosition(BUTTON_MARGIN + ((BUTTON_MARGIN + BUTTON_WIDTH) * (float) m_EditorButtons.size()), WindowSize.y - BUTTON_HEIGHT - BUTTON_MARGIN);
        m_EditorButtons.push_back(newButton);
        return newButton;
    }

    HexagonalGridType::DataHolder_T *LevelEditorScene::CreateHexagonalGridDataHolder(
            HexagonalGridType::GridNode_T * GridNode,
            const Grid::RenderableCoordinates2D& RenderCoordinates,
            const Grid::RenderableSize2D& RenderSize
    ) {
        std::map<GridImpl::NodeType, sf::Texture*> Textures = {
                {GridImpl::NodeType::Empty, m_Textures.at(LevelEditorTextureName::OutlinedHexagon)},
                {GridImpl::NodeType::Plain, m_Textures.at(LevelEditorTextureName::FilledHexagon)},
                {GridImpl::NodeType::Portal, m_Textures.at(LevelEditorTextureName::PortalHexagon)},
                {GridImpl::NodeType::PlayerStart, m_Textures.at(LevelEditorTextureName::FlagHexagon)},
        };
        return FillGridDataHolder<HexagonalGridType::DataHolder_T>(
                Textures,
                RenderCoordinates,
                RenderSize
        );
    }

    SquareGridType::DataHolder_T *LevelEditorScene::CreateSquareGridDataHolder(
            SquareGridType::GridNode_T * GridNode,
            const Grid::RenderableCoordinates2D& RenderCoordinates,
            const Grid::RenderableSize2D& RenderSize
    ) {
        std::map<GridImpl::NodeType, sf::Texture*> Textures = {
                {GridImpl::NodeType::Empty, m_Textures.at(LevelEditorTextureName::OutlinedSquare)},
                {GridImpl::NodeType::Plain, m_Textures.at(LevelEditorTextureName::FilledSquare)},
                {GridImpl::NodeType::Portal, m_Textures.at(LevelEditorTextureName::PortalSquare)},
                {GridImpl::NodeType::PlayerStart, m_Textures.at(LevelEditorTextureName::FlagSquare)},
        };
        return FillGridDataHolder<SquareGridType::DataHolder_T>(
                Textures,
                RenderCoordinates,
                RenderSize
        );
    }

    void LevelEditorScene::CreateGrid() {
        // @todo maybe we could generate automatically these ifs but not sure / factory
        const auto WindowSize = m_Game->GetWindow()->getSize();
        unsigned int GridWidth = 35;
        unsigned int GridHeight = 20;
        const auto BackBtnBounds = m_BackButton->GetGlobalBounds();
        const auto HeightToRemove = BackBtnBounds.height + BackBtnBounds.top + (BUTTON_MARGIN * 6) + BUTTON_HEIGHT;
        const auto ContainerHeight = static_cast<unsigned int>(std::max(WindowSize.y - HeightToRemove, 0.f));
        const auto ContainerWidth = WindowSize.x - (BUTTON_MARGIN * 2);
        if (m_CurrentGridType == GameEngineImpl::GridType::Square) {
            m_Grid.SquareGrid = new SquareGridType(
                GridWidth,
                GridHeight,
                {ContainerWidth, ContainerHeight},
                [this](SquareGridType::GridNode_T * GridNode, const Grid::RenderableCoordinates2D& RenderCoordinates, const Grid::RenderableSize2D& RenderSize) {
                    return CreateSquareGridDataHolder(GridNode, RenderCoordinates, RenderSize);
                }
            );
        } else if (m_CurrentGridType == GameEngineImpl::GridType::Hexagonal) {
            m_Grid.HexagonalGrid = new HexagonalGridType(
                GridWidth,
                GridHeight,
                {ContainerWidth, ContainerHeight},
                [this](HexagonalGridType::GridNode_T * GridNode, const Grid::RenderableCoordinates2D& RenderCoordinates, const Grid::RenderableSize2D& RenderSize) {
                    return CreateHexagonalGridDataHolder(GridNode, RenderCoordinates, RenderSize);
                }
            );
        }
    }

    void LevelEditorScene::SetCurrentGridType(GameEngineImpl::GridType NewGridType) {
        m_CurrentGridType = NewGridType;
        ResetNodeTypeButtons();
        CreateGrid();

        if (m_CurrentGridType == GameEngineImpl::GridType::Square) {
            AddButton(m_Textures.at(LevelEditorTextureName::OutlinedSquare), "Empty", GridImpl::NodeType::Empty);
            AddButton(m_Textures.at(LevelEditorTextureName::FilledSquare), "Plain", GridImpl::NodeType::Plain);
            AddButton(m_Textures.at(LevelEditorTextureName::PortalSquare), "Portal", GridImpl::NodeType::Portal);
            AddButton(m_Textures.at(LevelEditorTextureName::FlagSquare), "Player start", GridImpl::NodeType::PlayerStart);
        } else if (m_CurrentGridType == GameEngineImpl::GridType::Hexagonal) {
            AddButton(m_Textures.at(LevelEditorTextureName::OutlinedHexagon), "Empty", GridImpl::NodeType::Empty);
            AddButton(m_Textures.at(LevelEditorTextureName::FilledHexagon), "Plain", GridImpl::NodeType::Plain);
            AddButton(m_Textures.at(LevelEditorTextureName::PortalHexagon), "Portal", GridImpl::NodeType::Portal);
            AddButton(m_Textures.at(LevelEditorTextureName::FlagHexagon), "Player start", GridImpl::NodeType::PlayerStart);
        }
    }

    void LevelEditorScene::ResetNodeTypeButtons() {
        for (auto & Btn : m_EditorButtons) {
            delete Btn;
        }

        m_EditorButtons = {};

        m_GameMode->GetGameController()->ResetNodeTypeButtons();
    }

    const GameEngineImpl::GridType &LevelEditorScene::GetCurrentGridType() const {
        return m_CurrentGridType;
    }

    HexagonalGridType *LevelEditorScene::GetHexagonalGrid() const {
        return m_Grid.HexagonalGrid;
    }

    SquareGridType *LevelEditorScene::GetSquareGrid() const {
        return m_Grid.SquareGrid;
    }
} // Scenes