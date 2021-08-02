#pragma once

#include "TaskComplex.h"

class CTaskComplexSequence;

enum ePartnerState : int8_t
{
    PARTNER_STATE_UNK_1 = 1
};

class CTaskComplexPartner : public CTaskComplex
{
public:
    int32_t field_C;
    int32_t field_10;
    char m_commandName[32];
    int32_t m_taskId;
    CPed* m_partner;
    float m_distanceMultiplier;
    CVector m_point;
    CVector m_targetPoint;
    bool m_leadSpeaker;
    ePartnerState m_partnerState;
    int8_t m_firstToTargetFlag;
    int8_t m_updateDirectionCount;
    bool m_taskCompleted;
    bool m_makePedAlwaysFacePartner;
    char m_animBlockName[16];
    bool m_requiredAnimsStreamedIn;
    int8_t padding;

    static void InjectHooks();

    CTaskComplexPartner(const char* commandName, CPed* partner, bool leadSpeaker, float distanceMultiplier, bool makePedAlwaysFacePartner, int8_t updateDirectionCount, CVector point);
    ~CTaskComplexPartner();
private:
    CTaskComplexPartner* Constructor(const char* commandName, CPed* partner, bool leadSpeaker, float distanceMultiplier, bool makePedAlwaysFacePartner, int8_t updateDirectionCount, CVector point);
public:
    eTaskType GetId() override { return TASK_COMPLEX_PARTNER; }
    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed* ped) override;
    virtual void StreamRequiredAnims();
    virtual void RemoveStreamedAnims();
};

VALIDATE_SIZE(CTaskComplexPartner, 0x70);
