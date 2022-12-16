#ifndef PATHFINDING_BASEGRID_H
#define PATHFINDING_BASEGRID_H

#include <cstdlib>
#include <vector>
#include <functional>

namespace Grid {
    struct Coordinates2D {
        Coordinates2D() = default;
        Coordinates2D(int NewX, int NewY) : X(NewX), Y(NewY) {};
        int X = 0;
        int Y = 0;
    };

    template <typename DataHolderType, typename GridNodeType, bool WithDiagonals>
    class BaseDataHolderType {
    public:
        GridNodeType* Node;

        virtual bool IsBlocked() const;
        virtual std::vector<GridNodeType*> GetAdditionalNeighbors() = 0;

        BaseDataHolderType() = default;
        virtual ~BaseDataHolderType() = default;
    };

    template <typename GridNodeType, template<typename NodeType, bool WD> typename DataHolderNodeType, bool WithDiagonals>
    struct BaseGridNode {
        Coordinates2D Coordinates;
        std::vector<GridNodeType*> Neighbors;
        DataHolderNodeType<GridNodeType, WithDiagonals>* DataHolder = nullptr;

        bool IsBlocked() const;

        virtual std::vector<GridNodeType*> GetAdditionalNeighbors() const;
        virtual bool IsDiagonalFrom(GridNodeType* Neighbor) const = 0;

        BaseGridNode(Coordinates2D& C, DataHolderNodeType<GridNodeType, WithDiagonals>* DH);
        virtual ~BaseGridNode();

        virtual BaseGridNode& operator =(GridNodeType&& other);
    };

    // @todo maybe add templated number of nodes for fixed size array instead of vector
    template<typename GridNodeType, template<typename NodeType, bool WD> typename DataHolderNodeType, bool WithDiagonals>
    class BaseGrid {
    public:
        using GridNode_T = GridNodeType;
        using DataHolder_T = DataHolderNodeType<GridNodeType, WithDiagonals>;

        void CreateNodes(
                unsigned int& Width,
                unsigned int& Height,
                std::function<DataHolderNodeType<GridNodeType, WithDiagonals>*(GridNodeType* GridNode, const Coordinates2D& Coordinates)> CreateDataHolderNode = [](const Coordinates2D&) {return nullptr;}
        );

        void GenerateNeighbors();

        std::vector<Coordinates2D> GetNeighborsCoordinates(GridNodeType& Node);
        virtual std::vector<Coordinates2D> GetNeighborsCoordinates(Coordinates2D& Coordinates) = 0;

        GridNodeType* GetNodeAtCoordinates(const Coordinates2D& Coordinates);

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
