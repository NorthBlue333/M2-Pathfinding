#include "PositionUtilities.h"

namespace Utilities {
    sf::Vector2<float>
    PositionUtilities::GetCenterPosition(const sf::Rect<float> &parentBounds, const sf::Rect<float> &childBounds) {
        return sf::Vector2f{
                PositionUtilities::GetXCenterPosition(parentBounds, childBounds),
                PositionUtilities::GetYCenterPosition(parentBounds, childBounds)
        };
    }

    float PositionUtilities::GetXCenterPosition(const sf::Rect<float> &parentBounds, const sf::Rect<float> &childBounds) {
        return parentBounds.left + (parentBounds.width / 2) - (childBounds.width / 2);
    }

    float PositionUtilities::GetYCenterPosition(const sf::Rect<float> &parentBounds, const sf::Rect<float> &childBounds) {
        return parentBounds.top + (parentBounds.height / 2) - (childBounds.height / 2);
    }
} // Utilities