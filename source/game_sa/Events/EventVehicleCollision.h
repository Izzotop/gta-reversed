#pragma once 
#include "Event.h"

class CVehicle;
class CVector;

enum eVehicleEvadeType
{
    VEHICLE_EVADE_NONE = 0,
    VEHICLE_EVADE_BY_HITSIDE = 1
};

class CEventVehicleCollision : public CEvent
{
public:
    int16_t m_pieceType;
    int16_t m_evadeType;
    float m_fDamageIntensity;
    CVehicle* m_vehicle;
    CVector m_collisionImpactVelocity;
    CVector m_collisionPosition;
    int8_t m_moveState;
    int8_t field_31;
    int8_t field_32[2];

    static void InjectHooks();

    CEventVehicleCollision(int16_t pieceType, float damageIntensity, CVehicle* vehicle, const CVector& collisionImpactVelocity, const CVector& collisionPosition, int8_t moveState, int16_t evadeType);
    ~CEventVehicleCollision();
private:
    CEventVehicleCollision* Constructor(int16_t pieceType, float damageIntensity, CVehicle* vehicle, const CVector& collisionImpactVelocity, const CVector& collisionPosition, int8_t moveState, int16_t evadeType);
public:
    eEventType GetEventType() override { return EVENT_VEHICLE_COLLISION; }
    int GetEventPriority() override { return 58; }
    int GetLifeTime() override { return 0; }
    CEvent* Clone() override;
    bool AffectsPed(CPed* ped) override;
    bool TakesPriorityOver(CEvent* refEvent) override { return true; }

    CEvent* Clone_Reversed();
    bool AffectsPed_Reversed(CPed* ped);
};

VALIDATE_SIZE(CEventVehicleCollision, 0x34);
