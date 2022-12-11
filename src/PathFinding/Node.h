#pragma once
#include <vector>

namespace PathFinding
{

    class Node
    {
    public:
        Node(const int x, const int y) : x(x), y(y), g(0), h(0) {}

        int GetScore() const;

        void AddNeighbor(Node* node);

        int x, y, g, h;
        std::vector<Node*> neighbors;
        Node* parent{};
        bool visited = false;
    };
}
