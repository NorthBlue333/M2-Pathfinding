#ifndef PATHFINDING_BASEGRID_H
#define PATHFINDING_BASEGRID_H

#include <cstdlib>
#include <vector>
#include <functional>

namespace Grid {
    struct Coordinates2D {
        int X = 0;
        int Y = 0;
    };

    template <typename DataHolderType, typename GridNodeType>
    class BaseDataHolderType {
    public:
        GridNodeType* Node;

        virtual std::vector<GridNodeType*> GetAdditionalNeighbors() = 0;
        BaseDataHolderType() = default;
        virtual ~BaseDataHolderType() = default;
    };

    template <typename GridNodeType, template<typename NodeType> typename DataHolderNodeType>
    struct BaseGridNode {
        Coordinates2D Coordinates;
        std::vector<GridNodeType*> Neighbors;
        DataHolderNodeType<GridNodeType>* DataHolder = nullptr;

        virtual std::vector<GridNodeType*> GetAdditionalNeighbors() const;

        BaseGridNode(Coordinates2D& C, DataHolderNodeType<GridNodeType>* DH);
        virtual ~BaseGridNode();

        virtual BaseGridNode& operator =(GridNodeType&& other);
    };

    // @todo maybe add templated number of nodes for fixed size array instead of vector
    template<typename GridNodeType, template<typename NodeType> typename DataHolderNodeType>
    class BaseGrid {
    public:
        using GridNode_T = GridNodeType;
        using DataHolder_T = DataHolderNodeType<GridNodeType>;

        void CreateNodes(
                unsigned int& Width,
                unsigned int& Height,
                std::function<DataHolderNodeType<GridNodeType>*(GridNodeType* GridNode, const Coordinates2D& Coordinates)> CreateDataHolderNode = [](const Coordinates2D&) {return nullptr;}
        );

        void GenerateNeighbors();

        std::vector<Coordinates2D> GetNeighborsCoordinates(GridNodeType& Node);
        virtual std::vector<Coordinates2D> GetNeighborsCoordinates(Coordinates2D& Coordinates) = 0;

        std::vector<GridNodeType> const* GetNodes() const;

        bool IsInMap(Coordinates2D& Coordinates) const;

        virtual ~BaseGrid() = default;
    protected:
        unsigned int m_Width = 0;
        unsigned int m_Height = 0;

        std::vector<GridNodeType> m_Nodes;

        std::size_t GetIndexFromCoordinates(const Coordinates2D& Coordinates) const;
        Coordinates2D GetCoordinatesFromIndex(const int& Index) const;

        explicit BaseGrid() = default;
    };
} // Grid

#include "BaseGrid.tpp"

#endif //PATHFINDING_BASEGRID_H
