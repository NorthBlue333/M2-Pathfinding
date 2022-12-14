#include "HasFonts.h"

namespace GameEngineImpl::Traits {
    template <typename EnumFontName>
    HasFonts<EnumFontName>::~HasFonts()
    {
        for (auto & Font : m_Fonts) {
            delete Font.second;
        }
    }
} // Traits