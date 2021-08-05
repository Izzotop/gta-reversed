#include "StdInc.h"

#include "TaskComplexAvoidOtherPedWhileWandering.h"
#include "TaskComplexKillPedOnFoot.h"

void CEventPedCollisionWithPed::InjectHooks()
{
    HookInstall(0x4AC990, &CEventPedCollisionWithPed::Constructor);
    HookInstall(0x4ACAD0, &CEventPedCollisionWithPed::TakesPriorityOver_Reversed);
    HookInstall(0x4ACB10, &CEventPedCollisionWithPed::AffectsPed_Reversed);
}

void CEventPedCollisionWithPlayer::InjectHooks()
{
    HookInstall(0x5FED40, &CEventPedCollisionWithPlayer::Constructor);
}

void CEventPlayerCollisionWithPed::InjectHooks()
{
    HookInstall(0x5FEE40, &CEventPlayerCollisionWithPed::Constructor);
}

void CEventObjectCollision::InjectHooks()
{
    HookInstall(0x4ACCF0, &CEventObjectCollision::Constructor);
    HookInstall(0x4ACE30, &CEventObjectCollision::AffectsPed_Reversed);
}

void CEventBuildingCollision::InjectHooks()
{
    HookInstall(0x4ACF00, &CEventBuildingCollision::Constructor);
    HookInstall(0x4AD070, &CEventBuildingCollision::AffectsPed_Reversed);
    HookInstall(0x4AD1E0, &CEventBuildingCollision::IsHeadOnCollision);
    HookInstall(0x4B3120, &CEventBuildingCollision::CanTreatBuildingAsObject);
}

CEventPedCollisionWithPed::CEventPedCollisionWithPed(int16_t pieceType, float damageIntensity, CPed* victim, CVector* collisionImpactVelocity, CVector* collisionPos, int16_t moveState, int16_t victimMoveState)
{
    m_pieceType = pieceType;
    m_damageIntensity = damageIntensity;
    m_victim = victim;
    m_collisionImpactVelocity = *collisionImpactVelocity;
    m_collisionPos = *collisionPos;
    m_movestate = moveState;
    m_victimMoveState = victimMoveState;
    if (victim)
        victim->RegisterReference(reinterpret_cast<CEntity**>(&m_victim));
}

CEventPedCollisionWithPed::~CEventPedCollisionWithPed()
{
    if (m_victim)
        m_victim->CleanUpOldReference(reinterpret_cast<CEntity**>(&m_victim));
}

CEventPedCollisionWithPed* CEventPedCollisionWithPed::Constructor(int16_t pieceType, float damageIntensity, CPed* victim, CVector* collisionImpactVelocity, CVector* collisionPos, int16_t moveState, int16_t victimMoveState)
{
    this->CEventPedCollisionWithPed::CEventPedCollisionWithPed(pieceType, damageIntensity, victim, collisionImpactVelocity, collisionPos, moveState, victimMoveState);
    return this;
}

// 0x4ACAD0
bool CEventPedCollisionWithPed::TakesPriorityOver(CEvent* refEvent)
{
    return CEventPedCollisionWithPed::TakesPriorityOver_Reversed(refEvent);
}

// 0x4ACB10
bool CEventPedCollisionWithPed::AffectsPed(CPed* ped)
{
    return CEventPedCollisionWithPed::AffectsPed_Reversed(ped);
}

bool CEventPedCollisionWithPed::TakesPriorityOver_Reversed(CEvent* refEvent)
{
    if (CEventHandler::IsTemporaryEvent(refEvent))
        return true;

    return CEvent::TakesPriorityOver(refEvent);
}

