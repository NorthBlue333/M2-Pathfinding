#include "LevelEditorScene.h"

namespace GameEngineImpl::Scenes {
    LevelEditorScene::LevelEditorScene(GameType *Game) : BaseScene(Game), m_BackButton(nullptr) {
    }

    void LevelEditorScene::ExecuteCalculations(sf::Time Elapsed) {

    }

    void LevelEditorScene::Render() {
        auto Window = m_Game->GetWindow();
        m_BackButton->Render(Window);
        for (auto &button : m_EditorButtons) {
            button->Render(Window);
        }
        for (auto &button : m_GridTypeButtons) {
            button->Render(Window);
        }

        if (m_CurrentGridType == LevelEditorGridType::Square) {
            m_Grid.SquareGrid->Render(Window);
        } else if (m_CurrentGridType == LevelEditorGridType::Hexagonal) {
            m_Grid.HexagonalGrid->Render(Window);
        }
    }

    void LevelEditorScene::Load() {
        auto newFont = new sf::Font;
        newFont->loadFromFile("./assets/anek_devanagari/static/AnekDevanagari/AnekDevanagari-Bold.ttf");
        m_Fonts.insert({LevelEditorFont::AnekDevanagari, newFont});

        auto squareTexture = new sf::Texture;
        squareTexture->loadFromFile("./assets/textures/WhiteSquare.png");
        m_Textures.insert({LevelEditorTextureName::FilledSquare, squareTexture});

        auto hexagonTexture = new sf::Texture;
        hexagonTexture->loadFromFile("./assets/textures/WhiteHexagon.png");
        m_Textures.insert({LevelEditorTextureName::FilledHexagon, hexagonTexture});

        auto outlinedSquareTexture = new sf::Texture;
        outlinedSquareTexture->loadFromFile("./assets/textures/OutlinedWhiteSquare.png");
        m_Textures.insert({LevelEditorTextureName::OutlinedSquare, outlinedSquareTexture});

        auto outlinedHexagonTexture = new sf::Texture;
        outlinedHexagonTexture->loadFromFile("./assets/textures/OutlinedWhiteHexagon.png");
        m_Textures.insert({LevelEditorTextureName::OutlinedHexagon, outlinedHexagonTexture});

        auto portalSquareTexture = new sf::Texture;
        portalSquareTexture->loadFromFile("./assets/textures/PortalSquare.png");
        m_Textures.insert({LevelEditorTextureName::PortalSquare, portalSquareTexture});

        auto portalHexagonTexture = new sf::Texture;
        portalHexagonTexture->loadFromFile("./assets/textures/PortalHexagon.png");
        m_Textures.insert({LevelEditorTextureName::PortalHexagon, portalHexagonTexture});

        m_BackButton = new UI::TextButton("Back to main menu", *newFont);
        m_BackButton->SetPosition(10, 10);
        m_BackButton->SetOnClick([this](auto && Btn) { m_Game->LoadScene(GameSceneName::MainMenu); });

        const auto WindowSize = m_Game->GetWindow()->getSize();
        auto hexaTypeButton = new UI::TextButton("HexaType", *newFont);
        // @todo compute pos correctly maybe
        hexaTypeButton->SetPosition(WindowSize.x - 200, WindowSize.y - 50);
        hexaTypeButton->SetOnClick([this](auto && Btn) { SetCurrentGridType(LevelEditorGridType::Hexagonal); });
        m_GridTypeButtons.push_back(hexaTypeButton);
        auto squareTypeButton = new UI::TextButton("SquareType", *newFont);
        squareTypeButton->SetPosition(WindowSize.x - 200, WindowSize.y - 100);
        squareTypeButton->SetOnClick([this](auto && Btn) { SetCurrentGridType(LevelEditorGridType::Square); });
        m_GridTypeButtons.push_back(squareTypeButton);

        SetCurrentGridType(LevelEditorGridType::Square);
    }

    LevelEditorScene::~LevelEditorScene() {
        delete m_BackButton;

        for (auto & Btn : m_EditorButtons) {
            delete Btn;
        }

        for (auto & Btn : m_GridTypeButtons) {
            delete Btn;
        }

        if (m_CurrentGridType == LevelEditorGridType::Hexagonal) {
            delete m_Grid.HexagonalGrid;
        } else if (m_CurrentGridType == LevelEditorGridType::Square) {
            delete m_Grid.SquareGrid;
        }
    }

    std::vector<UI::IButton*> LevelEditorScene::GetButtons() {
        std::vector<UI::IButton*> buttons{m_EditorButtons};
        buttons.push_back(m_BackButton);
        for (auto &Btn : m_GridTypeButtons) {
            buttons.push_back(Btn);
        }
        if (m_CurrentGridType == LevelEditorGridType::Square) {
            auto Nodes = m_Grid.SquareGrid->GetNodes();
            for (auto & Node : *Nodes) {
                buttons.push_back(Node.DataHolder->GetGridNodeButton());
            }
        } else if (m_CurrentGridType == LevelEditorGridType::Hexagonal) {
            auto Nodes = m_Grid.HexagonalGrid->GetNodes();
            for (auto & Node : *Nodes) {
                buttons.push_back(Node.DataHolder->GetGridNodeButton());
            }
        }
        return buttons;
    }

