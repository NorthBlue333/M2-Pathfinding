#include "PlayGameScene.h"
#include "../../../UserInterface/TextButton.h"
#include "../../../Utilities/PositionUtilities.h"
#include <iostream>

namespace GameEngineImpl::Scenes::PlayGame {
    PlayGameScene::PlayGameScene(Game *Game) : BaseScene(Game), m_BackButton(nullptr), m_Player(nullptr) {

    }

    void PlayGameScene::ExecuteCalculations(sf::Time Elapsed) {

    }

    void PlayGameScene::Render() {
        auto Window = m_Game->GetWindow();
        m_BackButton->Render(Window);

        if (m_CurrentGridType == GameEngineImpl::GridType::Square) {
            m_Grid.SquareGrid->Render(Window);
        } else if (m_CurrentGridType == GameEngineImpl::GridType::Hexagonal) {
            m_Grid.HexagonalGrid->Render(Window);
        }

        m_Player->Render(Window);
    }

    void PlayGameScene::Load() {
        auto newFont = new sf::Font;
        newFont->loadFromFile("./assets/anek_devanagari/static/AnekDevanagari/AnekDevanagari-Bold.ttf");
        m_Fonts.insert({PlayGameFont::AnekDevanagari, newFont});

        std::map<PlayGameTextureName, std::string> TexturesToLoad = {
            {PlayGameTextureName::FilledSquare, "./assets/textures/WhiteSquare.png"},
            {PlayGameTextureName::FilledHexagon, "./assets/textures/WhiteHexagon.png"},
            {PlayGameTextureName::OutlinedSquare, "./assets/textures/OutlinedWhiteSquare.png"},
            {PlayGameTextureName::OutlinedHexagon, "./assets/textures/OutlinedWhiteHexagon.png"},
            {PlayGameTextureName::PortalSquare, "./assets/textures/PortalSquare.png"},
            {PlayGameTextureName::PortalHexagon, "./assets/textures/PortalHexagon.png"},
            {PlayGameTextureName::FlagSquare, "./assets/textures/FlagSquare.png"},
            {PlayGameTextureName::FlagHexagon, "./assets/textures/FlagHexagon.png"},
        };

        for (const auto &Pair : TexturesToLoad) {
            auto texture = new sf::Texture;
            texture->loadFromFile(Pair.second);
            m_Textures.insert({Pair.first, texture});
        }

        m_BackButton = new UI::TextButton("Back to main menu", *newFont);
        m_BackButton->SetPosition(10, 10);
        m_BackButton->SetOnClick([this](auto && Btn) { m_Game->LoadScene(GameSceneName::MainMenu); });

        CreateGrid();
    }

    PlayGameScene::~PlayGameScene() {
        delete m_BackButton;
        delete m_Player;
    }

