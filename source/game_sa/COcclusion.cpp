#include "StdInc.h"

COccluder(&COcclusion::aInteriorOccluders)[MAX_INTERIOR_OCCLUDERS] = *(COccluder(*)[MAX_INTERIOR_OCCLUDERS])0xC73CC8;
COccluder(&COcclusion::aOccluders)[MAX_MAP_OCCLUDERS] = *(COccluder(*)[MAX_MAP_OCCLUDERS])0xC73FA0;
CActiveOccluder(&COcclusion::aActiveOccluders)[MAX_ACTIVE_OCCLUDERS] = *(CActiveOccluder(*)[MAX_ACTIVE_OCCLUDERS])0xC78610;

int& COcclusion::NumInteriorOcculdersOnMap = *(int*)0xC73CC4;
int& COcclusion::NumOccludersOnMap = *(int*)0xC73F98;
int& COcclusion::NumActiveOccluders = *(int*)0xC73CC0;
short& COcclusion::FarAwayList = *(short*)0x8D5D68;
short& COcclusion::NearbyList = *(short*)0x8D5D6C;
short& COcclusion::ListWalkThroughFA = *(short*)0x8D5D70;
short& COcclusion::PreviousListWalkThroughFA = *(short*)0x8D5D74;

float& COcclusion::gMinXInOccluder = *(float*)0xC73CAC;
float& COcclusion::gMaxXInOccluder = *(float*)0xC73CA8;
float& COcclusion::gMinYInOccluder = *(float*)0xC73CA4;
float& COcclusion::gMaxYInOccluder = *(float*)0xC73CA0;

bool(&COcclusion::gOccluderCoorsValid)[8] = *(bool(*)[8])0xC73CB0;
CVector(&COcclusion::gOccluderCoors)[8] = *(CVector(*)[8])0xC798E0;
CVector(&COcclusion::gOccluderCoorsOnScreen)[8] = *(CVector(*)[8])0xC79950;
CVector& COcclusion::gCenterOnScreen = *(CVector*)0xC79940;

void COcclusion::InjectHooks()
{
    ReversibleHooks::Install("COcclusion", "Init", 0x71DCA0, &COcclusion::Init);
    ReversibleHooks::Install("COcclusion", "AddOne", 0x71DCD0, &COcclusion::AddOne);
    ReversibleHooks::Install("COcclusion", "IsPositionOccluded", 0x7200B0, &COcclusion::IsPositionOccluded);
}

void COcclusion::Init()
{
    COcclusion::NumOccludersOnMap = 0;
    COcclusion::NumInteriorOcculdersOnMap = 0;
    COcclusion::FarAwayList = -1;
    COcclusion::NearbyList = -1;
    COcclusion::ListWalkThroughFA = -1;
    COcclusion::PreviousListWalkThroughFA = -1;
}

