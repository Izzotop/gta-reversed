/*
Plugin-SDK (Grand Theft Auto San Andreas) header file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "TaskComplex.h"
#include "Vehicle.h"
#include "TaskUtilityLineUpPedWithCar.h"

class CTaskComplexLeaveCar : public CTaskComplex {
public:
    CVehicle* m_pTargetVehicle;
    int m_nTargetDoor;
    int m_nDelayTime;
    bool m_bSensibleLeaveCar;
    bool m_bForceGetOut;
    bool m_bDie;
    char _pad1;
    CTaskUtilityLineUpPedWithCar *m_pTaskUtilityLineUpPedWithCar;
    unsigned char m_nDoorFlagsSet;
    unsigned char m_nNumGettingInSet;
    char _pad2[2];
    int m_nDieAnimID;
    float m_fDieAnimBlendDelta;
    float m_fDieAnimSpeed;
    bool m_bIsInAir;
    char _pad3[3];

public:
    CTaskComplexLeaveCar(CVehicle* pTargetVehicle, int nTargetDoor, int nDelayTime, bool bSensibleLeaveCar, bool bForceGetOut);
    ~CTaskComplexLeaveCar();

    CTaskComplexLeaveCar* Constructor(CVehicle* pTargetVehicle, int nTargetDoor, int nDelayTime, bool bSensibleLeaveCar, bool bForceGetOut);

    CTask* Clone() override;
    eTaskType GetId() override { return TASK_COMPLEX_LEAVE_CAR; }
    bool MakeAbortable(CPed* ped, eAbortPriority priority, CEvent* _event) override;
    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed* ped) override;
};

VALIDATE_SIZE(CTaskComplexLeaveCar, 0x34);