    std::vector<UI::IButton*> PlayGameScene::GetButtons() {
        std::vector<UI::IButton*> buttons{};
        buttons.push_back(m_BackButton);
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

    HexagonalGridType::DataHolder_T *PlayGameScene::CreateHexagonalGridDataHolder(
        HexagonalGridType::GridNode_T * GridNode,
        const Grid::RenderableCoordinates2D& RenderCoordinates,
        const Grid::RenderableSize2D& RenderSize
    ) {
        std::map<GridImpl::NodeType, sf::Texture*> Textures = {
            {GridImpl::NodeType::Empty, m_Textures.at(PlayGameTextureName::OutlinedHexagon)},
            {GridImpl::NodeType::Plain, m_Textures.at(PlayGameTextureName::FilledHexagon)},
            {GridImpl::NodeType::Portal, m_Textures.at(PlayGameTextureName::PortalHexagon)},
            {GridImpl::NodeType::PlayerStart, m_Textures.at(PlayGameTextureName::FlagHexagon)},
        };
        return FillGridDataHolder<HexagonalGridType::DataHolder_T>(
            Textures,
            RenderCoordinates,
            RenderSize
        );
    }

    SquareGridType::DataHolder_T *PlayGameScene::CreateSquareGridDataHolder(
        SquareGridType::GridNode_T * GridNode,
        const Grid::RenderableCoordinates2D& RenderCoordinates,
        const Grid::RenderableSize2D& RenderSize
    ) {
        std::map<GridImpl::NodeType, sf::Texture*> Textures = {
            {GridImpl::NodeType::Empty, m_Textures.at(PlayGameTextureName::OutlinedSquare)},
            {GridImpl::NodeType::Plain, m_Textures.at(PlayGameTextureName::FilledSquare)},
            {GridImpl::NodeType::Portal, m_Textures.at(PlayGameTextureName::PortalSquare)},
            {GridImpl::NodeType::PlayerStart, m_Textures.at(PlayGameTextureName::FlagSquare)},
        };
        return FillGridDataHolder<SquareGridType::DataHolder_T>(
            Textures,
            RenderCoordinates,
            RenderSize
        );
    }

    void PlayGameScene::CreateGrid() {
        // @todo maybe we could generate automatically these ifs but not sure / factory
        const auto WindowSize = m_Game->GetWindow()->getSize();
        unsigned int GridWidth = 35;
        unsigned int GridHeight = 20;
        const auto BackBtnBounds = m_BackButton->GetGlobalBounds();
        const auto HeightToRemove = BackBtnBounds.height + BackBtnBounds.top + (BUTTON_MARGIN * 6) + BUTTON_HEIGHT;
        const auto ContainerHeight = static_cast<unsigned int>(std::max(WindowSize.y - HeightToRemove, 0.f));
        const auto ContainerWidth = WindowSize.x - (BUTTON_MARGIN * 2);

        m_CurrentGridType = m_Game->LoadedGridType;

        m_Player = new Player({0, 0});

        if (m_CurrentGridType == GameEngineImpl::GridType::Square) {
            m_Grid.SquareGrid = new SquareGridType(
                GridWidth,
                GridHeight,
                {ContainerWidth, ContainerHeight},
                [this](SquareGridType::GridNode_T * GridNode, const Grid::RenderableCoordinates2D& RenderCoordinates, const Grid::RenderableSize2D& RenderSize) {
                    return CreateSquareGridDataHolder(GridNode, RenderCoordinates, RenderSize);
                }
            );

            for (const auto & Data : m_Game->LoadedSavedData) {
                auto Node = m_Grid.SquareGrid->GetNodeAtCoordinates(Data.Coordinates);
                Node->DataHolder->SetCurrentNodeType(Data.NodeType);
                if (GridImpl::NodeType::Portal == Data.NodeType) {
                    auto LinkedDataHolder = m_Grid.SquareGrid->GetNodeAtCoordinates(Data.LinkedPortal)->DataHolder;
                    LinkedDataHolder->SetCurrentNodeType(Data.NodeType);
                    Node->DataHolder->SetLinkedPortal(LinkedDataHolder);
                }

                if (Data.NodeType == GridImpl::NodeType::PlayerStart) {
                    m_Player->SetCoordinates(Data.Coordinates);
                }
            }
            auto ContainerSize = m_Grid.SquareGrid->GetContainerSize();
            auto NodeRenderSize = m_Grid.SquareGrid->GetNodeRenderSize(ContainerSize);
            SetPlayerPositionFromCoordinates(
                m_Grid.SquareGrid->GetNodeRenderCoordinates(m_Player->GetCoordinates(), NodeRenderSize),
                NodeRenderSize
            );

            m_Grid.SquareGrid->GenerateNeighbors();
        } else if (m_CurrentGridType == GameEngineImpl::GridType::Hexagonal) {
            m_Grid.HexagonalGrid = new HexagonalGridType(
                GridWidth,
                GridHeight,
                {ContainerWidth, ContainerHeight},
                [this](HexagonalGridType::GridNode_T * GridNode, const Grid::RenderableCoordinates2D& RenderCoordinates, const Grid::RenderableSize2D& RenderSize) {
                    return CreateHexagonalGridDataHolder(GridNode, RenderCoordinates, RenderSize);
                }
            );

            for (const auto & Data : m_Game->LoadedSavedData) {
                auto Node = m_Grid.HexagonalGrid->GetNodeAtCoordinates(Data.Coordinates);
                Node->DataHolder->SetCurrentNodeType(Data.NodeType);
                if (GridImpl::NodeType::Portal == Data.NodeType) {
                    auto LinkedDataHolder = m_Grid.HexagonalGrid->GetNodeAtCoordinates(Data.LinkedPortal)->DataHolder;
                    LinkedDataHolder->SetCurrentNodeType(Data.NodeType);
                    Node->DataHolder->SetLinkedPortal(LinkedDataHolder);
                }

                if (Data.NodeType == GridImpl::NodeType::PlayerStart) {
                    m_Player->SetCoordinates(Data.Coordinates);
                }
            }
            auto ContainerSize = m_Grid.HexagonalGrid->GetContainerSize();
            auto NodeRenderSize = m_Grid.HexagonalGrid->GetNodeRenderSize(ContainerSize);
            SetPlayerPositionFromCoordinates(
                m_Grid.HexagonalGrid->GetNodeRenderCoordinates(m_Player->GetCoordinates(), NodeRenderSize),
                NodeRenderSize
            );

            m_Grid.HexagonalGrid->GenerateNeighbors();
        }
    }

    void
    PlayGameScene::SetPlayerPositionFromCoordinates(Grid::RenderableCoordinates2D RenderCoordinates, Grid::RenderableSize2D NodeSize) {
        // @todo correct position from FillDataHolder
        auto Coordinates = m_Player->GetCoordinates();

        auto PlayerBounds = m_Player->GetGlobalBounds();
        auto CenteredPos = Utilities::GetCenterPosition(
            {0, 0, static_cast<float>(NodeSize.Width), static_cast<float>(NodeSize.Height)},
            {0, 0, PlayerBounds.width, PlayerBounds.height}
        );
        m_Player->SetPosition(
            BUTTON_MARGIN + RenderCoordinates.X + CenteredPos.x, 70 + RenderCoordinates.Y + CenteredPos.y
        );
    }

    HexagonalGridType *PlayGameScene::GetHexagonalGrid() const {
        return m_Grid.HexagonalGrid;
    }

    SquareGridType *PlayGameScene::GetSquareGrid() const {
        return m_Grid.SquareGrid;
    }

    const GameEngineImpl::GridType &PlayGameScene::GetCurrentGridType() const {
        return m_CurrentGridType;
    }

    Player *PlayGameScene::GetPlayer() const {
        return m_Player;
    }
} // Scenes