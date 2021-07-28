#pragma once
#include "TaskComplex.h"

class CTaskComplexInAirAndLand : public CTaskComplex
{
public:
    unsigned char m_bUsingJumpGlide;
    unsigned char m_bUsingFallGlide;
    unsigned char m_bInvalidClimb;
    unsigned char _pad;

private:
    CTaskComplexInAirAndLand* Constructor(bool bUsingJumpGlide, bool bUsingFallGlide);
public:
    CTaskComplexInAirAndLand(bool bUsingJumpGlide, bool bUsingFallGlide);
    ~CTaskComplexInAirAndLand() override {}

    static void InjectHooks();

    CTask* Clone() override { return new CTaskComplexInAirAndLand(m_bUsingJumpGlide, m_bUsingFallGlide); }
    eTaskType GetId() override { return TASK_COMPLEX_IN_AIR_AND_LAND; }
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed* ped) override;

    CTask* CreateFirstSubTask_Reversed(CPed* ped);
    CTask* CreateNextSubTask_Reversed(CPed* ped);
    CTask* ControlSubTask_Reversed(CPed* ped);
};

VALIDATE_SIZE(CTaskComplexInAirAndLand, 0x10);
