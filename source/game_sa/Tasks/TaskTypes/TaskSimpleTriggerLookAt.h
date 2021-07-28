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

class CTaskSimpleTriggerLookAt : public CTaskSimple {
public:
    CEntity* m_pEntity;
    int      m_time;
    int      m_offsetBoneTag;
    RwV3d    m_offsetPos;
    bool     m_bUseTorso;
    char     _pad[3];
    float    m_fSpeed;
    int      m_BlendTime;
    bool     m_bEntityExist;
    char     m_priority;
    char     _pad2[2];

public:
    CTaskSimpleTriggerLookAt(CEntity* pEntity, int time, int offsetBoneTag, RwV3d offsetPos, bool bUseTorso = true, float speed = 0.25f, int blendTime = 1000, int priority = 3);
};

VALIDATE_SIZE(CTaskSimpleTriggerLookAt, 0x30);
