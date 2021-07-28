#include "TaskComplex.h"
#include "TaskTimer.h"

class CPed;

class CTaskComplexWaitForPed : public CTaskComplex
{
public:
    CPed* m_ped;
    float m_radius;
    std::uint32_t m_timeInMs;
    bool m_bRotateOtherPedsToWaitingPed;
private:
    char padding[3];
    CTaskTimer m_timer;
    std::int32_t m_framesToWaitForSettingRotation;
};

VALIDATE_SIZE(CTaskComplexWaitForPed, 0x2C);
