/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "RGBA.h"

struct tPickupMessage {
    float x;
    float y;
    float z;
    float width;
    float height;
    CRGBA color;
    unsigned char flags;
    char field_19;
    char _pad1A[2];
    unsigned int price;
    char *messageText;
};

VALIDATE_SIZE(tPickupMessage, 0x24);