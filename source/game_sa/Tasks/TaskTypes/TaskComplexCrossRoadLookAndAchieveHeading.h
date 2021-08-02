#pragma once

#include "TaskComplex.h"

class CTaskComplexCrossRoadLookAndAchieveHeading : public CTaskComplex {
public:
    CTaskComplexCrossRoadLookAndAchieveHeading* Constructor(unsigned int durationInMs, float fTargetHeading);
};