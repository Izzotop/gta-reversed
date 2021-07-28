/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "AEAudioEntity.h"

class CAEPoliceScannerAudioEntity : public CAEAudioEntity {
public:
    void UpdateParameters(CAESound* sound, short curPlayPos) override;
};

VALIDATE_SIZE(CAEPoliceScannerAudioEntity, 0x7C);
