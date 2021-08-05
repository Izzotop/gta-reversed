#include "StdInc.h"

void CAEExplosionAudioEntity::InjectHooks()
{
    //ReversibleHooks::Install("CAEExplosionAudioEntity", "Constructor", 0x5074B0, &CAEExplosionAudioEntity::Constructor);
    //ReversibleHooks::Install("CAEExplosionAudioEntity", "Destructor", 0x506B90, &CAEExplosionAudioEntity::Destructor);
    //ReversibleHooks::Install("CAEExplosionAudioEntity", "AddAudioEvent", 0x4DCBE0, &CAEExplosionAudioEntity::AddAudioEvent);
    //ReversibleHooks::Install("CAEExplosionAudioEntity", "StaticInitialise", 0x5B9A60, &CAEExplosionAudioEntity::StaticInitialise);
}

CAEExplosionAudioEntity::CAEExplosionAudioEntity()
{
}

CAEExplosionAudioEntity::~CAEExplosionAudioEntity()
{
}

CAEExplosionAudioEntity* CAEExplosionAudioEntity::Destructor()
{
    this->CAEExplosionAudioEntity::~CAEExplosionAudioEntity();
    return this;
}

CAEExplosionAudioEntity* CAEExplosionAudioEntity::Constructor()
{
    this->CAEExplosionAudioEntity::CAEExplosionAudioEntity();
    return this;
}

void CAEExplosionAudioEntity::AddAudioEvent(eAudioEvents event, const CVector& pos, float volume)
{
    return plugin::CallMethod<0x4DCBE0, CAEExplosionAudioEntity*, eAudioEvents, const CVector&, float>(this, event, pos, volume);
}

bool CAEExplosionAudioEntity::StaticInitialise()
{
    return plugin::CallAndReturn<bool, 0x5B9A60>();
}
