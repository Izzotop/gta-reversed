/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Ped.h"

class CEmergencyPed : public CPed {
public:
    CEmergencyPed(unsigned int pedType, unsigned int modelIndex);

    bool InRange(CPed* ped);

    void ProcessControl();
};

VALIDATE_SIZE(CEmergencyPed, 0x79C);