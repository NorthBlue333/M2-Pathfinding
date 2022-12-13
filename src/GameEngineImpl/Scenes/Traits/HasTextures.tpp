#include "HasTextures.h"

namespace GameEngineImpl::Traits {
    template <typename EnumTextureName>
    HasTextures<EnumTextureName>::~HasTextures()
    {
        // SFML seems to already delete textures, this causes a double free exception
//        for (auto & Texture : m_Textures) {
//            delete Texture.second;
//        }
    }
} // Traits