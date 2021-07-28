/*
Plugin-SDK (Grand Theft Auto San Andreas) header file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "TaskSimple.h"
#include "AnimBlendAssociation.h"
#include "Entity.h"

class CTaskSimpleIKChain : public CTaskSimple {
public:
    int      m_time;
    int      m_blendTime;
    void*    m_pIKChain;
    short    m_slotID;
    short    m_pivotBoneTag;
    short    m_effectorBoneTag;
    char     _pad[2];
    RwV3d    m_effectorVec;
    CEntity* m_pEntity;
    int      m_offsetBoneTag;
    RwV3d    m_offsetPos;
    float    m_speed;
    bool     m_bEntityExist;
    char     _pad2[3];
    // blending info
    float    m_blend;
    int      m_endTime;
    float    m_targetBlend;
    int      m_targetTime;
    int      m_isBlendingOut;

    CTaskSimpleIKChain(char* _IGNORED_ idString, int effectorBoneTag, RwV3d effectorVec, int pivotBoneTag, CEntity* pEntity, int offsetBoneTag, RwV3d offsetPos, float speed,
                       int time, int blendTime);
};

VALIDATE_SIZE(CTaskSimpleIKChain, 0x58);