bool CEventPedCollisionWithPed::AffectsPed_Reversed(CPed* ped)
{
    if (ped->IsAlive() && !ped->m_pAttachedTo && m_victim && !ped->bInVehicle && !m_victim->bInVehicle &&
        m_victim->GetIntelligence()->m_AnotherStaticCounter <= 30 && !ped->GetIntelligence()->IsThreatenedBy(*m_victim)) {
        if (m_movestate < PEDMOVE_WALK) {
            CPedGroup* victimGroup = CPedGroups::GetPedsGroup(m_victim);
            if (victimGroup && !victimGroup->GetMembership().IsLeader(m_victim)) {
                if (DotProduct(m_collisionImpactVelocity, ped->GetForward()) > -0.5f)
                    return false;
                CTask* pedPartnerTask = ped->GetTaskManager().FindActiveTaskByType(TASK_COMPLEX_PARTNER_DEAL);
                if (!pedPartnerTask)
                    pedPartnerTask = ped->GetTaskManager().FindActiveTaskByType(TASK_COMPLEX_PARTNER_GREET);
                if (pedPartnerTask) {
                    CTask* victimPartnerTask = m_victim->GetTaskManager().FindActiveTaskByType(TASK_COMPLEX_PARTNER_DEAL);
                    if (!victimPartnerTask)
                        victimPartnerTask = m_victim->GetTaskManager().FindActiveTaskByType(TASK_COMPLEX_PARTNER_GREET);
                    if (victimPartnerTask) {
                        if (pedPartnerTask->GetId() == victimPartnerTask->GetId())
                            return false;
                    }
                }
                CTask* pedActiveTask = ped->GetTaskManager().GetActiveTask();
                if (pedActiveTask && pedActiveTask->GetId() == TASK_COMPLEX_AVOID_OTHER_PED_WHILE_WANDERING
                    && reinterpret_cast<CTaskComplexAvoidOtherPedWhileWandering*>(pedActiveTask)->m_ped == m_victim)
                {
                    return false;
                }
                auto pTaskKillPedOnFoot = reinterpret_cast<CTaskComplexKillPedOnFoot*>(ped->GetTaskManager().FindActiveTaskByType(TASK_COMPLEX_KILL_PED_ON_FOOT));
                if (pTaskKillPedOnFoot && pTaskKillPedOnFoot->m_target == m_victim
                    && ped->GetTaskManager().FindActiveTaskByType(TASK_SIMPLE_FIGHT_CTRL)) {
                    return false;
                }
                else {
                    return true;
                }
            }
        }
    }
    return false;
}

CEventPedCollisionWithPlayer::CEventPedCollisionWithPlayer(int16_t pieceType, float damageIntensity, CPed* victim, CVector* collisionImpactVelocity, CVector* collisionPos, int16_t moveState, int16_t victimMoveState) :
    CEventPedCollisionWithPed(pieceType, damageIntensity, victim, collisionImpactVelocity, collisionPos, moveState, victimMoveState)
{
}

CEventPedCollisionWithPlayer* CEventPedCollisionWithPlayer::Constructor(int16_t pieceType, float damageIntensity, CPed* victim, CVector* collisionImpactVelocity, CVector* collisionPos, int16_t moveState, int16_t victimMoveState)
{
    this->CEventPedCollisionWithPlayer::CEventPedCollisionWithPlayer(pieceType, damageIntensity, victim, collisionImpactVelocity, collisionPos, moveState, victimMoveState);
    return this;
}

CEventPlayerCollisionWithPed::CEventPlayerCollisionWithPed(int16_t pieceType, float damageIntensity, CPed* victim, CVector* collisionImpactVelocity, CVector* collisionPos, int16_t moveState, int16_t victimMoveState) :
    CEventPedCollisionWithPed(pieceType, damageIntensity, victim, collisionImpactVelocity, collisionPos, moveState, victimMoveState)
{
}

CEventPlayerCollisionWithPed* CEventPlayerCollisionWithPed::Constructor(int16_t pieceType, float damageIntensity, CPed* victim, CVector* collisionImpactVelocity, CVector* collisionPos, int16_t moveState, int16_t victimMoveState)
{
    this->CEventPlayerCollisionWithPed::CEventPlayerCollisionWithPed(pieceType, damageIntensity, victim, collisionImpactVelocity, collisionPos, moveState, victimMoveState);
    return this;
}

CEventObjectCollision::CEventObjectCollision(int16_t pieceType, float damageIntensity, CObject* object, CVector* collisionImpactVelocity, CVector* collisionPos, int16_t moveState)
{
    m_pieceType = pieceType;
    m_moveState = moveState;
    m_damageIntensity = damageIntensity;
    m_object = object;
    m_collisionImpactVelocity = *collisionImpactVelocity;
    m_collisionPos = *collisionPos;
    if (m_object)
        m_object->RegisterReference(reinterpret_cast<CEntity**>(&m_object));
}

CEventObjectCollision::~CEventObjectCollision()
{
    if (m_object)
        m_object->CleanUpOldReference(reinterpret_cast<CEntity**>(&m_object));
}

CEventObjectCollision* CEventObjectCollision::Constructor(int16_t pieceType, float damageIntensity, CObject* object, CVector* collisionImpactVelocity, CVector* collisionPos, int16_t moveState)
{
    this->CEventObjectCollision::CEventObjectCollision(pieceType, damageIntensity, object, collisionImpactVelocity, collisionPos, moveState);
    return this;
}

