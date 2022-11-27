#include "SquareSpriteButton.h"
#include "../Utilities/PositionUtilities.h"

namespace UI {
    SquareSpriteButton::SquareSpriteButton(
            const sf::Texture *Texture,
            const sf::String &Name,
            const sf::Font &Font,
            float Width,
            float Height,
            unsigned int CharacterSize
    )
            : m_Texture(Texture),
              m_Name(sf::Text(Name, Font, CharacterSize)),
              m_Border(sf::RectangleShape(sf::Vector2f(Width, Height))),
              m_InactiveColor(sf::Color::White),
              m_HoverColor(sf::Color::Cyan),
              m_ActiveColor(sf::Color::Yellow),
              m_Sprite(sf::Sprite(*Texture)) {
        SetSpriteScale();
        m_Border.setFillColor(sf::Color::Transparent);
        // set inside thickness
        m_Border.setOutlineThickness(-BORDER_THICKNESS);
        ToggleActive(m_IsActive);
        SetAllPositions(m_Border.getPosition().x, m_Border.getPosition().y);
    }

    void SquareSpriteButton::DefaultOnHoverStart(UI::IButton *Button) {
        IButton::DefaultOnHoverStart(Button);
        m_Border.setOutlineColor(m_HoverColor);
    }

    void SquareSpriteButton::DefaultOnHoverEnd(UI::IButton *Button) {
        IButton::DefaultOnHoverEnd(Button);
        ToggleActive(m_IsActive);
    }

    void SquareSpriteButton::DefaultOnClick(UI::IButton *Button) {
        IButton::DefaultOnClick(Button);
        ToggleActive(!m_IsActive);
    }

    void SquareSpriteButton::Render(sf::RenderWindow *Window) {
        Window->draw(m_Border);
        Window->draw(m_Name);
        Window->draw(m_Sprite);
    }

    void SquareSpriteButton::ToggleActive(bool IsActive) {
        m_IsActive = IsActive;
        auto color = m_IsActive ? m_ActiveColor : m_InactiveColor;
        m_Border.setOutlineColor(color);
        m_Name.setFillColor(color);
    }

    sf::Rect<float> SquareSpriteButton::GetGlobalBounds() const {
        return m_Border.getGlobalBounds();
    }

    void SquareSpriteButton::SetPosition(float x, float y) {
        SetAllPositions(x, y);
    }

    void SquareSpriteButton::SetAllPositions(float x, float y) {
        m_Border.setPosition(x, y);
        auto BorderBounds = m_Border.getGlobalBounds();
        m_Sprite.setPosition(Utilities::PositionUtilities::GetXCenterPosition(BorderBounds, m_Sprite.getGlobalBounds()),
                             BorderBounds.top + BORDER_THICKNESS + 10);
        m_Name.setPosition(Utilities::PositionUtilities::GetXCenterPosition(BorderBounds, m_Name.getGlobalBounds()),
                           BorderBounds.top + BorderBounds.height - m_Name.getGlobalBounds().height - BORDER_THICKNESS - 10);
    }

    sf::Vector2<float> SquareSpriteButton::GetPosition() const {
        return m_Border.getPosition();
    }

    void SquareSpriteButton::SetSpriteScale() {
        auto MaxSpriteWidth = m_Border.getGlobalBounds().width * 0.8f - (BORDER_THICKNESS * 2);
        auto MaxSpriteHeight = m_Border.getGlobalBounds().height - m_Name.getGlobalBounds().height - (BORDER_THICKNESS * 2);
        auto TextureSize = m_Sprite.getTexture()->getSize();
        auto Ratio = (float) TextureSize.x / (float) TextureSize.y;
        auto NewWidth = MaxSpriteHeight * Ratio;
        auto NewHeight = MaxSpriteWidth / Ratio;
        if (NewWidth > MaxSpriteWidth) {
            NewWidth = MaxSpriteWidth;
        } else {
            NewHeight = MaxSpriteHeight;
        }

        m_Sprite.setScale(NewWidth / TextureSize.x, NewHeight / TextureSize.y);
    }
} // UI