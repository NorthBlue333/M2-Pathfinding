#include "Node.h"


int PathFinding::Node::GetScore() const { return g + h; }

void PathFinding::Node::AddNeighbor(Node* node)
{
    neighbors.push_back(node);
    node->neighbors.push_back(this);
}