    LevelEditorScene::NodeTypeButton* LevelEditorScene::AddButton(
            const sf::Texture *Texture,
            const sf::String &Name,
            GridImpl::NodeType NodeType
    ) {
        auto newButton = new LevelEditorScene::NodeTypeButton(Texture, Name, *m_Fonts.at(LevelEditorFont::AnekDevanagari), BUTTON_WIDTH, BUTTON_HEIGHT, 14.f);
        auto WindowSize = m_Game->GetWindow()->getSize();
        newButton->TargetNodeType = NodeType;
        newButton->SetOnClick([this](auto && Btn) {
            if (m_CurrentNodeTypeButton != nullptr) {
                m_CurrentNodeTypeButton->ToggleActive(false);
            }
            auto CastedBtn = static_cast<LevelEditorScene::NodeTypeButton*>(Btn);
            if (m_CurrentNodeTypeButton == CastedBtn) {
                m_CurrentNodeTypeButton = nullptr;
                return;
            }
            CastedBtn->ToggleActive(true);
            m_CurrentNodeTypeButton = CastedBtn;
        });
        newButton->SetPosition(BUTTON_MARGIN + ((BUTTON_MARGIN + BUTTON_WIDTH) * (float) m_EditorButtons.size()), WindowSize.y - BUTTON_HEIGHT - BUTTON_MARGIN);
        m_EditorButtons.push_back(newButton);
        return newButton;
    }

    LevelEditorScene::HexagonalGridType::DataHolder_T *LevelEditorScene::CreateHexagonalGridDataHolder(
            HexagonalGridType::GridNode_T * GridNode,
            const Grid::RenderableCoordinates2D& RenderCoordinates,
            const Grid::RenderableSize2D& RenderSize
    ) {
        std::map<GridImpl::NodeType, sf::Texture*> Textures = {
                {GridImpl::NodeType::Empty, m_Textures.at(LevelEditorTextureName::OutlinedHexagon)},
                {GridImpl::NodeType::Plain, m_Textures.at(LevelEditorTextureName::FilledHexagon)},
                {GridImpl::NodeType::Portal, m_Textures.at(LevelEditorTextureName::PortalHexagon)},
        };
        return FillGridDataHolder<LevelEditorScene::HexagonalGridType::DataHolder_T>(
                Textures,
                RenderCoordinates,
                RenderSize
        );
    }

    LevelEditorScene::SquareGridType::DataHolder_T *LevelEditorScene::CreateSquareGridDataHolder(
            SquareGridType::GridNode_T * GridNode,
            const Grid::RenderableCoordinates2D& RenderCoordinates,
            const Grid::RenderableSize2D& RenderSize
    ) {
        std::map<GridImpl::NodeType, sf::Texture*> Textures = {
                {GridImpl::NodeType::Empty, m_Textures.at(LevelEditorTextureName::OutlinedSquare)},
                {GridImpl::NodeType::Plain, m_Textures.at(LevelEditorTextureName::FilledSquare)},
                {GridImpl::NodeType::Portal, m_Textures.at(LevelEditorTextureName::PortalSquare)},
        };
        return FillGridDataHolder<LevelEditorScene::SquareGridType::DataHolder_T>(
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
        if (m_CurrentGridType == LevelEditorGridType::Square) {
            m_Grid.SquareGrid = new SquareGridType(
                GridWidth,
                GridHeight,
                {ContainerWidth, ContainerHeight},
                [this](SquareGridType::GridNode_T * GridNode, const Grid::RenderableCoordinates2D& RenderCoordinates, const Grid::RenderableSize2D& RenderSize) {
                    return CreateSquareGridDataHolder(GridNode, RenderCoordinates, RenderSize);
                }
            );
        } else if (m_CurrentGridType == LevelEditorGridType::Hexagonal) {
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

    void LevelEditorScene::SetCurrentGridType(LevelEditorGridType NewGridType) {
        m_CurrentGridType = NewGridType;
        m_LastPortal = nullptr;
        CreateGrid();
        ResetNodeTypeButtons();

        if (m_CurrentGridType == LevelEditorGridType::Square) {
            AddButton(m_Textures.at(LevelEditorTextureName::OutlinedSquare), "Empty", GridImpl::NodeType::Empty);
            AddButton(m_Textures.at(LevelEditorTextureName::FilledSquare), "Plain", GridImpl::NodeType::Plain);
            AddButton(m_Textures.at(LevelEditorTextureName::PortalSquare), "Portal", GridImpl::NodeType::Portal);
        } else if (m_CurrentGridType == LevelEditorGridType::Hexagonal) {
            AddButton(m_Textures.at(LevelEditorTextureName::OutlinedHexagon), "Empty", GridImpl::NodeType::Empty);
            AddButton(m_Textures.at(LevelEditorTextureName::FilledHexagon), "Plain", GridImpl::NodeType::Plain);
            AddButton(m_Textures.at(LevelEditorTextureName::PortalHexagon), "Portal", GridImpl::NodeType::Portal);
        }
    }

    void LevelEditorScene::ResetNodeTypeButtons() {
        for (auto & Btn : m_EditorButtons) {
            delete Btn;
        }

        m_EditorButtons = {};
        m_CurrentNodeTypeButton = nullptr;
    }
} // Scenes