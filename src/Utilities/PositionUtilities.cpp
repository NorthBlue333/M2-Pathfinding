#include "PositionUtilities.h"

namespace Utilities {
    sf::Vector2<float>
    GetCenterPosition(const sf::Rect<float> &parentBounds, const sf::Rect<float> &childBounds) {
        return sf::Vector2f{
                GetXCenterPosition(parentBounds, childBounds),
                GetYCenterPosition(parentBounds, childBounds)
        };
    }

    float GetXCenterPosition(const sf::Rect<float> &parentBounds, const sf::Rect<float> &childBounds) {
        return parentBounds.left + (parentBounds.width / 2) - (childBounds.width / 2);
    }

    float GetYCenterPosition(const sf::Rect<float> &parentBounds, const sf::Rect<float> &childBounds) {
        return parentBounds.top + (parentBounds.height / 2) - (childBounds.height / 2);
    }

    sf::Vector2<float> GetFillSpriteScale(sf::Vector2<unsigned int> TextureSize, float MaxSpriteHeight, float MaxSpriteWidth) {
        auto Ratio = (float) TextureSize.x / (float) TextureSize.y;
        auto NewWidth = MaxSpriteHeight * Ratio;
        auto NewHeight = MaxSpriteWidth / Ratio;
        if (NewWidth > MaxSpriteWidth) {
            NewWidth = MaxSpriteWidth;
        } else {
            NewHeight = MaxSpriteHeight;
        }

        return {NewWidth / TextureSize.x, NewHeight / TextureSize.y};
    }
} // Utilities