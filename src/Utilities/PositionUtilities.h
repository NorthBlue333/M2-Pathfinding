#ifndef PATHFINDING_POSITIONUTILITIES_H
#define PATHFINDING_POSITIONUTILITIES_H

#include <SFML/Graphics.hpp>

namespace Utilities {
        sf::Vector2<float> GetCenterPosition(const sf::Rect<float>& parentBounds, const sf::Rect<float>& childBounds);
        float GetXCenterPosition(const sf::Rect<float>& parentBounds, const sf::Rect<float>& childBounds);
        float GetYCenterPosition(const sf::Rect<float>& parentBounds, const sf::Rect<float>& childBounds);
} // Utilities

#endif //PATHFINDING_POSITIONUTILITIES_H
