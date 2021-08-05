#pragma once
#include "TaskSimple.h"

class CTaskSimpleAchieveHeading : public CTaskSimple
{
public:
    int field_8;
    int field_C;
    int field_10;
    int field_14;

    CTaskSimpleAchieveHeading(float fAngle, float arg2, float arg3);
    ~CTaskSimpleAchieveHeading() override;

    bool ProcessPed(class CPed* ped) override;
    CTask* Clone() override;
    eTaskType GetId() override { return TASK_SIMPLE_ACHIEVE_HEADING; }
    bool MakeAbortable(CPed* ped, eAbortPriority priority, CEvent* _event) override;
};

VALIDATE_SIZE(CTaskSimpleAchieveHeading, 0x18);
