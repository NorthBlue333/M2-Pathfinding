#ifndef PATHFINDING_HASFONTS_H
#define PATHFINDING_HASFONTS_H

#include <map>
#include <SFML/Graphics/Font.hpp>

namespace GameEngineImpl::Traits {
    template <typename EnumFontName>
    class HasFonts {
    protected:
        std::map<EnumFontName, sf::Font*> m_Fonts;
        virtual ~HasFonts();
    };

} // Traits

#include "HasFonts.tpp"

#endif //PATHFINDING_HASFONTS_H
