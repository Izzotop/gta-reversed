#include "StdInc.h"
/*
Plugin-SDK (Grand Theft Auto San Andreas) source file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/

void CGeneral::InjectHooks()
{
    ReversibleHooks::Install("CGeneral", "LimitAngle", 0x53CB00, &CGeneral::LimitAngle);
    ReversibleHooks::Install("CGeneral", "LimitRadianAngle", 0x53CB50, &CGeneral::LimitRadianAngle);
    ReversibleHooks::Install("CGeneral", "GetRadianAngleBetweenPoints", 0x53CBE0, &CGeneral::GetRadianAngleBetweenPoints);
    ReversibleHooks::Install("CGeneral", "GetRandomNumberInRange_int", 0x407180, (int(*)(int, int))&CGeneral::GetRandomNumberInRange);
    ReversibleHooks::Install("CGeneral", "GetRandomNumberInRange_float", 0x41BD90, (float(*)(float, float))&CGeneral::GetRandomNumberInRange);
    ReversibleHooks::Install("CGeneral", "GetAngleBetweenPoints", 0x53CEA0, &CGeneral::GetAngleBetweenPoints);
    ReversibleHooks::Install("CGeneral", "CamShakeNoPos", 0x50A970, &CGeneral::CamShakeNoPos);
    ReversibleHooks::Install("CGeneral", "GetNodeHeadingFromVector", 0x53CDC0, &CGeneral::GetNodeHeadingFromVector);
//    ReversibleHooks::Install("CGeneral", "SolveQuadratic", 0x53CE30, &CGeneral::SolveQuadratic);
}

// Converted from cdecl float CGeneral::LimitAngle(float angle) 0x53CB00
float CGeneral::LimitAngle(float angle) {
    while (angle >= 180.0f)
        angle -= 360.0f;

    while(angle < -180.0f)
        angle += 360.0f;

    return angle;
}

// Converted from cdecl float CGeneral::LimitRadianAngle(float angle) 0x53CB50
float CGeneral::LimitRadianAngle(float angle) {
    angle = clamp(angle, -25.0F, 25.0F);

    while (angle >= PI)
        angle -= TWO_PI;

    while (angle < -PI)
        angle += TWO_PI;

    return angle;
}

// Converted from cdecl float CGeneral::GetRadianAngleBetweenPoints(float x1,float y1,float x2,float y2) 0x53CBE0
float CGeneral::GetRadianAngleBetweenPoints(float x1, float y1, float x2, float y2) {
    const auto xDiff = x2 - x1;
    auto yDiff = y2 - y1;

    if (yDiff == 0.0F)
        yDiff = 0.0001F;

    const auto fAtan = atan2(xDiff / yDiff, 1.0F);
    if (xDiff <= 0.0F)
    {
        if (yDiff <= 0.0F)
            return HALF_PI - fAtan - HALF_PI;

        return -HALF_PI - (fAtan + HALF_PI);
    }

    if (yDiff <= 0)
        return HALF_PI - (fAtan + HALF_PI);

    return HALF_PI - fAtan + HALF_PI;
}

// Converted from cdecl float CGeneral::GetATanOfXY(float x,float y) 0x53CC70
float CGeneral::GetATanOfXY(float x, float y) {
    return ((float(__cdecl *)(float, float))0x53CC70)(x, y);
}

// Converted from cdecl uchar CGeneral::GetNodeHeadingFromVector(float x,float y) 0x53CDC0
unsigned char CGeneral::GetNodeHeadingFromVector(float x, float y) {
    auto fAngle = CGeneral::GetRadianAngleBetweenPoints(x, y, 0.0F, 0.0F);
    if (fAngle < 0.0F)
        fAngle += TWO_PI;

    fAngle = TWO_PI - fAngle + (PI / 8.0F);
    if (fAngle >= TWO_PI)
        fAngle -= TWO_PI;

    return floor(fAngle * (1.0F / TWO_PI) * 8.0F); // Get it into [0:7] range
}

// Converted from cdecl bool CGeneral::SolveQuadratic(float a,float b,float c,float &x1,float &x2) 0x53CE30
bool CGeneral::SolveQuadratic(float a, float b, float c, float& x1, float& x2) {
    return ((bool(__cdecl *)(float, float, float, float&, float&))0x53CE30)(a, b, c, x1, x2);
}

// Converted from cdecl float CGeneral::GetAngleBetweenPoints(float x1,float y1,float x2,float y2) 0x53CEA0
float CGeneral::GetAngleBetweenPoints(float x1, float y1, float x2, float y2) {
    return RadiansToDegrees(CGeneral::GetRadianAngleBetweenPoints(x1, y1, x2, y2));
}

// Converted from cdecl uint CGeneral::GetRandomNumberInRange(int min, int max) 0x407180
int CGeneral::GetRandomNumberInRange(int min, int max) {
    const auto fRand = static_cast<float>(rand()) * RAND_MAX_RECIPROCAL;
    return min + static_cast<std::int32_t>(fRand * static_cast<float>(max - min));
}

// Converted from cdecl float CGeneral::GetRandomNumberInRange(float min,float max) 0x41BD90
float CGeneral::GetRandomNumberInRange(float min, float max) {
    const auto fRand = static_cast<float>(rand()) * RAND_MAX_RECIPROCAL;
    return min + fRand * (max - min);
}

void CGeneral::CamShakeNoPos(CCamera *camera, float force)
{
    auto fCurForce = camera->m_fCamShakeForce - (CTimer::m_snTimeInMilliseconds - camera->m_nCamShakeStart) * 0.001F;
    fCurForce = clamp(fCurForce, 0.0F, 2.0F);

    if (force > fCurForce)
    {
        camera->m_fCamShakeForce = force;
        camera->m_nCamShakeStart = CTimer::m_snTimeInMilliseconds;
    }
}
