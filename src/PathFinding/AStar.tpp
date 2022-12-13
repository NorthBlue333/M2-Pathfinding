#include "AStar.h"

namespace PathFinding {
    template<typename NodeType>
    int AStarNode<NodeType>::GetScore() const {
        return G + H;
    }

    template<typename NodeType>
    bool AStarNode<NodeType>::operator==(const AStarNode<NodeType> &Other) {
        return this->OriginalNode == Other.OriginalNode;
    }

    template<typename GridType, typename NodeType>
    std::vector<NodeType *> AStar<GridType, NodeType>::GetPath(NodeType *Start, NodeType *Target) {
        std::vector<AStarNode<NodeType>> openSet;
        std::vector<NodeType*> closedSet;
        openSet.reserve(this->m_Grid->GetNodes().size() / 2);
        closedSet.reserve(this->m_Grid->GetNodes().size() / 2);

        openSet.emplace_back(Start);

        AStarNode<NodeType>* current = nullptr;
        while (!openSet.empty()) {
            auto current_it = openSet.begin();
            current = current_it;

            // @todo probably better to bubble sort the array and get the last element
            for (auto it = openSet.begin(); it != openSet.end(); ++it) {
                const auto node = *it;
                if (node->GetScore() <= current->GetScore()) {
                    current = node;
                    current_it = it;
                }
            }

            if (current->OriginalNode == Target) {
                break;
            }

            openSet.erase(current_it);
            closedSet.push_back(current->OriginalNode);
            current = &openSet.back();

            for (auto neighbor : current->OriginalNode->Neighbors) {
                if (!std::find(closedSet.begin(), closedSet.end(), neighbor))
                {
                    // @todo extract to method on OriginalNode
                    const bool b_diagonal = current->OriginalNode->Coordinates.X != neighbor->Coordinates.X && current->OriginalNode->Coordinates.Y != neighbor->Coordinates.Y;
                    const auto total_cost = current->G + (b_diagonal ? 14 : 10);
                    openSet.emplace_back(neighbor);
                    auto Last = openSet.back();
                    Last.ParentInPath = current;
                    Last.G = total_cost;
                    Last.H = heuristic(neighbor, Target);
                }
            }
        }

        std::vector<NodeType*> path;
        while (current != nullptr) {
            path.push_back(current->OriginalNode);
            current = current->ParentInPath;
        }

        return path;
    }
}