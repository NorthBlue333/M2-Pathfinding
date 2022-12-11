#include "GridNodeButton.h"
#include "../Utilities/PositionUtilities.h"

namespace UI {
    GridNodeButton::GridNodeButton(
            const sf::Texture *Texture,
            float Width,
            float Height
    )
            : m_Texture(Texture),
              m_Sprite(sf::Sprite(*Texture)),
              m_Width(Width),
              m_Height(Height)
    {
        SetSpriteScale();
    }

    void GridNodeButton::DefaultOnHoverStart(UI::IButton *Button) {
        IButton::DefaultOnHoverStart(Button);
    }

    void GridNodeButton::DefaultOnHoverEnd(UI::IButton *Button) {
        IButton::DefaultOnHoverEnd(Button);
    }

    void GridNodeButton::DefaultOnClick(UI::IButton *Button) {
        IButton::DefaultOnClick(Button);
    }

    void GridNodeButton::Render(sf::RenderWindow *Window) {
        Window->draw(m_Sprite);
    }

    sf::Rect<float> GridNodeButton::GetGlobalBounds() const {
        return m_Sprite.getGlobalBounds();
    }

    void GridNodeButton::SetPosition(float x, float y) {
        m_Sprite.setPosition(x, y);
    }

    sf::Vector2<float> GridNodeButton::GetPosition() const {
        return m_Sprite.getPosition();
    }

    void GridNodeButton::SetSpriteScale() {
        auto TextureSize = m_Sprite.getTexture()->getSize();
        const auto Scale = Utilities::GetFillSpriteScale(TextureSize, m_Width, m_Height);
        m_Sprite.setScale(Scale.x, Scale.y);
    }

    void GridNodeButton::SetTexture(const sf::Texture *Texture) {
        m_Texture = Texture;
        m_Sprite.setTexture(*m_Texture);
    }
} // UI