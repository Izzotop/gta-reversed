#pragma once

class CMaths {
public:
    static float* ms_SinTable;

public:
    static void InjectHooks();

    static void InitMathsTables();
};
