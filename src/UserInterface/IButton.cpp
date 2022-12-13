#include "IButton.h"
#include <iostream>

namespace UI {
    IButton::IButton() {
        m_OnHoverStart = [this](auto && Btn) { DefaultOnHoverStart(std::forward<decltype(Btn)>(Btn)); };
        m_OnHoverEnd = [this](auto && Btn) { DefaultOnHoverEnd(std::forward<decltype(Btn)>(Btn)); };
        m_OnClick = [this](auto && Btn) { DefaultOnClick(std::forward<decltype(Btn)>(Btn)); };
        m_OnDragOver = [this](auto && Btn) { DefaultOnDragOver(std::forward<decltype(Btn)>(Btn)); };
    }

    void IButton::DefaultOnHoverStart(IButton *Button) {
        std::cout << "Default on hover start" << std::endl;
    }

    void IButton::DefaultOnHoverEnd(IButton *Button) {
        std::cout << "Default on hover end" << std::endl;
    }

    void IButton::DefaultOnClick(IButton*) {
        std::cout << "Default on click" << std::endl;
    }

    void IButton::DefaultOnDragOver(IButton*) {
        std::cout << "Default on drag over" << std::endl;
    }

    void IButton::SetOnHover(const IButton::EventType &OnHoverStart, const IButton::EventType &OnHoverEnd) {
        m_OnHoverStart = OnHoverStart;
        m_OnHoverEnd = OnHoverEnd;
    }

    void IButton::SetOnClick(const IButton::EventType &OnClick) {
        m_OnClick = OnClick;
    }

    void IButton::SetOnDragOver(const IButton::EventType &OnDragOver) {
        m_OnDragOver = OnDragOver;
    }

    void IButton::Hover(bool isHovered) {
        if (isHovered && !m_IsHovered) {
            std::invoke(m_OnHoverStart, this);
        } else if (!isHovered && m_IsHovered) {
            std::invoke(m_OnHoverEnd, this);
        }
        m_IsHovered = isHovered;
    }

    void IButton::Click() {
        std::invoke(m_OnClick, this);
    }

    void IButton::DragOver() {
        std::invoke(m_OnDragOver, this);
    }
} // UI