void COcclusion::AddOne(float centerX, float centerY, float centerZ, float width, float length, float height, float rotX, float rotY, float rotZ, uint32_t flags, bool isInterior)
{
    int numMissingDimensions = 0;

    auto iWidth = static_cast<int32_t>(fabs(width));
    auto iLength = static_cast<int32_t>(fabs(length));
    auto iHeight = static_cast<int32_t>(fabs(height));

    if (!iLength)
        numMissingDimensions++;
    if (!iWidth)
        numMissingDimensions++;
    if (!iHeight)
        numMissingDimensions++;

    if (numMissingDimensions > 1)
        return;

    // Get the angles in [0 : 360] space and convert to radians
    auto fRotX = DegreesToRadians(CGeneral::LimitAngle(rotX) + 180.0F);
    auto fRotY = DegreesToRadians(CGeneral::LimitAngle(rotY) + 180.0F);
    auto fRotZ = DegreesToRadians(CGeneral::LimitAngle(rotZ) + 180.0F);
    const auto fTwoPiToChar = 256.0F / TWO_PI;

    if (isInterior)
    {
        auto& occluder = COcclusion::aInteriorOccluders[COcclusion::NumInteriorOcculdersOnMap];
        occluder.m_fMidX = centerX * 4.0F;
        occluder.m_fMidY = centerY * 4.0F;
        occluder.m_fMidZ = centerZ * 4.0F;
        occluder.m_fWidth = iWidth * 4.0F;
        occluder.m_fLength = iLength * 4.0F;
        occluder.m_fHeight = iHeight * 4.0F;
        occluder.m_cRotX = rotX * fTwoPiToChar;
        occluder.m_cRotY = rotY * fTwoPiToChar;
        occluder.m_cRotZ = rotZ * fTwoPiToChar;
        ++COcclusion::NumInteriorOcculdersOnMap;
    }
    else
    {
        auto& occluder = COcclusion::aOccluders[COcclusion::NumOccludersOnMap];
        occluder.m_fMidX = centerX * 4.0F;
        occluder.m_fMidY = centerY * 4.0F;
        occluder.m_fMidZ = centerZ * 4.0F;
        occluder.m_fWidth = iWidth * 4.0F;
        occluder.m_fLength = iLength * 4.0F;
        occluder.m_fHeight = iHeight * 4.0F;
        occluder.m_cRotX = rotX * fTwoPiToChar;
        occluder.m_cRotY = rotY * fTwoPiToChar;
        occluder.m_cRotZ = rotZ * fTwoPiToChar;

        if (flags)
            occluder.m_bFarAway = true;
        else
            occluder.m_bFarAway = false;

        occluder.m_nNextIndex = COcclusion::FarAwayList;
        COcclusion::FarAwayList = COcclusion::NumOccludersOnMap;
        ++COcclusion::NumOccludersOnMap;
    }
}

bool COcclusion::OccluderHidesBehind(CActiveOccluder* first, CActiveOccluder* second)
{
    return plugin::CallAndReturn<bool, 0x71E080, CActiveOccluder*, CActiveOccluder*>(first, second);
}

bool COcclusion::IsPositionOccluded(CVector vecPos, float fRadius)
{
    //return plugin::CallAndReturn<bool, 0x71E080, CVector, float>(vecPos, fRadius);
    if (!COcclusion::NumActiveOccluders)
        return false;

    CVector outPos;
    float screenX, screenY;
    if (!CalcScreenCoors(vecPos, &outPos, &screenX, &screenY))
        return false;

    const auto fLongEdge = std::max(screenX, screenY);
    auto fScreenRadius = fRadius * fLongEdge;
    auto fScreenDepth = outPos.z - fRadius;

    for (auto ind = 0; ind < COcclusion::NumActiveOccluders; ++ind)
    {
        auto& occluder = COcclusion::aActiveOccluders[ind];
        if (occluder.m_wDepth >= fScreenDepth
            || !occluder.IsPointWithinOcclusionArea(outPos.x, outPos.y, fScreenRadius)
            || !occluder.IsPointBehindOccluder(vecPos, fRadius))
        {
            continue;
        }

        return true;
    }

    return false;
}

void COcclusion::ProcessBeforeRendering()
{
    plugin::Call<0x7201C0>();
}

bool CActiveOccluder::IsPointWithinOcclusionArea(float fX, float fY, float fRadius)
{
    return plugin::CallMethodAndReturn<bool, 0x71E580, CActiveOccluder*, float, float, float>(this, fX, fY, fRadius);
}

bool CActiveOccluder::IsPointBehindOccluder(CVector vecPos, float fRadius)
{
    return plugin::CallMethodAndReturn<bool, 0x71FA40, CActiveOccluder*, CVector, float>(this, vecPos, fRadius);
}

void COccluder::ProcessOneOccluder(CActiveOccluder* pActiveOccluder)
{
    plugin::CallMethod<0x71E5D0, COccluder*, CActiveOccluder*>(this, pActiveOccluder);
}

void COccluder::ProcessLineSegment(int iInd1, int iInd2, CActiveOccluder* pActiveOccluder)
{
    plugin::CallMethod<0x71E130, COccluder*, int, int, CActiveOccluder*>(this, iInd1, iInd2, pActiveOccluder);
}
