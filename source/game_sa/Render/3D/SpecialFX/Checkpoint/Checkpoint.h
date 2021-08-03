/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "RGBA.h"
#include "Vector.h"

class CCheckpoint {
public:
    uint16_t m_nType;
    bool     m_bIsUsed;
    bool     m_bMustBeRenderedThisFrame;
    int      m_nIdentifier;
    CRGBA    m_colour;
    short    m_nPulsePeriod;
    short    m_nRotateRate;
    CVector  m_vecPosition;
    CVector  m_vecDirection;
    float    m_fPulseFraction;
    float    m_fSize;
    float    m_fDistanceToPlayer; //or CameraRange
    float    m_multiSize;

public:
    void Render();
};

VALIDATE_SIZE(CCheckpoint, 0x38);