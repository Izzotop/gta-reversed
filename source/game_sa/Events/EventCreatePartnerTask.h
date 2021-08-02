#pragma once
#include "Event.h"

class CEventCreatePartnerTask : public CEvent
{
public:
    int32_t m_randomNumber;
    CPed* m_partner;
    bool m_leadSpeaker;
    float m_distanceMultiplier;

    static void InjectHooks();

    CEventCreatePartnerTask(int32_t randomNumber, CPed* partner, bool leadSpeaker, float distanceMultiplier);
    ~CEventCreatePartnerTask();
private:
    CEventCreatePartnerTask* Constructor(int32_t randomNumber, CPed* partner, bool leadSpeaker, float distanceMultiplier);
public:
    eEventType GetEventType() override { return EVENT_CREATE_PARTNER_TASK; }
    int GetEventPriority() override { return 6; }
    int GetLifeTime() override { return 0; }
    CEvent* Clone() override { return new CEventCreatePartnerTask(m_randomNumber, m_partner, m_leadSpeaker, m_distanceMultiplier); }
    bool AffectsPed(CPed* ped) override { return true; }
};

VALIDATE_SIZE(CEventCreatePartnerTask, 0x1C);
