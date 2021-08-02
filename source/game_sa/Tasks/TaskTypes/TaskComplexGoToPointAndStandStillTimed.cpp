#include "StdInc.h"

#include "TaskComplexGoToPointAndStandStillTimed.h"

#include "TaskComplexLeaveCar.h"
#include "TaskSimplePause.h"
#include "TaskSimpleStandStill.h"

void CTaskComplexGoToPointAndStandStillTimed::InjectHooks()
{
    HookInstall(0x6685E0, &CTaskComplexGoToPointAndStandStillTimed::Constructor);
    HookInstall(0x66CF30, &CTaskComplexGoToPointAndStandStillTimed::Clone_Reversed);
    HookInstall(0x6686A0, &CTaskComplexGoToPointAndStandStillTimed::StopTimer_Reversed);
    HookInstall(0x668640, &CTaskComplexGoToPointAndStandStillTimed::MakeAbortable_Reversed);
    HookInstall(0x66DC90, &CTaskComplexGoToPointAndStandStillTimed::CreateFirstSubTask_Reversed);
    HookInstall(0x66DCE0, &CTaskComplexGoToPointAndStandStillTimed::ControlSubTask_Reversed);
}

CTaskComplexGoToPointAndStandStillTimed::CTaskComplexGoToPointAndStandStillTimed(int moveState, const CVector& targetPoint, float fRadius, float fMoveStateRadius, int time)
    : CTaskComplexGoToPointAndStandStill(moveState, targetPoint, fRadius, fMoveStateRadius, false, false)
{
    m_nTime = time;
}

CTaskComplexGoToPointAndStandStillTimed::~CTaskComplexGoToPointAndStandStillTimed()
{
    // nothing here
}

// 0x6685E0
CTaskComplexGoToPointAndStandStillTimed* CTaskComplexGoToPointAndStandStillTimed::Constructor(int moveState, const CVector& targetPoint, float fRadius, float fMoveStateRadius, int time)
{
    this->CTaskComplexGoToPointAndStandStillTimed::CTaskComplexGoToPointAndStandStillTimed(moveState,  targetPoint, fRadius, fMoveStateRadius, time);
    return this;
}

// 0x66CF30
CTask* CTaskComplexGoToPointAndStandStillTimed::Clone()
{
    return CTaskComplexGoToPointAndStandStillTimed::Clone_Reversed();
}

// 0x6686A0
void CTaskComplexGoToPointAndStandStillTimed::StopTimer(CEvent* _event)
{
    return CTaskComplexGoToPointAndStandStillTimed::StopTimer_Reversed(_event);
}

// 0x668640
bool CTaskComplexGoToPointAndStandStillTimed::MakeAbortable(CPed* ped, eAbortPriority priority, CEvent* _event)
{
    return CTaskComplexGoToPointAndStandStillTimed::MakeAbortable_Reversed(ped, priority, _event);
}

// 0x66DC90
CTask* CTaskComplexGoToPointAndStandStillTimed::CreateFirstSubTask(CPed* ped)
{
    return CTaskComplexGoToPointAndStandStillTimed::CreateFirstSubTask_Reversed(ped);
}

// 0x66DCE0
CTask* CTaskComplexGoToPointAndStandStillTimed::ControlSubTask(CPed* ped)
{
    return CTaskComplexGoToPointAndStandStillTimed::ControlSubTask_Reversed(ped);
}

CTask* CTaskComplexGoToPointAndStandStillTimed::Clone_Reversed()
{
    return new CTaskComplexGoToPointAndStandStillTimed(m_moveState, m_vecTargetPoint, m_fRadius, m_fMoveStateRadius, m_nTime);
}


void CTaskComplexGoToPointAndStandStillTimed::StopTimer_Reversed(CEvent* _event)
{
    if (!CEventHandler::IsTemporaryEvent(_event)) 
        m_timer.Stop();
}

bool CTaskComplexGoToPointAndStandStillTimed::MakeAbortable_Reversed(CPed* ped, eAbortPriority priority, CEvent* _event)
{
    bool bSubTaskAbortable = m_pSubTask->MakeAbortable(ped, priority, _event);
    if (bSubTaskAbortable && priority == ABORT_PRIORITY_URGENT && (!_event || !CEventHandler::IsTemporaryEvent(_event)))
        m_timer.Stop();
    return bSubTaskAbortable;
}

CTask* CTaskComplexGoToPointAndStandStillTimed::CreateFirstSubTask_Reversed(CPed* ped)
{
    m_timer.Start(m_nTime);
    m_bTargetPointUpdated = false;
    if (ped->bInVehicle)
        return CTaskComplexGoToPointAndStandStill::CreateFirstSubTask(TASK_COMPLEX_LEAVE_CAR, ped);
    return CTaskComplexGoToPointAndStandStill::CreateFirstSubTask(TASK_SIMPLE_GO_TO_POINT, ped);
}

CTask* CTaskComplexGoToPointAndStandStillTimed::ControlSubTask_Reversed(CPed* ped)
{
    if (m_timer.Reset()) {
        if (m_timer.IsOutOfTime() && 
            m_pSubTask->GetId() != TASK_SIMPLE_STAND_STILL && CPedPlacement::FindZCoorForPed(&m_vecTargetPoint)) {            
            ped->SetPosn(m_vecTargetPoint);
        }
    }
    return CTaskComplexGoToPointAndStandStill::ControlSubTask(ped);
}
