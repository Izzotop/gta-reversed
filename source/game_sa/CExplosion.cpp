#include "StdInc.h"

CAEExplosionAudioEntity& CExplosion::m_ExplosionAudioEntity = *(CAEExplosionAudioEntity*)0xC888D0;
CExplosion(&CExplosion::aExplosions)[16] = *(CExplosion(*)[16])0xC88950;

void CExplosion::InjectHooks()
{
    ReversibleHooks::Install("CExplosion", "ClearAllExplosions", 0x736840, &CExplosion::ClearAllExplosions);
    ReversibleHooks::Install("CExplosion", "Shutdown", 0x7368F0, &CExplosion::Shutdown);
    ReversibleHooks::Install("CExplosion", "GetExplosionActiveCounter", 0x736900, &CExplosion::GetExplosionActiveCounter);
    ReversibleHooks::Install("CExplosion", "ResetExplosionActiveCounter", 0x736910, &CExplosion::ResetExplosionActiveCounter);
    ReversibleHooks::Install("CExplosion", "DoesExplosionMakeSound", 0x736920, &CExplosion::DoesExplosionMakeSound);
    //ReversibleHooks::Install("CExplosion", "GetExplosionType", 0x736930, &CExplosion::GetExplosionType);
    //ReversibleHooks::Install("CExplosion", "GetExplosionPosition", 0x736940, &CExplosion::GetExplosionPosition);
    //ReversibleHooks::Install("CExplosion", "TestForExplosionInArea", 0x736950, &CExplosion::TestForExplosionInArea);
    //ReversibleHooks::Install("CExplosion", "RemoveAllExplosionsInArea", 0x7369E0, &CExplosion::RemoveAllExplosionsInArea);
    //ReversibleHooks::Install("CExplosion", "Initialise", 0x736A40, &CExplosion::Initialise);
    //ReversibleHooks::Install("CExplosion", "AddExplosion", 0x736A50, &CExplosion::AddExplosion);
    //ReversibleHooks::Install("CExplosion", "Update", 0x737620, &CExplosion::Update);
}


void CExplosion::ClearAllExplosions()
{
    for (auto& exp : aExplosions) {
        exp = {};
        /*
        - We use the constructor here for code clarity, the original code is this:

        exp.m_vecPosition.x = {0.0f, 0.0f, 0.0f};
        exp.m_nType = 0;
        exp.m_fRadius = 1.0;
        exp.m_fVisibleDistance = 0.0;
        exp.m_fPropagationRate = 0.0;
        exp.m_fGroundZ = 0.0;
        exp.m_pCreator = 0;
        exp.m_pVictim = 0;
        exp.m_nExpireTime = 0.0;
        exp.m_nActiveCounter = 0;
        exp.m_nCreatedTime = 0.0;
        exp.m_bMakeSound = 1;
        exp.m_nFuelTimer = 0;

        for (auto i = 0; i < 3; i++) {
            exp.m_vecFuelDirection[i] = {0.0f, 0.0f, 0.0f};
            exp.m_fFuelOffsetDistance[i] = 0.0;
            exp.m_fFuelSpeed[i] = 0.0;
        }
        */
    }
}

void CExplosion::Shutdown()
{
    /* Empty */
}

int8_t CExplosion::GetExplosionActiveCounter(uchar id)
{
    return aExplosions[id]._pad;
}

void CExplosion::ResetExplosionActiveCounter(uchar id)
{
    aExplosions[id]._pad = 0;
}

bool CExplosion::DoesExplosionMakeSound(uchar id)
{
    return aExplosions[id].m_bMakeSound;
}

int32_t CExplosion::GetExplosionType(uchar id)
{
    return plugin::CallAndReturn<int32_t, 0x736930, uchar>(id);
}

CVector * CExplosion::GetExplosionPosition(uchar id)
{
    return plugin::CallAndReturn<CVector *, 0x736940, uchar>(id);
}

int8_t CExplosion::TestForExplosionInArea(eExplosionType type, float minX, float maxX, float minY, float maxY, float minZ, float maxZ)
{
    return plugin::CallAndReturn<int8_t, 0x736950, eExplosionType, float, float, float, float, float, float>(type, minX, maxX, minY, maxY, minZ, maxZ);
}

void CExplosion::RemoveAllExplosionsInArea(CVector pos, float r)
{
    return plugin::Call<0x7369E0, CVector, float>(pos, r);
}

void CExplosion::Initialise()
{
    return plugin::Call<0x736A40>();
}

int8_t CExplosion::AddExplosion(CEntity * pNewVictim, CEntity * pNewCreator, eExplosionType type, CVector const& pos, uint lifetimea, uchar usesSound, float cameraShake, uchar isVisible)
{
    return plugin::CallAndReturn<int8_t, 0x736A50, CEntity *, CEntity *, eExplosionType, CVector const&, uint, uchar, float, uchar>(pNewVictim, pNewCreator, type, pos, lifetimea, usesSound, cameraShake, isVisible);
}

void CExplosion::Update()
{
    return plugin::Call<0x737620>();
}

