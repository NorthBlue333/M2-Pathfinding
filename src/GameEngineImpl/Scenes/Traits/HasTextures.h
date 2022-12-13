#ifndef PATHFINDING_HASTEXTURES_H
#define PATHFINDING_HASTEXTURES_H

#include <map>
#include <SFML/Graphics/Texture.hpp>

namespace GameEngineImpl::Traits {
    template <typename EnumTextureName>
    class HasTextures {
    protected:
        std::map<EnumTextureName, sf::Texture*> m_Textures;
        virtual ~HasTextures();
    };

} // Traits

#include "HasTextures.tpp"

#endif //PATHFINDING_HASTEXTURES_H
