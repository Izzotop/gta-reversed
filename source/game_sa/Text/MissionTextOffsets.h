#pragma once

#include "Text.h"

struct tTextOffset {
    char     szMissionName[8];
    uint32_t offset;
};

// TABL block
class CMissionTextOffsets {
public:
    static const uint16_t MAX_MISSION_TEXTS = 200;

    tTextOffset data[MAX_MISSION_TEXTS];
    uint32_t    size;

public:
    CMissionTextOffsets();;

    void Load(uint32_t length, FILE* file, uint32_t* offset, uint32_t nSkipBytes);
};
