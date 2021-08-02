#pragma once
#include "EventEditableResponse.h"
#include "Vector.h"

class CVehicle;
class CEventPotentialWalkIntoVehicle : public CEventEditableResponse {
public:
    CVehicle* m_vehicle;
    int32_t m_moveState;

    static void InjectHooks();

    CEventPotentialWalkIntoVehicle(CVehicle* vehicle, int32_t moveState);
    ~CEventPotentialWalkIntoVehicle();
private:
    CEventPotentialWalkIntoVehicle* Constructor(CVehicle* vehicle, int32_t moveState);
public:
    eEventType GetEventType() override { return EVENT_POTENTIAL_WALK_INTO_VEHICLE; }
    bool TakesPriorityOver(CEvent* refEvent) override { return true; }
    CEventPotentialWalkIntoVehicle* CloneEditable() override { return new CEventPotentialWalkIntoVehicle(m_vehicle, m_moveState); }
    int32_t GetEventPriority() override { return 29; }
    int32_t GetLifeTime() override { return 0; }
    bool AffectsPed(CPed* ped) override;
private:
    bool AffectsPed_Reversed(CPed* ped);
};

VALIDATE_SIZE(CEventPotentialWalkIntoVehicle, 0x1C);

class CObject;
class CEventPotentialWalkIntoObject : public CEventEditableResponse {
public:
    CObject* m_object;
    int32_t m_moveState;

    static void InjectHooks();

    CEventPotentialWalkIntoObject(CObject* object, int32_t moveState);
    ~CEventPotentialWalkIntoObject();
private:
    CEventPotentialWalkIntoObject* Constructor(CObject* object, int32_t moveState);
public:
    eEventType GetEventType() override { return EVENT_POTENTIAL_WALK_INTO_OBJECT; }
    bool TakesPriorityOver(CEvent* refEvent) override { return true; }
    CEventPotentialWalkIntoObject* CloneEditable() override { return new CEventPotentialWalkIntoObject(m_object, m_moveState); }
    int32_t GetEventPriority() override { return 27; }
    int32_t GetLifeTime() override { return 0; }
    bool AffectsPed(CPed* ped) override;
private:
    bool AffectsPed_Reversed(CPed* ped);
};

VALIDATE_SIZE(CEventPotentialWalkIntoObject, 0x1C);

class CEventPotentialWalkIntoFire : public CEventEditableResponse {
public:
    CVector m_firePos;
    float m_fireSize;
    float m_radius;
    int32_t m_moveState;

    static void InjectHooks();

    CEventPotentialWalkIntoFire(CVector* firePos, float fireSize, int32_t moveState);
    ~CEventPotentialWalkIntoFire() {}
private:
    CEventPotentialWalkIntoFire* Constructor(CVector* firePos, float fireSize, int32_t moveState);
public:
    eEventType GetEventType() override { return EVENT_POTENTIAL_WALK_INTO_FIRE; }
    int32_t GetEventPriority() override { return 31; }
    int32_t GetLifeTime() override { return 0; }
    bool AffectsPed(CPed* ped) override;
    CEventPotentialWalkIntoFire* CloneEditable() override { return new CEventPotentialWalkIntoFire(&m_firePos, m_fireSize, m_moveState); }
private:
    bool AffectsPed_Reversed(CPed* ped);
};

VALIDATE_SIZE(CEventPotentialWalkIntoFire, 0x2C);


class CEventPotentialWalkIntoPed : public CEventEditableResponse {
public:
    CVector m_targetPoint;
    CPed* m_ped;
    int32_t m_moveState;

    static void InjectHooks();

    CEventPotentialWalkIntoPed(CPed* ped, CVector* targetPoint, int32_t moveState);
    ~CEventPotentialWalkIntoPed();
private:
    CEventPotentialWalkIntoPed* Constructor(CPed* ped, CVector* targetPoint, int32_t moveState);
public:
    eEventType GetEventType() override { return EVENT_POTENTIAL_WALK_INTO_PED; }
    int32_t GetEventPriority() override { return 28; }
    int32_t GetLifeTime() override { return 0; }
    bool AffectsPed(CPed* ped) override;
    CEntity* GetSourceEntity() override { return m_ped; }
    bool TakesPriorityOver(CEvent* refEvent) override;
    CEventPotentialWalkIntoPed* CloneEditable() override { return new CEventPotentialWalkIntoPed(m_ped, &m_targetPoint, m_moveState); }
private:
    bool AffectsPed_Reversed(CPed* ped);
    bool TakesPriorityOver_Reversed(CEvent* refEvent);
};

VALIDATE_SIZE(CEventPotentialWalkIntoPed, 0x28);

