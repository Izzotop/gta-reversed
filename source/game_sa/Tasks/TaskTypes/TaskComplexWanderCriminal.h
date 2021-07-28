#pragma once
#include "TaskComplexWander.h"

class CTaskComplexWanderCriminal : public CTaskComplexWander
{
public:
    CTaskComplexWanderCriminal* Constructor(int MoveState, unsigned char Dir, bool bWanderSensibly);
};