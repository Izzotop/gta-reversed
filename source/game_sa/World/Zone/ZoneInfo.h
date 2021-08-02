/*
Plugin-SDK (Grand Theft Auto San Andreas) header file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "RenderWare.h"

class CZoneInfo {
public:
    uint8_t GangDensity[10];
    uint8_t DrugDealerCounter;
    RwRGBA ZoneColor;
    union {
        struct {
            uint8_t zonePopulationType : 5;
        };
        uint8_t Flags1;
    };
    uint8_t Flags2;
};

VALIDATE_SIZE(CZoneInfo, 0x11);
