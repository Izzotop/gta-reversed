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

    ReversibleHooks::Install("COccluder", "ProcessOneOccluder", 0x71E5D0, &COccluder::ProcessOneOccluder);
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
    //return plugin::CallAndReturn<bool, 0x71E080, CActiveOccluder*, CActiveOccluder*>(first, second);
    if (!first->m_cLinesCount)
        return second->m_cLinesCount == 0;

    if (first->m_cLinesCount <= 0)
        return true;

    auto* pNextLine = first->m_aLines;
    auto iLineInd = 0;
    if (second->m_cLinesCount <= 0)
        return true;

    while (iLineInd < first->m_cLinesCount)
    {
        if (second->m_cLinesCount > 0)
            break;

        ++iLineInd;
        ++pNextLine;
    }

    if (iLineInd >= first->m_cLinesCount)
        return true;


}

bool COcclusion::IsPositionOccluded(CVector vecPos, float fRadius)
{
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

bool COccluder::ProcessOneOccluder(CActiveOccluder* pActiveOccluder)
{
    pActiveOccluder->m_cLinesCount = 0;
    auto vecPos = CVector(m_fMidX * 0.25F, m_fMidY * 0.25F, m_fMidZ * 0.25F);
    float temp1, temp2;

    if (!CalcScreenCoors(vecPos, &COcclusion::gCenterOnScreen, &temp1, &temp2) || COcclusion::gCenterOnScreen.z < -150.0F || COcclusion::gCenterOnScreen.z > 300.0F)
        return false;

    auto fMagnitude = CVector(m_fWidth / 4.0F, m_fLength / 4.0F, m_fHeight / 4.0F).Magnitude();
    pActiveOccluder->m_wDepth = COcclusion::gCenterOnScreen.z - fMagnitude;

    auto matRotX = CMatrix();
    auto matRotY = CMatrix();
    auto matRotZ = CMatrix();;
    auto matTransform = CMatrix();

    matRotX.SetRotateX(m_cRotZ / 40.0F); //TODO: Check if the fields in the model aren't in the wrong order
    matRotY.SetRotateY(m_cRotY / 40.0F);
    matRotZ.SetRotateZ(m_cRotX / 40.0F);
    matTransform = (matRotY * matRotX) * matRotZ;

    COcclusion::gMinXInOccluder = 999999.88F;
    COcclusion::gMinYInOccluder = 999999.88F;
    COcclusion::gMaxXInOccluder = -999999.88F;
    COcclusion::gMaxYInOccluder = -999999.88F;

    if (   m_fLength * 0.25F != 0.0F
        && m_fWidth  * 0.25F != 0.0F
        && m_fHeight * 0.25F != 0.0F) {
        auto vecWidth = CVector(m_fWidth / 8.0F, 0.0F, 0.0F);
        auto vecTransWidth = matTransform * vecWidth;

        auto vecLength = CVector(0.0F, m_fLength / 8.0F, 0.0F);
        auto vecTransLength = matTransform * vecLength;

        auto vecHeight = CVector(0.0F, 0.0F, m_fHeight / 8.0F);
        auto vecTransHeight = matTransform * vecHeight;

        CVector aVecArr[6]{
            vecTransLength, -vecTransLength,
            vecTransWidth, -vecTransWidth,
            vecTransHeight, -vecTransHeight
        };

        const auto& vecCamPos = TheCamera.GetPosition();
        bool abOnScreen[6]{
            DotProduct((vecPos + aVecArr[0] - vecCamPos), aVecArr[0]) < 0.0F,
            DotProduct((vecPos + aVecArr[1] - vecCamPos), aVecArr[1]) < 0.0F,
            DotProduct((vecPos + aVecArr[2] - vecCamPos), aVecArr[2]) < 0.0F,
            DotProduct((vecPos + aVecArr[3] - vecCamPos), aVecArr[3]) < 0.0F,
            DotProduct((vecPos + aVecArr[4] - vecCamPos), aVecArr[4]) < 0.0F,
            DotProduct((vecPos + aVecArr[5] - vecCamPos), aVecArr[5]) < 0.0F
        };

        COcclusion::gOccluderCoors[0] = vecPos + aVecArr[0] + aVecArr[2] + aVecArr[4];
        COcclusion::gOccluderCoors[1] = vecPos + aVecArr[1] + aVecArr[2] + aVecArr[4];
        COcclusion::gOccluderCoors[2] = vecPos + aVecArr[0] + aVecArr[3] + aVecArr[4];
        COcclusion::gOccluderCoors[3] = vecPos + aVecArr[1] + aVecArr[3] + aVecArr[4];
        COcclusion::gOccluderCoors[4] = vecPos + aVecArr[0] + aVecArr[2] + aVecArr[5];
        COcclusion::gOccluderCoors[5] = vecPos + aVecArr[1] + aVecArr[2] + aVecArr[5];
        COcclusion::gOccluderCoors[6] = vecPos + aVecArr[0] + aVecArr[3] + aVecArr[5];
        COcclusion::gOccluderCoors[7] = vecPos + aVecArr[1] + aVecArr[3] + aVecArr[5];

        for (auto i = 0; i < 8; ++i) {
            COcclusion::gOccluderCoorsValid[i] = CalcScreenCoors(COcclusion::gOccluderCoors[i], &COcclusion::gOccluderCoorsOnScreen[i], &temp1, &temp2);
        }

        if (   (abOnScreen[0] == abOnScreen[2] || !ProcessLineSegment(0, 4, pActiveOccluder))
            && (abOnScreen[0] == abOnScreen[3] || !ProcessLineSegment(2, 6, pActiveOccluder))
            && (abOnScreen[0] == abOnScreen[4] || !ProcessLineSegment(0, 2, pActiveOccluder))
            && (abOnScreen[0] == abOnScreen[5] || !ProcessLineSegment(4, 6, pActiveOccluder))
            && (abOnScreen[1] == abOnScreen[2] || !ProcessLineSegment(1, 5, pActiveOccluder))
            && (abOnScreen[1] == abOnScreen[3] || !ProcessLineSegment(3, 7, pActiveOccluder))
            && (abOnScreen[1] == abOnScreen[4] || !ProcessLineSegment(1, 3, pActiveOccluder))
            && (abOnScreen[1] == abOnScreen[5] || !ProcessLineSegment(5, 7, pActiveOccluder))
            && (abOnScreen[2] == abOnScreen[4] || !ProcessLineSegment(0, 1, pActiveOccluder))
            && (abOnScreen[3] == abOnScreen[4] || !ProcessLineSegment(2, 3, pActiveOccluder))
            && (abOnScreen[3] == abOnScreen[5] || !ProcessLineSegment(6, 7, pActiveOccluder))
            && (abOnScreen[2] == abOnScreen[5] || !ProcessLineSegment(4, 5, pActiveOccluder))
            && RsGlobal.maximumWidth * 0.15F <= COcclusion::gMaxXInOccluder - COcclusion::gMinXInOccluder
            && RsGlobal.maximumHeight * 0.1F <= COcclusion::gMaxYInOccluder - COcclusion::gMinYInOccluder) {

            pActiveOccluder->m_cUnkn = 0;
            for (auto i = 0; i < 6; ++i) {
                if (abOnScreen[i]) {
                    auto vecNormalised = CVector(aVecArr[i]);
                    vecNormalised.Normalise();
                    auto vecScreenPos = vecPos + aVecArr[i];

                    pActiveOccluder->m_aVectors[pActiveOccluder->m_cUnkn] = vecNormalised;
                    pActiveOccluder->m_fRadiuses[pActiveOccluder->m_cUnkn] = DotProduct(vecScreenPos, vecNormalised);
                    ++pActiveOccluder->m_cUnkn;
                }
            }

            return true;
        }

        return false;
    }

    CVector vec1, vec2;
    if (m_fLength * 0.25F == 0.0F) {
        auto vecWidth = CVector(m_fWidth / 8.0F, 0.0F, 0.0F);
        vec1 = matTransform * vecWidth;

        auto vecHeight = CVector(0.0F, 0.0F, m_fHeight / 8.0F);
        vec2 = matTransform * vecHeight;
    }
    else if (m_fWidth * 0.25F == 0.0F) {
        auto vecLength = CVector(0.0F, m_fLength / 8.0F, 0.0F);
        vec1 = matTransform * vecLength;

        auto vecHeight = CVector(0.0F, 0.0F, m_fHeight / 8.0F);
        vec2 = matTransform * vecHeight;
    }
    else if (m_fHeight * 0.25F == 0.0F) {
        auto vecLength = CVector(0.0F, m_fLength / 8.0F, 0.0F);
        vec1 = matTransform * vecLength;

        auto vecWidth = CVector(m_fWidth / 8.0F, 0.0F, 0.0F);
        vec2 = matTransform * vecWidth;
    }

    COcclusion::gOccluderCoors[0] = vecPos + vec1 + vec2;
    COcclusion::gOccluderCoors[1] = vecPos - vec1 + vec2;
    COcclusion::gOccluderCoors[2] = vecPos - vec1 - vec2;
    COcclusion::gOccluderCoors[3] = vecPos + vec1 - vec2;

    for (auto i = 0; i < 4; ++i) {
        COcclusion::gOccluderCoorsValid[i] = CalcScreenCoors(COcclusion::gOccluderCoors[i], &COcclusion::gOccluderCoorsOnScreen[i], &temp1, &temp2);
    }

    if (   !ProcessLineSegment(0, 1, pActiveOccluder)
        && !ProcessLineSegment(1, 2, pActiveOccluder)
        && !ProcessLineSegment(2, 3, pActiveOccluder)
        && !ProcessLineSegment(3, 0, pActiveOccluder)
        && RsGlobal.maximumWidth  * 0.1  <= COcclusion::gMaxXInOccluder - COcclusion::gMinXInOccluder
        && RsGlobal.maximumHeight * 0.07 <= COcclusion::gMaxYInOccluder - COcclusion::gMinYInOccluder){

        auto vecCross = CrossProduct(vec1, vec2);
        vecCross.Normalise();

        pActiveOccluder->m_aVectors[0] = vecCross;
        pActiveOccluder->m_fRadiuses[0] = DotProduct(vecCross, vecPos);
        pActiveOccluder->m_cUnkn = 1;

        return true;
    }

    return false;
}

bool COccluder::ProcessLineSegment(int iInd1, int iInd2, CActiveOccluder* pActiveOccluder)
{
    return plugin::CallMethodAndReturn<bool, 0x71E130, COccluder*, int, int, CActiveOccluder*>(this, iInd1, iInd2, pActiveOccluder);
}
