#pragma once

#include <eEventType.h>

class CInterestingEvents {
public:
    using EType = eEventType;

    static void InjectHooks();

    CInterestingEvents();
    CInterestingEvents* Constructor();

    ~CInterestingEvents();
    CInterestingEvents* Destructor();

    void Add(eEventType type, CEntity* entity);
    void ScanForNearbyEntities();
    void GetInterestingEvent();
    void InvalidateEvent(const void* interestingEvent);
    void InvalidateNonVisibleEvents();
};

extern CInterestingEvents& g_InterestingEvents;
