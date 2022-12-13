#ifndef PATHFINDING_LEVELEDITORGAMECONTROLLER_H
#define PATHFINDING_LEVELEDITORGAMECONTROLLER_H

#include "../../common_types.h"
#include "../Traits/HasMouseEvents.h"
#include "../../../GridImpl/GridsWithPortals.h"
#include "common.h"

namespace GameEngineImpl::Scenes {
    class LevelEditorScene;
    class LevelEditorGameMode;

    class LevelEditorGameController :
        public BaseGameControllerType<LevelEditorScene, LevelEditorGameMode, LevelEditorGameController>,
        public Traits::HasMouseEvents
    {
    public:
        LevelEditorGameController(GameType* Game, LevelEditorScene* Scene, LevelEditorGameMode* GameMode);
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
    private:
        NodeTypeButton* m_CurrentNodeTypeButton = nullptr;
        GridImpl::IGridDataHolder * m_LastPortal = nullptr;
        GridImpl::IGridDataHolder * m_PlayerStart = nullptr;
    };

} // Scenes

#include "LevelEditorGameController.tpp"

#endif //PATHFINDING_LEVELEDITORGAMECONTROLLER_H