// 0x4ACE30
bool CEventObjectCollision::AffectsPed(CPed* ped)
{
    return CEventObjectCollision::AffectsPed_Reversed(ped);
}

bool CEventObjectCollision::AffectsPed_Reversed(CPed* ped)
{
    if (!ped->m_pAttachedTo) {
        if (m_object && !m_object->physicalFlags.bDisableMoveForce) {
            if (!ped->IsPlayer() && ped->IsAlive()) 
                return true;
        }
    }
    return false;
}

CEventBuildingCollision::CEventBuildingCollision(int16_t pieceType, float damageIntensity, CBuilding* building, CVector* collisionImpactVelocity, CVector* collisionPos, int16_t moveState)
{
    m_pieceType = pieceType;
    m_moveState = moveState;
    m_damageIntensity = damageIntensity;
    m_building = building;
    m_collisionImpactVelocity = *collisionImpactVelocity;
    m_collisionPos = *collisionPos;
    if (building)
        m_building->RegisterReference(reinterpret_cast<CEntity**>(&m_building));
}

CEventBuildingCollision::~CEventBuildingCollision()
{
    if (m_building)
        m_building->CleanUpOldReference(reinterpret_cast<CEntity**>(&m_building));
}

CEventBuildingCollision* CEventBuildingCollision::Constructor(int16_t pieceType, float damageIntensity, CBuilding* building, CVector* collisionImpactVelocity, CVector* collisionPos, int16_t moveState)
{
    this->CEventBuildingCollision::CEventBuildingCollision(pieceType, damageIntensity, building, collisionImpactVelocity, collisionPos, moveState);
    return this;
}

// 0x4AD070
bool CEventBuildingCollision::AffectsPed(CPed* ped)
{
    return CEventBuildingCollision::AffectsPed_Reversed(ped);
}

bool CEventBuildingCollision::AffectsPed_Reversed(CPed* ped)
{
    if (!ped->IsPlayer()
        && ped->IsAlive()
        && m_moveState != PEDMOVE_STILL
        && (m_collisionImpactVelocity.z <= 0.707f || m_building->m_bIsTempBuilding)
        && !ped->m_pAttachedTo)
    {
        CVector direction(m_collisionImpactVelocity.x, m_collisionImpactVelocity.y, 0.0f);
        direction.Normalise();
        float dotProduct = DotProduct(direction, ped->GetForward());
        if (dotProduct <= -0.422f) {
            if (ped->GetEventHandler().GetCurrentEventType() == EVENT_BUILDING_COLLISION) {
                auto buildingColEvent = static_cast<CEventBuildingCollision*>(ped->GetEventHandlerHistory().GetCurrentEvent());
                if (buildingColEvent->m_building == m_building && dotProduct > -0.5f) 
                    return false;
            }
            // CEventPotentialWalkIntoBuilding doesn't even exist on PC
            assert (ped->GetEventHandler().GetCurrentEventType() != EVENT_POTENTIAL_WALK_INTO_BUILDING);
            if (dotProduct <= -0.5f && !ped->GetTaskManager().FindActiveTaskByType(TASK_COMPLEX_CLIMB))
                return ped->GetEventHandler().GetCurrentEventType() != EVENT_GUN_AIMED_AT;
        }
    }
    return false;
}

// 0x4AD1E0
bool CEventBuildingCollision::IsHeadOnCollision(CPed* ped)
{
    CVector velocity = m_collisionImpactVelocity;
    velocity.z = 0.0f;
    velocity.Normalise();
    return -DotProduct(velocity, ped->GetForward()) > 0.866f;
}

// 0x4B3120
bool CEventBuildingCollision::CanTreatBuildingAsObject(CBuilding* building)
{
    if (building->m_bIsTempBuilding)
        return true;
    CColModel* colModel = CModelInfo::GetModelInfo(building->m_nModelIndex)->GetColModel();
    CVector& boundMax = colModel->m_boundBox.m_vecMax;
    CVector& boundMin = colModel->m_boundBox.m_vecMin;
    float absoluteLengthX = fabs(boundMax.x - boundMin.x);
    float absoluteLengthY = fabs(boundMax.y - boundMin.y);
    float lengthZ = boundMax.z - boundMin.z;
    if (lengthZ < 2.0f && (absoluteLengthX < 6.0f || absoluteLengthY < 6.0f)
        || absoluteLengthX < 6.0f && absoluteLengthY < 6.0f)
    {
        return true;
    }
    return false;
}
