#include "StdInc.h"

#include "CLines.h"

void CLines::InjectHooks() {
    //ReversibleHooks::Install("CLines", "RenderLineNoClipping")
}

void CLines::RenderLineNoClipping(float startX, float startY, float startZ, float endX, float endY, float endZ, unsigned int startColor, unsigned int endColor)
{
    plugin::Call<0x6FF460, float, float, float, float, float, float, unsigned int, unsigned int>(startX, startY, startZ, endX, endY, endZ, startColor, endColor);
}

void CLines::ImmediateLine2D(int startX, int startY, int endX, int endY, unsigned char startR, unsigned char startG, unsigned char startB, unsigned char startA, unsigned char endR, unsigned char endG, unsigned char endB, unsigned char endA) {
    plugin::Call<0x6FF790, int, int, int, int, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char>(startX, startY, endX, endY, startR, startG, startB, startA, endR, endG, endB, endA);
}
