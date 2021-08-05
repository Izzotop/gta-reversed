#pragma once

#include "PluginBase.h"
#include "CVector.h"
#include "CAEExplosionAudioEntity.h"

enum eExplosionType : uint32_t {
    EXPLOSION_GRENADE,
    EXPLOSION_MOLOTOV,
    EXPLOSION_ROCKET,
    EXPLOSION_WEAK_ROCKET,
    EXPLOSION_CAR,
    EXPLOSION_QUICK_CAR,
    EXPLOSION_BOAT,
    EXPLOSION_AIRCRAFT,
    EXPLOSION_MINE,
    EXPLOSION_OBJECT,
    EXPLOSION_TANK_FIRE,
    EXPLOSION_SMALL,
    EXPLOSION_RC_VEHICLE
};

class CExplosion {
public:
    eExplosionType m_nType{};
    CVector        m_vecPosition{};
    float          m_fRadius{1.0f};
    float          m_fPropagationRate{};
    CEntity*       m_pCreator{};
    CEntity*       m_pVictim{};
    float          m_nExpireTime{};
    float          m_fDamagePercentage{};
    uint8_t        m_nActiveCounter{};
    byte           _pad{};
    bool           m_bMakeSound{true};
    float          m_nCreatedTime{};
    int32_t        m_nParticlesExpireTime{};
    float          m_fVisibleDistance{};
    float          m_fGroundZ{};
    int32_t        m_nFuelTimer{};
    CVector        m_vecFuelDirection[3]{};
    float          m_fFuelOffsetDistance[3]{};
    float          m_fFuelSpeed[3]{};

    static CAEExplosionAudioEntity& m_ExplosionAudioEntity;
    static CExplosion(&aExplosions)[16];

    static void InjectHooks();
    static void ClearAllExplosions();
    static void Shutdown();
    static int8_t GetExplosionActiveCounter(uchar id);
    static void ResetExplosionActiveCounter(uchar id);
    static bool DoesExplosionMakeSound(uchar id);
    static int32_t GetExplosionType(uchar id);
    static const CVector& GetExplosionPosition(uchar id);
    static bool TestForExplosionInArea(eExplosionType type, float minX, float maxX, float minY, float maxY, float minZ, float maxZ);
    static void RemoveAllExplosionsInArea(CVector pos, float r);
    static void Initialise();
    static int8_t AddExplosion(CEntity* pNewVictim, CEntity* pNewCreator, eExplosionType type, CVector const& pos, uint lifetimea, uchar usesSound, float cameraShake, uchar isVisible);
    static void Update();

};
VALIDATE_SIZE(CExplosion, 0x7C);
