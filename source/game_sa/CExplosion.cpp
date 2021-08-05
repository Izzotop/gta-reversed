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
    ReversibleHooks::Install("CExplosion", "GetExplosionType", 0x736930, &CExplosion::GetExplosionType);
    ReversibleHooks::Install("CExplosion", "GetExplosionPosition", 0x736940, &CExplosion::GetExplosionPosition);
    ReversibleHooks::Install("CExplosion", "TestForExplosionInArea", 0x736950, &CExplosion::TestForExplosionInArea);
    ReversibleHooks::Install("CExplosion", "RemoveAllExplosionsInArea", 0x7369E0, &CExplosion::RemoveAllExplosionsInArea);
    ReversibleHooks::Install("CExplosion", "Initialise", 0x736A40, &CExplosion::Initialise);
    ReversibleHooks::Install("CExplosion", "AddExplosion", 0x736A50, &CExplosion::AddExplosion);
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
    return aExplosions[id].m_nType;
}

const CVector& CExplosion::GetExplosionPosition(uchar id)
{
    return aExplosions[id].m_vecPosition;
}

bool CExplosion::TestForExplosionInArea(eExplosionType type, float minX, float maxX, float minY, float maxY, float minZ, float maxZ)
{
    const CBoundingBox boundingBox{ {minX, minY, minZ}, {maxX, maxY, maxZ} };
    for (auto& exp : aExplosions) {
        if (!exp.m_nActiveCounter)
            continue;
        if (type != -1 && exp.m_nType != type)
            continue;
        if (boundingBox.IsPointWithin(exp.m_vecPosition))
            return true;
    }
    return false;
}

void CExplosion::RemoveAllExplosionsInArea(CVector pos, float r)
{
    for (auto& exp : aExplosions) {
        if (!exp.m_nActiveCounter)
            continue;
        if (DistanceBetweenPointsSquared(exp.m_vecPosition, pos) < r * r) {
            exp.m_nActiveCounter = 0;
        }
    }
}

void CExplosion::Initialise()
{
    ClearAllExplosions();
}

CExplosion* CExplosion::GetFree() {
    for (auto& exp : aExplosions) {
        if (!exp.m_nActiveCounter)
            return &exp;
    }
    return nullptr;
}

bool DoesNeedToVehProcessBombTimer(eExplosionType type) {
    switch (type) {
    case eExplosionType::EXPLOSION_ROCKET:
    case eExplosionType::EXPLOSION_QUICK_CAR:
    case eExplosionType::EXPLOSION_MINE:
    case eExplosionType::EXPLOSION_OBJECT:
    case eExplosionType::EXPLOSION_TANK_FIRE:
        return true;
    }
    return false;
};

