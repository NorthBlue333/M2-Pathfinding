#ifndef PATHFINDING_HASMOUSEEVENTS_H
#define PATHFINDING_HASMOUSEEVENTS_H

#include <SFML/System/Vector2.hpp>
#include <vector>
#include "../../../UserInterface/IButton.h"

namespace GameEngineImpl::Traits {
    class HasMouseEvents {
    protected:
        bool bIsMouseLeftPressed = false;

        virtual ~HasMouseEvents() = default;

        void HandleOnMouseHover(sf::Vector2f MousePosition, std::vector<UI::IButton*>& Buttons);
        void HandleOnMouseDragOver(sf::Vector2f MousePosition, std::vector<UI::IButton*>& Buttons);
        void HandleOnMouseLeft(sf::Event& Event, std::vector<UI::IButton*>& Buttons);

        void SetMousePressed(sf::Event& Event);
    };

} // GameEngineImpl

#endif //PATHFINDING_HASMOUSEEVENTS_H
