/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "TaskComplex.h"
#include "TaskTimer.h"
#include "TaskComplex.h"

class CTaskComplexKillPedOnFoot : public CTaskComplex {
public:
    uint8_t m_bit_1 : 1;
    uint8_t m_bit_2 : 1;
    uint8_t m_bit_3 : 1;
    uint8_t m_bit_4 : 1;
    uint8_t m_bit_5 : 1;
    uint8_t m_bit_6 : 1;
    uint8_t m_bit_7 : 1;
    uint8_t m_bit_8 : 1;
    uint8_t _pad0[3];
    CPed* m_target;
    uint32_t m_pedFlags;
    int32_t m_actionDelay;
    int32_t m_actionChance;
    uint8_t field_20;
    uint8_t _pad1[3];
    uint32_t m_startTime;
    uint32_t m_time;
    CTaskTimer m_timer;

    static void InjectHooks();

    CTaskComplexKillPedOnFoot(CPed* target, int32_t time, uint32_t pedFlags, int32_t delay, int32_t chance, int8_t a7);
    ~CTaskComplexKillPedOnFoot();
private:
    CTaskComplexKillPedOnFoot* Constructor(CPed* target, int32_t time, uint32_t pedFlags, int32_t delay, int32_t chance, int8_t a7);
public:
    CTask* Clone() override { return new CTaskComplexKillPedOnFoot(m_target, m_time, m_pedFlags, m_actionDelay, m_actionChance, field_20); }
    eTaskType GetId() override { return TASK_COMPLEX_KILL_PED_ON_FOOT; }
    bool MakeAbortable(CPed* ped, eAbortPriority priority, CEvent* event) override;
    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed* ped) override;
    void* CreateSubTask(int32_t taskId, CPed* ped);
};

VALIDATE_SIZE(CTaskComplexKillPedOnFoot, 0x38);
