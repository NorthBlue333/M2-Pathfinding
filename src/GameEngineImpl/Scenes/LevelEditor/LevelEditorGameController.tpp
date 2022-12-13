#include "LevelEditorGameController.h"
#include "LevelEditorGameController.h"
#include "LevelEditorScene.h"

namespace GameEngineImpl::Scenes {
    template <typename DataHolderType>
    void LevelEditorGameController::HandleOnGridButtonClick(UI::IButton *Btn) {
        if (nullptr == m_CurrentNodeTypeButton)
            return;

        auto CastedBtn = static_cast<GridNodeButton<DataHolderType>*>(Btn);
        if (nullptr == CastedBtn || nullptr == CastedBtn->DataHolder)
            return;

        CastedBtn->DataHolder->SetCurrentNodeType(m_CurrentNodeTypeButton->TargetNodeType);

        if (m_CurrentNodeTypeButton->TargetNodeType == GridImpl::NodeType::PlayerStart) {
            auto PlayerStart = dynamic_cast<DataHolderType*>(m_PlayerStart);
            if (nullptr != PlayerStart && PlayerStart != CastedBtn->DataHolder) {
                PlayerStart->SetCurrentNodeType(GridImpl::NodeType::Empty);
            }

            m_PlayerStart = CastedBtn->DataHolder;
        }

        if (nullptr == CastedBtn->DataHolder->GetLinkedPortal() && nullptr == m_LastPortal && m_CurrentNodeTypeButton->TargetNodeType == GridImpl::NodeType::Portal) {
            m_LastPortal = CastedBtn->DataHolder;
        } else {
            auto LastPortal = dynamic_cast<DataHolderType*>(m_LastPortal);
            if (nullptr != LastPortal && LastPortal != CastedBtn->DataHolder) {
                if (m_CurrentNodeTypeButton->TargetNodeType == GridImpl::NodeType::Portal) {
                    LastPortal->SetLinkedPortal(CastedBtn->DataHolder);
                    m_LastPortal = nullptr;
                } else {
                    LastPortal->SetCurrentNodeType(GridImpl::NodeType::Empty);
                    m_LastPortal = nullptr;
                }
            }
        }
    }

    template <typename DataHolderType>
    void LevelEditorGameController::HandleOnGridButtonHoverStart(UI::IButton *Btn) {
        auto CastedBtn = static_cast<GridNodeButton<DataHolderType>*>(Btn);
        if (
            nullptr == CastedBtn->DataHolder
            || CastedBtn->DataHolder->GetCurrentNodeType() != GridImpl::NodeType::Portal
            || nullptr == CastedBtn->DataHolder->GetLinkedPortal()
        )
            return;

        CastedBtn->ShowOverlay();
        CastedBtn->DataHolder->GetLinkedPortal()->GetGridNodeButton()->ShowOverlay();
    }

    template <typename DataHolderType>
    void LevelEditorGameController::HandleOnGridButtonHoverEnd(UI::IButton *Btn) {
        auto CastedBtn = static_cast<GridNodeButton<DataHolderType>*>(Btn);

        if (
            nullptr == CastedBtn->DataHolder
            || CastedBtn->DataHolder->GetCurrentNodeType() != GridImpl::NodeType::Portal
            || nullptr == CastedBtn->DataHolder->GetLinkedPortal()
        )
            return;

        CastedBtn->HideOverlay();
        CastedBtn->DataHolder->GetLinkedPortal()->GetGridNodeButton()->HideOverlay();
    }
} // Scenes