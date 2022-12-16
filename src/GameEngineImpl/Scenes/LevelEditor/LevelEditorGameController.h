#ifndef PATHFINDING_LEVELEDITORGAMECONTROLLER_H
#define PATHFINDING_LEVELEDITORGAMECONTROLLER_H

#include "../../Game.h"
#include "../Traits/HasMouseEvents.h"
#include "../../../GridImpl/GridsWithPortals.h"
#include "common.h"
#include "../../../Utilities/SaveUtilities.h"

namespace GameEngineImpl::Scenes::LevelEditor {
    class LevelEditorScene;
    class LevelEditorGameMode;

    class LevelEditorGameController :
        public BaseGameControllerType<LevelEditorScene, LevelEditorGameMode, LevelEditorGameController>,
        public Traits::HasMouseEvents
    {
    public:
        LevelEditorGameController(Game* Game, LevelEditorScene* Scene, LevelEditorGameMode* GameMode);
        ~LevelEditorGameController() override = default;

        void ComputeInputs() override;

        template <typename DataHolderType>
        void HandleOnGridButtonClick(UI::IButton* Btn);
        template <typename DataHolderType>
        void HandleOnGridButtonHoverStart(UI::IButton* Btn);
        template <typename DataHolderType>
        void HandleOnGridButtonHoverEnd(UI::IButton* Btn);

        void HandleOnNodeTypeButtonClick(UI::IButton *Btn);

        void ResetNodeTypeButtons();
        void SaveNodes();
    private:
        NodeTypeButton* m_CurrentNodeTypeButton = nullptr;
        GridImpl::IGridDataHolder * m_LastPortal = nullptr;
        GridImpl::IGridDataHolder * m_PlayerStart = nullptr;
        Utilities::SaveUtilities SaveUtils;
    };

} // Scenes

#include "LevelEditorGameController.tpp"

#endif //PATHFINDING_LEVELEDITORGAMECONTROLLER_H
