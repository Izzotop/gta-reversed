#pragma once

class CLines {
public:
    static void InjectHooks();

    static void RenderLineNoClipping(float startX, float startY, float startZ, float endX, float endY, float endZ, unsigned int startColor, unsigned int endColor);
    static void ImmediateLine2D(int startX, int startY, int endX, int endY, unsigned char startR, unsigned char startG, unsigned char startB, unsigned char startA, unsigned char endR, unsigned char endG, unsigned char endB, unsigned char endA);
};
