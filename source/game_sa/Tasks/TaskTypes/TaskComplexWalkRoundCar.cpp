#include "StdInc.h"

#include "TaskComplexWalkRoundCar.h"

void CTaskComplexWalkRoundCar::SetNewVehicle(CVehicle* vehicle, uint8_t flags)
{
    plugin::CallMethod<0x654290, CTaskComplexWalkRoundCar*, CVehicle*, uint8_t>(this, vehicle, flags);
}
