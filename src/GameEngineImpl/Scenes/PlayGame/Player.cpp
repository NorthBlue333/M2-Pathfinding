#include "Player.h"

namespace GameEngineImpl::Scenes::PlayGame {
    void Player::Render(sf::RenderWindow *Window) const {
        Window->draw(m_Circle);
    }

    Player::Player(Grid::Coordinates2D Coordinates) {
        m_Coordinates = Coordinates;
        m_Circle.setPosition(Coordinates.X, Coordinates.Y);
        m_Circle.setFillColor(sf::Color::Green);
        m_Circle.setRadius(10.f);
    }

    sf::Rect<float> Player::GetGlobalBounds() const {
        return m_Circle.getGlobalBounds();
    }

    void Player::SetPosition(float x, float y) {
        m_Circle.setPosition(x, y);
    }

    sf::Vector2<float> Player::GetPosition() const {
        return m_Circle.getPosition();
    }

    const Grid::Coordinates2D &Player::GetCoordinates() const {
        return m_Coordinates;
    }
}
