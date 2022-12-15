#include <list>
#include "AStar.h"
#include "Heuristic.h"

namespace PathFinding {
    template <typename NodeType>
    int AStarNode<NodeType>::GetScore() const {
        return G + H;
    }

    template<typename GridType, typename NodeType>
    std::vector<NodeType *> AStar<GridType, NodeType>::GetPath(NodeType *Start, NodeType *Target) {
        std::map<NodeType*, AStarNode<NodeType>> AStarNodes;
        std::list<NodeType*> openSet;

        openSet.push_back(Start);

        NodeType* Current = nullptr;
        while (!openSet.empty()) {
            auto current_it = openSet.begin();
            Current = *current_it;
            auto CurrentAStarNode = &GetOrCreateAStartNodeInMap(AStarNodes, Current);

            // @todo probably better to bubble sort the array and get the last element
            for (auto it = openSet.begin(); it != openSet.end(); ++it) {
                const auto Node = *it;
                auto AStarNode = &GetOrCreateAStartNodeInMap(AStarNodes, Node);
                if (AStarNode->GetScore() <= CurrentAStarNode->GetScore()) {
                    Current = Node;
                    current_it = it;
                    CurrentAStarNode = AStarNode;
                }
            }

            openSet.erase(current_it);

            CurrentAStarNode->Visited = true;

            if (Current == Target) {
                break;
            }

            for (auto Neighbor : Current->Neighbors) {
                auto AStarNode = &GetOrCreateAStartNodeInMap(AStarNodes, Neighbor);
                if (!AStarNode->Visited)
                {
                    const bool b_diagonal = Neighbor->IsDiagonalFrom(Current);
                    const auto total_cost = CurrentAStarNode->G + (b_diagonal ? 14 : 10);
                    openSet.push_back(Neighbor);
                    AStarNode->ParentInPath = Current;
                    AStarNode->G = total_cost;
                    AStarNode->H = Heuristic::Euclidean(Neighbor->Coordinates, Target->Coordinates);
                    AStarNode->Visited = true;
                }
            }
        }

        std::vector<NodeType*> FinalPath;
        while (Current != nullptr) {
            FinalPath.push_back(Current);
            Current = AStarNodes.contains(Current) ? AStarNodes[Current].ParentInPath : nullptr;
        }

        return FinalPath;
    }

    template<typename GridType, typename NodeType>
    AStarNode<NodeType> &AStar<GridType, NodeType>::GetOrCreateAStartNodeInMap(std::map<NodeType *, AStarNode<NodeType>>& Map, NodeType* Node) const {
        if (!Map.contains(Node)) {
            Map.insert({Node, {}});
        }

        return Map[Node];
    }
}