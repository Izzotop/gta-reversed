/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "FileObjectInstance.h"

struct tBinaryIplFile {
    char           fourcc[4]; // "bnry"
    unsigned short numInstances;
    char           _unused06[14];
    unsigned short numCarGenerators;
    char           _unused16[6];
    unsigned int   instancesOffset; // file offset to CFileObjectInstance structures
    char           _unused20[28];
    unsigned int   carGeneratorsOffset;
    char           _unused40[12];
};

VALIDATE_SIZE(tBinaryIplFile, 0x4C);