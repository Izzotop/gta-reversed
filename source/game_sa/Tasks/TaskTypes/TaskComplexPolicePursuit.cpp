#include "StdInc.h"

#include "TaskComplexPolicePursuit.h"

CTaskComplexPolicePursuit* CTaskComplexPolicePursuit::Constructor()
{
    return plugin::CallMethodAndReturn <CTaskComplexPolicePursuit*, 0x68BA70, CTaskComplexPolicePursuit*>(this);
}