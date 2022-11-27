#ifndef PATHFINDING_TEXTBUTTON_H
#define PATHFINDING_TEXTBUTTON_H

#include "IButton.h"

namespace UI {
    class TextButton : public IButton {
    public:
        explicit TextButton(
                const sf::String& ContentText,
                const sf::Font& font,
                unsigned int characterSize = 30
        );

        void Render(sf::RenderWindow *Window) override;
        sf::Rect<float> GetGlobalBounds() const override;
        void SetPosition(float x, float y) override;
        sf::Vector2<float> GetPosition() const override;
    protected:
        std::string m_ContentText;
        sf::Text m_Text;
    };

} // UI

#endif //PATHFINDING_TEXTBUTTON_H
