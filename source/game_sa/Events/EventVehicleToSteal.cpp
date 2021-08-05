#include "StdInc.h"

#include "EventVehicleToSteal.h"

#include "TaskComplexEnterCar.h"

void CEventVehicleToSteal::InjectHooks()
{
    HookInstall(0x4AF670, &CEventVehicleToSteal::Constructor);
    HookInstall(0x4AF760, &CEventVehicleToSteal::AffectsPed_Reversed);
}

CEventVehicleToSteal::CEventVehicleToSteal(CVehicle* vehicle)
{
    m_vehicle = vehicle;
    if (m_vehicle)
        m_vehicle->RegisterReference(reinterpret_cast<CEntity**>(&m_vehicle));
}

CEventVehicleToSteal::~CEventVehicleToSteal()
{
    if (m_vehicle)
        m_vehicle->CleanUpOldReference(reinterpret_cast<CEntity**>(&m_vehicle));
}

// 0x4AF670
CEventVehicleToSteal* CEventVehicleToSteal::Constructor(CVehicle* vehicle)
{
    this->CEventVehicleToSteal::CEventVehicleToSteal(vehicle);
    return this;
}

// 0x4AF760
bool CEventVehicleToSteal::AffectsPed(CPed* ped)
{
    return CEventVehicleToSteal::AffectsPed_Reversed(ped);
}

bool CEventVehicleToSteal::AffectsPed_Reversed(CPed* ped)
{
    if (ped->IsAlive() && m_vehicle) {
        auto taskManager = FindPlayerPed()->GetTaskManager();
        auto enterCarAsDriverTask = reinterpret_cast<CTaskComplexEnterCar*>(taskManager.FindTaskByType(TASK_PRIMARY_PRIMARY, TASK_COMPLEX_ENTER_CAR_AS_DRIVER));
        if (!enterCarAsDriverTask || !enterCarAsDriverTask->m_pTargetVehicle) {
            if (m_vehicle == FindPlayerPed()->m_pVehicle
                && (CTheScripts::IsPlayerOnAMission() || CPad::GetPad(0)->bPlayerSafe))
            {
                return false;
            }
            return ped->m_nPedType == PED_TYPE_CRIMINAL && ped->m_pVehicle != m_vehicle
                || ped->m_nPedType == PED_TYPE_COP && m_vehicle == ped->m_pVehicle;
        }
    }
    return false;
}
