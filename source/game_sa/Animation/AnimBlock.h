/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

class CAnimBlock {
public:
    char  szName[16];
    bool  bLoaded;
    char  _pad;
    short usRefs;
    int   startAnimation;
    int   animationCount;
    int   animationStyle;
};

VALIDATE_SIZE(CAnimBlock, 0x20);
