#include "GridsWithPortals.h"

namespace GridImpl {
    template <template <typename NodeType> typename GridDataHolderType, typename GridNodeType>
    void
    GridDataHolder<GridDataHolderType, GridNodeType>::SetCurrentNodeType(NodeType NewType) {
        if (CurrentNodeType == NewType)
            return;
        SetLinkedPortal(nullptr);
        CurrentNodeType = NewType;
        SetTextureFromNodeType();
    }

    template <template <typename NodeType> typename GridDataHolderType, typename GridNodeType>
    const GridDataHolderType<GridNodeType>* GridDataHolder<GridDataHolderType, GridNodeType>::GetLinkedPortal() const {
        return LinkedPortal;
    }

    template <template <typename NodeType> typename GridDataHolderType, typename GridNodeType>
    void GridDataHolder<GridDataHolderType, GridNodeType>::SetLinkedPortal(GridDataHolderType<GridNodeType> *Linked) {
        if (CurrentNodeType != NodeType::Portal)
            return;

        if (LinkedPortal == Linked)
            return;

        auto OldPortal = LinkedPortal;
        LinkedPortal = Linked;
        if (nullptr != LinkedPortal)
            LinkedPortal->LinkedPortal = static_cast<GridDataHolderType<GridNodeType>*>(this);

        if (nullptr != OldPortal) {
            OldPortal->SetCurrentNodeType(NodeType::Empty);
        }
    }

    template <template <typename NodeType> typename GridDataHolderType, typename GridNodeType>
    std::vector<GridNodeType *> GridDataHolder<GridDataHolderType, GridNodeType>::GetAdditionalNeighbors() {
        if (CurrentNodeType != NodeType::Portal || LinkedPortal == nullptr)
            return {};

        return {LinkedPortal->Node};
    }

    template <template <typename NodeType> typename GridDataHolderType, typename GridNodeType>
    GridDataHolder<GridDataHolderType, GridNodeType>::~GridDataHolder()  {
        SetLinkedPortal(nullptr);
    }
} // GridImpl