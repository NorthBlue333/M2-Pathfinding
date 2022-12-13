#include "HasMouseEvents.h"

namespace GameEngineImpl::Traits {
    void HasMouseEvents::HandleOnMouseLeft(sf::Event& Event, std::vector<UI::IButton*>& Buttons) {
        if (
            sf::Event::MouseButtonPressed == Event.type
            && sf::Mouse::Button::Left == Event.mouseButton.button
        )
            return;

        for (auto & button : Buttons) {
            if (!button->GetGlobalBounds().contains(sf::Vector2f(Event.mouseButton.x, Event.mouseButton.y)))
                continue;

            button->Click();
        }
    }

    void HasMouseEvents::HandleOnMouseHover(const sf::Vector2f MousePosition, std::vector<UI::IButton*>& Buttons) {
        for (auto & button : Buttons) {
            button->Hover(button->GetGlobalBounds().contains(MousePosition));
        }
    }

    void HasMouseEvents::HandleOnMouseDragOver(const sf::Vector2f MousePosition, std::vector<UI::IButton *> &Buttons) {
        if (!bIsMouseLeftPressed)
            return;

        for (auto & button : Buttons) {
            if (!button->GetGlobalBounds().contains(MousePosition))
                continue;

            button->DragOver();
        }
    }

    void HasMouseEvents::SetMousePressed(sf::Event& Event) {
        if (
            sf::Event::MouseButtonPressed == Event.type
            && sf::Mouse::Button::Left == Event.mouseButton.button
        ) {
            bIsMouseLeftPressed = true;
            return;
        }
        if (
            sf::Event::MouseButtonReleased == Event.type
            && sf::Mouse::Button::Left == Event.mouseButton.button
        ) {
            bIsMouseLeftPressed = false;
            return;
        }
    }
} // GameEngineImpl