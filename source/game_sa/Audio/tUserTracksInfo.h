#pragma once

#include <cstdint>

#include "eAudioFileType.h"

struct tUserTracksInfo {
    uint32_t startUfilesPath;
    uint32_t pathLength;
    eAudioFileType fileType;
};

VALIDATE_SIZE(tUserTracksInfo, 0xc);
