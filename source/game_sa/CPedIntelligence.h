/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "CTaskManager.h"
#include "CEventHandler.h"
#include "CEventGroup.h"
#include "CEntityScanner.h"
#include "CTaskTimer.h"
#include "CEventScanner.h"
#include "CTaskSimpleUseGun.h"
#include "CTaskSimpleFight.h"
#include "CTaskSimpleHoldEntity.h"
#include "CTaskSimpleThrowProjectile.h"
#include "CTaskSimpleSwim.h"
#include "CTaskSimpleDuck.h"
#include "CTaskSimpleClimb.h"
#include "CTaskSimpleJetPack.h"
#include "CTaskSimpleInAir.h"
#include "CPedStuckChecker.h"
#include "CVehicleScanner.h"

enum eEventType;

class CPedIntelligence {
public:
    class CPed    *m_pPed;
    CTaskManager   m_TaskMgr;
    CEventHandler  m_eventHandler;
    CEventGroup    m_eventGroup;
    int            m_nDecisionMakerType;
    int            m_nDecisionMakerTypeInGroup;
    float          m_fHearingRange;
    float          m_fSeeingRange;
    unsigned int   m_nDmNumPedsToScan;
    float          m_fDmRadius;
    int field_CC;
    char field_D0;
    unsigned char m_nEventId;
    unsigned char m_nEventPriority;
    char field_D3;
    CVehicleScanner m_vehicleScanner;
    CEntityScanner m_entityScanner;
    char field_174;
    char gap_175[3];
    CTaskTimer field_178;
    int field_184;
    char field_188;
    char gap_189[3];
    CEventScanner m_eventScanner;
    bool field_260;
    char field_261[3];
    CPedStuckChecker m_pedStuckChecker;
    int m_AnotherStaticCounter;
    int m_StaticCounter;
    CVector m_vecLastPedPosDuringDamageEntity;
    class CEntity* m_apInterestingEntities[3];

    static float& STEALTH_KILL_RANGE;
    static float& LIGHT_AI_LEVEL_MAX;
    static float& flt_8D2384;
    static float& flt_8D2388;

public:
    static void InjectHooks();

    static void* operator new(unsigned int size);
    static void operator delete(void* object);

    CEntity** GetPedEntities();
    void SetPedDecisionMakerType(int newType);
    void SetPedDecisionMakerTypeInGroup(int newType);
    void RestorePedDecisionMakerType();
    void SetHearingRange(float range);
    void SetSeeingRange(float range);
    bool IsInHearingRange(CVector const& posn);
    bool IsInSeeingRange(CVector const& posn);
    bool FindRespectedFriendInInformRange();
    bool IsRespondingToEvent(eEventType eventType);
    void AddTaskPhysResponse(CTask* pTask, int unUsed);
    void AddTaskEventResponseTemp(CTask* pTask, int unUsed);
    void AddTaskEventResponseNonTemp(CTask* pTask, int unUsed);
    void AddTaskPrimaryMaybeInGroup(CTask* pTask, bool bAffectsPed);
    CTask* FindTaskByType(int taskId);
    CTaskSimpleFight* GetTaskFighting();
    CTaskSimpleUseGun* GetTaskUseGun();
    CTaskSimpleThrowProjectile* GetTaskThrow();
    CTask* GetTaskHold(bool bIgnoreCheckingForSimplestActiveTask);
    CTaskSimpleSwim* GetTaskSwim();
    CTaskSimpleDuck* GetTaskDuck(bool bIgnoreCheckingForSimplestActiveTask);
    CTaskSimpleJetPack* GetTaskJetPack();
    CTaskSimpleInAir* GetTaskInAir();
    CTaskSimpleClimb* GetTaskClimb();
    bool GetUsingParachute();
    void SetTaskDuckSecondary(unsigned short nLengthOfDuck);
    void ClearTaskDuckSecondary();
    void ClearTasks(bool bClearPrimaryTasks, bool bClearSecondaryTasks);
    void FlushImmediately(bool bSetPrimaryDefaultTask);
    C2dEffect* GetEffectInUse();
    void SetEffectInUse(C2dEffect* effect);
    void ProcessAfterProcCol();
    void ProcessAfterPreRender();
    void ProcessEventHandler();
    bool IsFriendlyWith(CPed* pPed);
    bool IsThreatenedBy(CPed const& ped);
    bool Respects(CPed* pPed);
    bool IsInACarOrEnteringOne();
    static bool AreFriends(CPed* ped1, CPed* ped2);
    bool IsPedGoingSomewhereOnFoot();
    int GetMoveStateFromGoToTask();
    void FlushIntelligence();
    bool TestForStealthKill(CPed* pTarget, bool bFullTest);
    void RecordEventForScript(int EventID, int EventPriority);
    bool HasInterestingEntites();
    bool IsInterestingEntity(CEntity* pEntity);
    void LookAtInterestingEntities();
    void RemoveAllInterestingEntities();
    bool IsPedGoingForCarDoor();
    float CanSeeEntityWithLights(CEntity* pEntity, int unUsed);
    void ProcessStaticCounter();
    void ProcessFirst();
    void Process();
    CTask* GetActivePrimaryTask();
    float GetPedFOVRange();
};

VALIDATE_SIZE(CPedIntelligence, 0x294);
