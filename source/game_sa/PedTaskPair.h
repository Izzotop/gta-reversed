/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Ped.h"
#include "Task.h"

class CPedTaskPair {
public:
    CPed* m_pPed;
    CTask* m_pTask;
    int32_t m_taskSlot;
    int32_t field_C;
    int8_t field_10;

public:
    void Flush();
};

VALIDATE_SIZE(CPedTaskPair, 0x14);
