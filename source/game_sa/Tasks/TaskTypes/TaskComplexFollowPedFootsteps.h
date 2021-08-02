#include "TaskComplex.h"

class CPointRoute;

class CTaskComplexFollowPedFootsteps : public CTaskComplex {
public:
    CPed*        m_targetPed;
    uint32_t     m_subTaskCreateCheckTimer;
    uint32_t     m_lineOfSightCheckTimer;
    CPointRoute* m_pointRoute;
    int16_t      m_moveState;
    uint8_t      m_updateGoToPoint : 1;

public:
    static void InjectHooks();

    CTaskComplexFollowPedFootsteps(CPed* ped);
    ~CTaskComplexFollowPedFootsteps();
private:
    CTaskComplexFollowPedFootsteps* Constructor(CPed* ped);
public:
    CTask* Clone() override { return new CTaskComplexFollowPedFootsteps(m_targetPed); }
    eTaskType GetId() override { return TASK_COMPLEX_FOLLOW_PED_FOOTSTEPS; }
    bool MakeAbortable(CPed* ped, eAbortPriority priority, CEvent* event) override;
    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed* ped) override;
    virtual CTask* CreateSubTask(eTaskType taskType, CPed* ped);

};

VALIDATE_SIZE(CTaskComplexFollowPedFootsteps, 0x20);
