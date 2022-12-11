#include "GridsWithPortals.h"

namespace GridImpl {
    const NodeType &IGridDataHolder::GetCurrentNodeType() const {
        return CurrentNodeType;
    }

    void IGridDataHolder::SetTextures(std::map<NodeType, sf::Texture *> &NewTextures) {
        Textures = NewTextures;
        SetTextureFromNodeType();
    }
}