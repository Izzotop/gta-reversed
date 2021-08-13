/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "CTask.h"

class CPed;

class CTaskSimple : public CTask {
public:
    CTaskSimple();
    ~CTaskSimple();

    CTask* GetSubTask() override;
    bool IsSimple() override;
    virtual bool ProcessPed(CPed* ped) = 0;
    virtual bool SetPedPosition(CPed* ped);

private:
    friend void CTaskManager::InjectHooks();
    friend void InjectHooksMain();
    static void InjectHooks();

    CTaskSimple* Constructor();
    CTaskSimple* Destructor();
    CTask* GetSubTask_Reversed();
    bool IsSimple_Reversed();
    bool SetPedPosition_Reversed(CPed* ped);
};

VALIDATE_SIZE(CTaskSimple, 0x8);
