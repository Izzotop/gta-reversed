/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Vector.h"

class CSphere {
public:
    CVector m_vecCenter;
    float   m_fRadius;

public:
    void Set(float radius, CVector const& center);
};

VALIDATE_SIZE(CSphere, 0x10);