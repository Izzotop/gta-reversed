#include "StdInc.h"

#include "TaskSimpleRunAnim.h"

void CEventScriptCommand::InjectHooks()
{
    HookInstall(0x4B0A00, &CEventScriptCommand::Constructor);
    HookInstall(0x4B0A30, &CEventScriptCommand::GetEventType);
    HookInstall(0x4B0B20, &CEventScriptCommand::GetEventPriority);
    HookInstall(0x4B6490, &CEventScriptCommand::Clone);
    HookInstall(0x4B0AF0, &CEventScriptCommand::AffectsPed);
    HookInstall(0x4B0BA0, &CEventScriptCommand::TakesPriorityOver);
    HookInstall(0x4B0AB0, &CEventScriptCommand::IsValid);
    HookInstall(0x4B0AA0, &CEventScriptCommand::CloneScriptTask);
}

CEventScriptCommand::CEventScriptCommand(int32_t primaryTaskIndex, CTask* task, bool affectsDeadPeds)
{
    m_primaryTaskIndex = primaryTaskIndex;
    m_task = task;
    m_affectsDeadPeds = affectsDeadPeds;
}

CEventScriptCommand::~CEventScriptCommand()
{
    delete m_task;
}

// 0x4B0A00
CEventScriptCommand* CEventScriptCommand::Constructor(int32_t primaryTaskIndex, CTask* task, bool affectsDeadPeds)
{
    this->CEventScriptCommand::CEventScriptCommand(primaryTaskIndex, task, affectsDeadPeds);
    return this;
}

// 0x4B0B20
int CEventScriptCommand::GetEventPriority()
{
    return CEventScriptCommand::GetEventPriority_Reversed();
}

// 0x4B6490
CEvent* CEventScriptCommand::Clone()
{
    return CEventScriptCommand::Clone_Reversed();
}

// 0x4B0AF0
bool CEventScriptCommand::AffectsPed(CPed* ped)
{
    return CEventScriptCommand::AffectsPed_Reversed(ped);
}

// 0x4B0BA0
bool CEventScriptCommand::TakesPriorityOver(CEvent* refEvent)
{
    return CEventScriptCommand::TakesPriorityOver_Reversed(refEvent);
}

// 0x4B0AB0
bool CEventScriptCommand::IsValid(CPed* ped)
{
    return CEventScriptCommand::IsValid_Reversed(ped);
}

// 0x4B0AA0
CTask* CEventScriptCommand::CloneScriptTask()
{
    return CEventScriptCommand::CloneScriptTask_Reversed();
}

int CEventScriptCommand::GetEventPriority_Reversed()
{
    if (m_affectsDeadPeds)
        return 75;
    if (!m_task)
        return 53;
    const int32_t taskId = m_task->GetId();
    if (taskId == TASK_SIMPLE_NAMED_ANIM) {
        CTaskSimpleRunAnim* pTaskRunAnim = static_cast<CTaskSimpleRunAnim*>(m_task);
        if (pTaskRunAnim->m_nFlags & ANIM_FLAG_LOOPED)
            return 71;
    }
    if (taskId == TASK_SIMPLE_DIE || taskId == TASK_SIMPLE_SWIM || taskId == TASK_COMPLEX_USE_MOBILE_PHONE)
        return 71;
    if (taskId != TASK_COMPLEX_DIE)
        return 53;
    return 71;
}


CEvent*  CEventScriptCommand::Clone_Reversed()
{
    return new CEventScriptCommand(m_primaryTaskIndex, CloneScriptTask(), m_affectsDeadPeds);
}

bool CEventScriptCommand::AffectsPed_Reversed(CPed* ped)
{
    return ped->IsAlive() || m_affectsDeadPeds;
}

bool CEventScriptCommand::TakesPriorityOver_Reversed(CEvent* refEvent)
{
    eEventType refEventType = refEvent->GetEventType();
    if (m_affectsDeadPeds && (refEventType == EVENT_DEATH || m_affectsDeadPeds && refEventType == EVENT_DAMAGE))
        return true;
    return GetEventPriority() >= refEvent->GetEventPriority();
}

bool CEventScriptCommand::IsValid_Reversed(CPed* ped)
{
    if (ped)
        return ped->IsAlive();
    if (m_bValid || m_nTimeActive <= GetLifeTime())
        return true;
    return false;
}

CTask* CEventScriptCommand::CloneScriptTask_Reversed()
{
    if (m_task)
        return m_task->Clone();
    return nullptr;
}
