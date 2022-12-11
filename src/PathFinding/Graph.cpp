#include "Graph.h"

namespace PathFinding
{

	std::vector<Node*> Graph::Path(Node* source, Node* target)
	{
		Node* current = nullptr;
		NodeSet openSet;
		openSet.reserve(nodes.size() / 2);

		openSet.push_back(source);

		while (!openSet.empty()) {
			auto current_it = openSet.begin();
			current = *current_it;

			// @todo probably better to bubble sort the array and get the last element 
			for (auto it = openSet.begin(); it != openSet.end(); ++it) {
				const auto node = *it;
				if (node->GetScore() <= current->GetScore()) {
					current = node;
					current_it = it;
				}
			}

			if (current == target) {
				break;
			}

			openSet.erase(current_it);
			current->visited = true;

			for (auto neighbor : current->neighbors) {
				if (!neighbor->visited)
				{
					neighbor->visited = true;
					const bool b_diagonal = current->x != neighbor->x && current->y != neighbor->y;
					const auto total_cost = current->g + (b_diagonal ? 14 : 10);
					neighbor->g = total_cost;
					neighbor->h = heuristic(neighbor, target);
					neighbor->parent = current;
					openSet.push_back(neighbor);
				}
			}
		}

		NodeSet path;
		while (current != nullptr) {
			path.push_back(current);
			current = current->parent;
		}

		openSet.clear();

		return path;
	}

}
