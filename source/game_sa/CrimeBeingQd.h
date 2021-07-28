/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Vector.h"

#include "eCrimeType.h"


class CCrimeBeingQd {
public:
    eCrimeType   m_nCrimeType;
    unsigned int m_nCrimeID;
    unsigned int m_nTimeOfQing;
    CVector      m_vecCoors;
    bool         m_bAlreadyReported;
    bool         m_bPoliceDontReallyCare;
    char         _pad1A[2];
};

VALIDATE_SIZE(CCrimeBeingQd, 0x1C);
