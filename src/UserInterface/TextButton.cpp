#include "TextButton.h"

namespace UI {
    TextButton::TextButton(const sf::String &ContentText, const sf::Font &font, unsigned int characterSize)
            : IButton(), m_ContentText(ContentText) {
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

    void TextButton::DefaultOnHoverStart(IButton *Button) {
        m_Text.setStyle(sf::Text::Bold | sf::Text::Underlined);
        IButton::DefaultOnHoverStart(Button);
    }

    void TextButton::DefaultOnHoverEnd(IButton *Button) {
        m_Text.setStyle(sf::Text::Regular);
        IButton::DefaultOnHoverEnd(Button);
    }

    void TextButton::DefaultOnClick(IButton *Button) {
        m_Text.setFillColor(sf::Color::Blue);
        IButton::DefaultOnClick(Button);
    }

    void TextButton::DefaultOnDragOver(IButton *Button) {
        m_Text.setFillColor(sf::Color::White);
        IButton::DefaultOnDragOver(Button);
    }
} // UI