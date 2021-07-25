#pragma once

#include "CVector2D.h"
#include "CVector.h"

struct CActiveOccluderLine
{
    CVector2D m_vecOrigin;
    CVector2D m_vecDirection;
    float m_fLength;
};
VALIDATE_SIZE(CActiveOccluderLine, 0x14);

struct CActiveOccluder
{
    CActiveOccluderLine m_aLines[6];
    int16_t m_wDepth;
    uint8_t m_cLinesCount;
    uint8_t m_cNumVectors;
    CVector m_aVectors[3];
    float m_afRadiuses[3];

public:
    bool IsPointWithinOcclusionArea(float fX, float fY, float fRadius);
    bool IsPointBehindOccluder(CVector vecPos, float fRadius);
};
VALIDATE_SIZE(CActiveOccluder, 0xAC);

struct COccluder
{
    int16_t m_wMidX;
    int16_t m_wMidY;
    int16_t m_wMidZ;
    int16_t m_wLength;
    int16_t m_wWidth;
    int16_t m_wHeight;
    uint8_t m_cRotZ;
    uint8_t m_cRotY;
    uint8_t m_cRotX;
    uint8_t m_cPad;
    struct
    {
        int16_t m_nNextIndex : 15;
        int16_t m_bFarAway : 1;
    };

public:
    bool ProcessOneOccluder(CActiveOccluder* pActiveOccluder);
    bool ProcessLineSegment(int iInd1, int iInd2, CActiveOccluder* pActiveOccluder);
    bool NearCamera();
};
VALIDATE_SIZE(COccluder, 0x12);

class COcclusion
{
public:
    static constexpr int MAX_INTERIOR_OCCLUDERS = 40;
    static constexpr int MAX_MAP_OCCLUDERS = 1000;
    static constexpr int MAX_ACTIVE_OCCLUDERS = 28;
    static constexpr int NUM_OCCLUDERS_PROCESSED_PER_FRAME = 16;

    static COccluder(&aInteriorOccluders)[MAX_INTERIOR_OCCLUDERS];
    static COccluder(&aOccluders)[MAX_MAP_OCCLUDERS];
    static CActiveOccluder(&aActiveOccluders)[MAX_ACTIVE_OCCLUDERS];

    static int& NumInteriorOcculdersOnMap;
    static int& NumOccludersOnMap;
    static int& NumActiveOccluders;
    static short& FarAwayList;
    static short& NearbyList;
    static short& ListWalkThroughFA;
    static short& PreviousListWalkThroughFA;

    static float& gMinXInOccluder;
    static float& gMaxXInOccluder;
    static float& gMinYInOccluder;
    static float& gMaxYInOccluder;

    static bool(&gOccluderCoorsValid)[8];
    static CVector(&gOccluderCoors)[8];
    static CVector(&gOccluderCoorsOnScreen)[8];
    static CVector& gCenterOnScreen;

public:
    static void InjectHooks();

public:
    static void Init();
    static void AddOne(float centerX, float centerY, float centerZ, float width, float length, float height, float rotZ, float rotY, float rotX, uint32_t flags, bool isInterior);
    static bool OccluderHidesBehind(CActiveOccluder* first, CActiveOccluder* second);
    static bool IsPositionOccluded(CVector vecPos, float fRadius);
    static void ProcessBeforeRendering();
};
