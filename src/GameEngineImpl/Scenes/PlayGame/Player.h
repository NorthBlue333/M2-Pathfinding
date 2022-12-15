#ifndef PATHFINDING_PLAYER_H
#define PATHFINDING_PLAYER_H

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../../../Grid/BaseGrid.h"

namespace GameEngineImpl::Scenes::PlayGame {
    class Player {
    public:
        /// In pixels per sec
        static int constexpr MOVEMENT_SPEED = 10;

        explicit Player(Grid::Coordinates2D Coordinates);
        ~Player() = default;

        void Render(sf::RenderWindow* Window) const;
        sf::Rect<float> GetGlobalBounds() const;
        void SetPosition(float x, float y);
        sf::Vector2<float> GetPosition() const;
        const Grid::Coordinates2D& GetCoordinates() const;
    private:
        Grid::Coordinates2D m_Coordinates;

        sf::CircleShape m_Circle;
    };
}

#endif //PATHFINDING_PLAYER_H
