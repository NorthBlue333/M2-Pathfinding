#ifndef PATHFINDING_SQUARESPRITEBUTTON_H
#define PATHFINDING_SQUARESPRITEBUTTON_H

#include "IButton.h"

namespace UI {
    class SquareSpriteButton : public IButton {
    public:
        explicit SquareSpriteButton(
                const sf::Texture *Texture,
                const sf::String& Name,
                const sf::Font& Font,
                float Width = 50,
                float Height = 50,
                unsigned int CharacterSize = 20
        );
        ~SquareSpriteButton() override = default;

        void ToggleActive(bool IsActive);

        void Render(sf::RenderWindow *Window) override;
        sf::Rect<float> GetGlobalBounds() const override;
        void SetPosition(float x, float y) override;
        sf::Vector2<float> GetPosition() const override;
    protected:
        static float constexpr BORDER_THICKNESS = 3.f;

        bool m_IsActive = false;
        const sf::Texture* m_Texture;
        sf::RectangleShape m_Border;
        sf::Text m_Name;
        sf::Sprite m_Sprite;
        sf::Color m_InactiveColor;
        sf::Color m_HoverColor;
        sf::Color m_ActiveColor;

        void SetSpriteScale();
        void SetAllPositions(float x, float y);

        void DefaultOnHoverStart(UI::IButton *Button) override;
        void DefaultOnHoverEnd(UI::IButton *Button) override;
        void DefaultOnClick(UI::IButton *Button) override;
    };

} // UI

#endif //PATHFINDING_SQUARESPRITEBUTTON_H
