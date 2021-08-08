#pragma once

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
    // char           _pad;
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

public:
    static void InjectHooks();

    static void Initialise();
    static void Shutdown();
    static void ClearAllExplosions();

    static int8_t GetExplosionActiveCounter(uint8_t id);
    static void ResetExplosionActiveCounter(uint8_t id);
    static bool DoesExplosionMakeSound(uint8_t id);
    static int32_t GetExplosionType(uint8_t id);
    static const CVector& GetExplosionPosition(uint8_t id);

    static bool TestForExplosionInArea(eExplosionType type, float minX, float maxX, float minY, float maxY, float minZ, float maxZ);
    static void RemoveAllExplosionsInArea(CVector pos, float r);
    static void AddExplosion(CEntity* pNewVictim, CEntity* pNewCreator, eExplosionType type, CVector pos, uint32_t lifetimea, uint8_t usesSound, float cameraShake, uint8_t isVisible);
    static void Update();

    static CExplosion* GetFree(); // NOTSA

    // NOTSA functions:
    void SetCreator(CEntity* pNewCreator) noexcept {
        if (m_pCreator)
            m_pCreator->CleanUpOldReference(&m_pCreator);

        if (pNewCreator)
            pNewCreator->RegisterReference(&m_pCreator);

        m_pCreator = pNewCreator;
    }

    void SetVictim(CEntity* pNewVictim) noexcept {
        if (m_pVictim)
            m_pVictim->CleanUpOldReference(&m_pVictim);

        if (pNewVictim)
            pNewVictim->RegisterReference(&m_pVictim);

        m_pVictim = pNewVictim;
    }
};
VALIDATE_SIZE(CExplosion, 0x7C);
