#ifndef PATHFINDING_POSITIONUTILITIES_H
#define PATHFINDING_POSITIONUTILITIES_H

#include <SFML/Graphics.hpp>

namespace Utilities {
    class PositionUtilities {
    public:
        static sf::Vector2<float> GetCenterPosition(const sf::Rect<float>& parentBounds, const sf::Rect<float>& childBounds);
        static float GetXCenterPosition(const sf::Rect<float>& parentBounds, const sf::Rect<float>& childBounds);
        static float GetYCenterPosition(const sf::Rect<float>& parentBounds, const sf::Rect<float>& childBounds);
    };

} // Utilities

#endif //PATHFINDING_POSITIONUTILITIES_H
