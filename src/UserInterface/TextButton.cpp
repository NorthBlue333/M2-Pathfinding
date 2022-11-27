#include "TextButton.h"

namespace UI {
    TextButton::TextButton(const sf::String &ContentText, const sf::Font &font, unsigned int characterSize) : IButton(), m_ContentText(ContentText) {
        m_Text = sf::Text(ContentText, font, characterSize);
    }

    void TextButton::Render(sf::RenderWindow *Window) {
        Window->draw(m_Text);
    }

    sf::Rect<float> TextButton::GetGlobalBounds() const {
        return m_Text.getGlobalBounds();
    }

    void TextButton::SetPosition(float x, float y) {
        m_Text.setPosition(x, y);
    }

    sf::Vector2<float> TextButton::GetPosition() const {
        return m_Text.getPosition();
    }
} // UI