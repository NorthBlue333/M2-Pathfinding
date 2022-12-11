#ifndef PATHFINDING_GRIDNODEBUTTON_H
#define PATHFINDING_GRIDNODEBUTTON_H

#include "IButton.h"

namespace UI {
    class GridNodeButton : public IButton {
    public:
        explicit GridNodeButton(
                const sf::Texture *Texture,
                float Width = 50,
                float Height = 50
        );
        ~GridNodeButton() override = default;

        void SetTexture(const sf::Texture *Texture);
        void Render(sf::RenderWindow *Window) override;
        sf::Rect<float> GetGlobalBounds() const override;
        void SetPosition(float x, float y) override;
        sf::Vector2<float> GetPosition() const override;
    protected:
        float m_Width;
        float m_Height;
        const sf::Texture* m_Texture;
        sf::Sprite m_Sprite;

        void SetSpriteScale();

        void DefaultOnHoverStart(UI::IButton *Button) override;
        void DefaultOnHoverEnd(UI::IButton *Button) override;
        void DefaultOnClick(UI::IButton *Button) override;
    };

} // UI

#endif //PATHFINDING_GRIDNODEBUTTON_H