void CExplosion::AddExplosion(CEntity * pVictim, CEntity * pCreator, eExplosionType type, CVector pos, uint lifetime, uchar usesSound, float cameraShake, uchar isVisible)
{
    if (auto pExp = GetFree()) {
        pExp->m_vecPosition = pos;
        pExp->m_nType = type;
        pExp->m_fRadius = 1.0f;
        pExp->m_fVisibleDistance = 0.0f;
        pExp->m_fGroundZ = 0.0f;
        pExp->m_fDamagePercentage = 0.0f;
        pExp->m_nActiveCounter = 1;
        pExp->_pad = 1;
        pExp->m_bMakeSound = usesSound;
        pExp->m_nFuelTimer = 0;
        pExp->SetCreator(pCreator);
        pExp->SetVictim(pVictim);

        for (auto i = 0; i < 3; i++) {
            float& fOffsetDistance = pExp->m_fFuelOffsetDistance[i];
            float& fFuelSpeed = pExp->m_fFuelSpeed[i];
            CVector& vecFuelDir = pExp->m_vecFuelDirection[i];

            if (i && rand() >= RAND_MAX / 2) {
                fOffsetDistance = 0.0f;
            } else {
                vecFuelDir = CVector{
                    2 * CGeneral::GetRandomNumberInRange(0.0f, 1.0f) - 1.0f,
                    2 * CGeneral::GetRandomNumberInRange(0.0f, 1.0f) - 1.0f,
                    CGeneral::GetRandomNumberInRange(0.2f, 1.0f)
                };
                fOffsetDistance = CGeneral::GetRandomNumberInRange(0.5f, 2.0f);
                fFuelSpeed = CGeneral::GetRandomNumberInRange(20.0f, 30.0f);
            }
        }

        pExp->m_nParticlesExpireTime = lifetime ? CTimer::m_snTimeInMilliseconds + lifetime : 0;

        const auto PlaySoundIfEnabled = [&]() {
            if (pExp->m_bMakeSound) {
                m_ExplosionAudioEntity.AddAudioEvent(eAudioEvents::AE_EXPLOSION, pExp->m_vecPosition, -36.0f);
            }
        };

        // Originally most likeley a separate function
        // but this way its nicer
        const auto CreateAndPlayFxWithSound = [&](const char* name) {
            FxSystem_c* pFx{nullptr};
            if (pExp->m_pVictim) {
                if (RwObject* pRwObj = pExp->m_pVictim->m_pRwObject) {
                    if (RwMatrix* pMatrix = pExp->m_pVictim->GetModellingMatrix()) {
                        CVector expToVictimDir = pos - pExp->m_pVictim->GetPosition();
                        pFx = g_fxMan.CreateFxSystem(
                            name,
                            &expToVictimDir,
                            pMatrix,
                            false
                        );
                    }
                }
            } else {
                pFx = g_fxMan.CreateFxSystem(name, &pExp->m_vecPosition, nullptr, false);
            }
            if (pFx) {
                PlaySoundIfEnabled();
                pFx->PlayAndKill();
            }
        };

        if (isVisible) {
            pExp->m_fRadius = 0.0f;
            pExp->m_fVisibleDistance = 0.0f;
        }

        bool bNoFire = false;
        switch (type) {
        case eExplosionType::EXPLOSION_GRENADE: {
            if (!isVisible) {
                pExp->m_fRadius = 9.0f;
                pExp->m_fVisibleDistance = 300.0f;
            }
            pExp->m_nExpireTime = (float)(CTimer::m_snTimeInMilliseconds + lifetime + 750);
            pExp->m_fPropagationRate = 0.5f;
            if (pExp->m_pVictim) {

            } else {
                CreateAndPlayFxWithSound("explosion_small");
            }
            break;
        }
        case eExplosionType::EXPLOSION_MOLOTOV: {
            if (!isVisible) {
                pExp->m_fRadius = 6.0f;
            }
            pExp->m_nExpireTime = (float)(CTimer::m_snTimeInMilliseconds + lifetime + 3000);

            bool bHit = false;
            const float fGroundPos = CWorld::FindGroundZFor3DCoord(
                pos.x,
                pos.y,
                pos.z + 3.0f,
                &bHit,
                nullptr
            );
            if (bHit)
                pos.z = fGroundPos;

            float fWaterLevel{};
            if (CWaterLevel::GetWaterLevelNoWaves(pos.x, pos.y, pos.z, &fWaterLevel, nullptr, nullptr)) {
                /* must be done like this because of call order */
                if (pos.z < fWaterLevel) {
                    bNoFire = true;
                    break;
                }
            }

            CreateAndPlayFxWithSound("explosion_molotov");

            break;
        }
        case eExplosionType::EXPLOSION_ROCKET:
        case eExplosionType::EXPLOSION_WEAK_ROCKET: {
            if (!isVisible) {
                pExp->m_fRadius = 10.0f;
                pExp->m_fVisibleDistance = 300.0f;
            }
            if (type == eExplosionType::EXPLOSION_WEAK_ROCKET) {
                pExp->m_fVisibleDistance = 200.0f;
                pExp->m_fDamagePercentage = 0.2f;
            }
            pExp->m_nExpireTime = (float)(CTimer::m_snTimeInMilliseconds + lifetime + 750);
            pExp->m_fPropagationRate = 0.5f;

            CreateAndPlayFxWithSound("explosion_small");
        }
        case eExplosionType::EXPLOSION_CAR:
        case eExplosionType::EXPLOSION_QUICK_CAR: {
            if (!isVisible) {
                pExp->m_fRadius = 9.0f;
                pExp->m_fVisibleDistance = 300.0f;
            }
            pExp->m_nExpireTime = (float)(CTimer::m_snTimeInMilliseconds + lifetime + 4250);
            pExp->m_fPropagationRate = 0.5f;
            pExp->m_nCreatedTime = (float)CTimer::m_snTimeInMilliseconds;

            if (pExp->m_pVictim) {
                CCrime::ReportCrime(eCrimeType::CRIME_EXPLOSION, pExp->m_pVictim->AsPed(), nullptr); /* won't do anything as second ped is nullptr */
            }
            CreateAndPlayFxWithSound("explosion_medium");
        }
        case eExplosionType::EXPLOSION_BOAT:
        case eExplosionType::EXPLOSION_AIRCRAFT: {
            if (!isVisible) {
                pExp->m_fRadius = 25.0f;
                pExp->m_fVisibleDistance = 600.0f;
            }
            pExp->m_nExpireTime = (float)(CTimer::m_snTimeInMilliseconds + lifetime + 3000);
            pExp->m_nCreatedTime = (float)CTimer::m_snTimeInMilliseconds;

            CreateAndPlayFxWithSound("explosion_large");
        }
        case eExplosionType::EXPLOSION_MINE: {
            if (!isVisible) {
                pExp->m_fRadius = 10.0f;
                pExp->m_fVisibleDistance = 150.0f;
            }
            pExp->m_nExpireTime = (float)(CTimer::m_snTimeInMilliseconds + lifetime + 750);
            pExp->m_fPropagationRate = 0.5f;

            PlaySoundIfEnabled();
            /* No fx for this */
            break;
        }
        case eExplosionType::EXPLOSION_TANK_FIRE: {
            if (!isVisible) {
                pExp->m_fRadius = 10.0f;
                pExp->m_fVisibleDistance = 150.0f;
            }
            pExp->m_nExpireTime = (float)(CTimer::m_snTimeInMilliseconds + lifetime + 750);
            pExp->m_fPropagationRate = 0.5f;

            CreateAndPlayFxWithSound("explosion_large");
            break;
        }
        case eExplosionType::EXPLOSION_SMALL: {
            if (!isVisible) {
                pExp->m_fRadius = 3.0f;
                pExp->m_fVisibleDistance = 90.0f;
            }
            pExp->m_nExpireTime = (float)(CTimer::m_snTimeInMilliseconds + lifetime + 750);
            pExp->m_fPropagationRate = 0.5f;

            CreateAndPlayFxWithSound("explosion_small");
            break;
        }
        case eExplosionType::EXPLOSION_RC_VEHICLE: {
            if (!isVisible) {
                pExp->m_fRadius = 3.0f;
                pExp->m_fVisibleDistance = 90.0f;
            }
            pExp->m_nExpireTime = (float)(CTimer::m_snTimeInMilliseconds + lifetime + 750);
            pExp->m_fPropagationRate = 0.5f;

            CreateAndPlayFxWithSound("explosion_tiny");
            break;
        }
        }
        if (!bNoFire) {
            switch (type) {
            case eExplosionType::EXPLOSION_MOLOTOV:
            case eExplosionType::EXPLOSION_ROCKET:
            case eExplosionType::EXPLOSION_WEAK_ROCKET:
            case eExplosionType::EXPLOSION_OBJECT: {
                const auto numFires = (type == eExplosionType::EXPLOSION_MOLOTOV) ?
                    (rand() - 2) % 4 : (rand() + 1) % 4;
                if (numFires) {
                    for (auto i = 0; i < numFires; i++) {
                        const CVector firePos = pExp->m_vecPosition + CVector{
                            CGeneral::GetRandomNumberInRange(-4.0f, 4.0f),
                            CGeneral::GetRandomNumberInRange(-4.0f, 4.0f),
                            0.0f
                        };
                        bool bHitGround{};
                        const float fGroundZ = CWorld::FindGroundZFor3DCoord(firePos.x, firePos.y, firePos.z + 3.0f, &bHitGround, nullptr);
                        if (bHitGround && fabs(firePos.z - pExp->m_vecPosition.z) < 10.0f) {
                            gFireManager.StartFire(
                                firePos,
                                0.8f,
                                0,
                                pExp->m_pCreator,
                                CGeneral::GetRandomNumberInRange(5600.0f, 12600.0f) * 0.4f,
                                3,
                                1
                            );
                        }
                    }
                    if (pCreator && pCreator->IsPed() && pCreator->AsPed()->IsPlayer())
                        CStats::IncrementStat(eStats::STAT_FIRES_STARTED, 1.0f);
                }
                break;
            }
            }
        }

        if (pVictim)
            g_InterestingEvents.Add(eEventType::EVENT_ATTRACTOR, pVictim);
        CShadows::AddPermanentShadow(
            eShadowType::SHADOW_DEFAULT, gpShadowHeliTex, &pos, 8.0f, 0.0f, 0.0f, -8.0f, 200, 0, 0, 0, 10.0f, 30000, 1.0f);
        if (pExp->m_fVisibleDistance != 0.0f && !pExp->m_nParticlesExpireTime) {
            CWorld::TriggerExplosion(
                pos,
                pExp->m_fRadius,
                pExp->m_fVisibleDistance,
                pVictim,
                pCreator,
                DoesNeedToVehProcessBombTimer(type),
                pExp->m_fDamagePercentage
            );
        }
        if (type == eExplosionType::EXPLOSION_MOLOTOV) {
            TheCamera.CamShake(cameraShake == -1.0f ? 0.2f : cameraShake, pos.x, pos.y, pos.z);
        } else {
            if (cameraShake == -1.0f)
                cameraShake = 0.6f;
            TheCamera.CamShake(cameraShake, pos.x, pos.y, pos.z);

            CPad::GetPad(0)->StartShake_Distance(300, 128, pos);
            if (CGameLogic::IsCoopGameGoingOn())
                CPad::GetPad(1)->StartShake_Distance(300, 128, pos);
        }
    }
}

void CExplosion::Update()
{
    return plugin::Call<0x737620>();
}

