#include "GridsWithPortals.h"

namespace GridImpl {
    template <template <typename NodeType, bool WithDiagonals> typename GridDataHolderType, typename GridNodeType, bool WithDiagonals>
    void
    GridDataHolder<GridDataHolderType, GridNodeType, WithDiagonals>::SetCurrentNodeType(NodeType NewType) {
        if (CurrentNodeType == NewType)
            return;
        SetLinkedPortal(nullptr);
        CurrentNodeType = NewType;
        SetTextureFromNodeType();
    }

    template <template <typename NodeType, bool WithDiagonals> typename GridDataHolderType, typename GridNodeType, bool WithDiagonals>
    const GridDataHolderType<GridNodeType, WithDiagonals>* GridDataHolder<GridDataHolderType, GridNodeType, WithDiagonals>::GetLinkedPortal() const {
        return LinkedPortal;
    }

    template <template <typename NodeType, bool WithDiagonals> typename GridDataHolderType, typename GridNodeType, bool WithDiagonals>
    void GridDataHolder<GridDataHolderType, GridNodeType, WithDiagonals>::SetLinkedPortal(GridDataHolderType<GridNodeType, WithDiagonals> *Linked) {
        if (CurrentNodeType != NodeType::Portal)
            return;

        if (LinkedPortal == Linked)
            return;

        auto OldPortal = LinkedPortal;
        LinkedPortal = Linked;
        if (nullptr != LinkedPortal)
            LinkedPortal->LinkedPortal = static_cast<GridDataHolderType<GridNodeType, WithDiagonals>*>(this);

        if (nullptr != OldPortal) {
            if (OldPortal->LinkedPortal == this)
                OldPortal->LinkedPortal = nullptr;
            OldPortal->SetCurrentNodeType(NodeType::Empty);
        }
    }

    template <template <typename NodeType, bool WithDiagonals> typename GridDataHolderType, typename GridNodeType, bool WithDiagonals>
    std::vector<GridNodeType *> GridDataHolder<GridDataHolderType, GridNodeType, WithDiagonals>::GetAdditionalNeighbors() {
        if (CurrentNodeType != NodeType::Portal || LinkedPortal == nullptr)
            return {};

        return {LinkedPortal->Node};
    }

    template <template <typename NodeType, bool WithDiagonals> typename GridDataHolderType, typename GridNodeType, bool WithDiagonals>
    GridDataHolder<GridDataHolderType, GridNodeType, WithDiagonals>::~GridDataHolder()  {
        SetLinkedPortal(nullptr);
    }
} // GridImpl