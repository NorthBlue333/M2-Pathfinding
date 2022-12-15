#pragma once
#include <cmath>

namespace PathFinding
{

    class Heuristic
    {
        struct Position
        {
            int x, y;
        };
    public:

        static Position GetDelta(const Grid::Coordinates2D& Source, const Grid::Coordinates2D& Target)
        {
            return { abs(Source.X - Target.X), abs(Source.Y - Target.Y) };
        }

        static int Manhattan(const Grid::Coordinates2D& Source, const Grid::Coordinates2D& Target)
        {
            const auto delta = GetDelta(Source, Target);
            return 10 * (delta.x + delta.y);
        }

        static int Euclidean(const Grid::Coordinates2D& Source, const Grid::Coordinates2D& Target)
        {
            const auto delta = GetDelta(Source, Target);
            return std::sqrt(std::pow(delta.x, 2) + std::pow(delta.y, 2)) * 10;
        }

        static int Octagonal(const Grid::Coordinates2D& Source, const Grid::Coordinates2D& Target)
        {
            const auto delta = GetDelta(Source, Target);
            return 10 * (delta.x + delta.y) + (-6) * std::min(delta.x, delta.y);
        }

    };

}
