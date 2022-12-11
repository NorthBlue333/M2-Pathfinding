#pragma once
#include "Node.h"

namespace PathFinding
{

    class Heuristic
    {
        struct Position
        {
            int x, y;
        };
    public:

        static Position GetDelta(const Node* source, const Node* target)
        {
            return{ abs(source->x - target->x), abs(source->y - target->y) };
        }

        static int Manhattan(const Node* source, const Node* target)
        {
            const auto delta = GetDelta(source, target);
            return 10 * (delta.x + delta.y);
        }

        static int Euclidean(const Node* source, const Node* target)
        {
            const auto delta = GetDelta(source, target);
            return sqrt(pow(delta.x, 2) + pow(delta.y, 2)) * 10;
        }

        static int Octagonal(const Node* source, const Node* target)
        {
            const auto delta = GetDelta(source, target);
            return 10 * (delta.x + delta.y) + (-6) * std::min(delta.x, delta.y);
        }

    };

}
