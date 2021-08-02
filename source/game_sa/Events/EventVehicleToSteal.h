#pragma once

#include "Event.h"

class CVehicle;

class CEventVehicleToSteal : public CEvent {
public:
    CVehicle* m_vehicle;

public:
    CEventVehicleToSteal(CVehicle* vehicle);
    ~CEventVehicleToSteal();

    eEventType GetEventType() override { return EVENT_VEHICLE_TO_STEAL; }
    int GetEventPriority() override { return 7; }
    int GetLifeTime() override { return 0; }
    CEvent* Clone() override { return new CEventVehicleToSteal(m_vehicle); }
    bool AffectsPed(CPed* ped) override;

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CEventVehicleToSteal* Constructor(CVehicle* vehicle);
    bool AffectsPed_Reversed(CPed* ped);
};
