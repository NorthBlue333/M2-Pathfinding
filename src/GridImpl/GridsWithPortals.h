#ifndef PATHFINDING_GRIDSWITHPORTALS_H
#define PATHFINDING_GRIDSWITHPORTALS_H

#include <SFML/Graphics.hpp>
#include "../Grid/BaseGrid.h"

namespace GridImpl {
    enum struct NodeType {
        Empty = 0,
        Plain,
        Portal
    };

    class IGridDataHolder {
    public:
        IGridDataHolder() = default;
        virtual ~IGridDataHolder() = default;

        virtual void Render(sf::RenderWindow *Window) = 0;

        virtual void SetCurrentNodeType(NodeType NewType) = 0;
        const NodeType& GetCurrentNodeType() const;

        void SetTextures(std::map<NodeType, sf::Texture*>& NewTextures);
    protected:
        virtual void SetTextureFromNodeType() = 0;

        std::map<NodeType, sf::Texture*> Textures;
        NodeType CurrentNodeType = NodeType::Empty;
    };

    template <template <typename NodeType> typename GridDataHolderType, typename GridNodeType>
    class GridDataHolder : public IGridDataHolder, public Grid::BaseDataHolderType<GridDataHolderType<GridNodeType>, GridNodeType> {
    public:
        GridDataHolder() = default;
        ~GridDataHolder() override;

        const GridDataHolderType<GridNodeType>* GetLinkedPortal() const;
        void SetLinkedPortal(GridDataHolderType<GridNodeType>* Linked);

        std::vector<GridNodeType*> GetAdditionalNeighbors() override;

        void SetCurrentNodeType(NodeType NewType) override;
    protected:
        GridDataHolderType<GridNodeType>* LinkedPortal = nullptr;
    };

} // GridImpl

#include "GridsWithPortals.tpp"

#endif //PATHFINDING_GRIDSWITHPORTALS_H
