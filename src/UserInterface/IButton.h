#ifndef PATHFINDING_IBUTTON_H
#define PATHFINDING_IBUTTON_H

#include <SFML/Graphics.hpp>
#include <string>
#include <functional>

namespace UI {
    class IButton {
    public:
        using EventType = std::function<void(IButton*)>;
        explicit IButton();
        virtual ~IButton() = default;

        void Hover(bool isHovered);
        void Click();
        void DragOver();
        virtual void Render(sf::RenderWindow* Window) = 0;

        void SetOnHover(const EventType &OnHover, const IButton::EventType &OnHoverEnd);
        void SetOnClick(const EventType &OnClick);
        void SetOnDragOver(const EventType &OnDragOver);

        virtual sf::Rect<float> GetGlobalBounds() const = 0;
        virtual void SetPosition(float x, float y) = 0;
        virtual sf::Vector2<float> GetPosition() const = 0;
    protected:
        EventType m_OnHoverStart;
        EventType m_OnHoverEnd;
        EventType m_OnClick;
        EventType m_OnDragOver;

        bool m_IsHovered = false;

        virtual void DefaultOnHoverStart(IButton* Button);
        virtual void DefaultOnHoverEnd(IButton* Button);
        virtual void DefaultOnClick(IButton* Button);
        virtual void DefaultOnDragOver(IButton* Button);
    };

} // UI

#endif //PATHFINDING_IBUTTON_H
