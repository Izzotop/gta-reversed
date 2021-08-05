#pragma once

#include "eAudioEvents.h"
#include "CAEAudioEntity.h"

class CAEExplosionAudioEntity : public CAEAudioEntity {
public:
    int8_t field_7C;
    int8_t _pad7D[3];

    static void InjectHooks();

    CAEExplosionAudioEntity();
    ~CAEExplosionAudioEntity();

private:
    CAEExplosionAudioEntity* Destructor();
    CAEExplosionAudioEntity* Constructor();

public:
    void AddAudioEvent(eAudioEvents event, const CVector& pos, float volume);
    static bool StaticInitialise();

};
VALIDATE_SIZE(CAEExplosionAudioEntity, 0x80);
