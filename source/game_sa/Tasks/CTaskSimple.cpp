/*
Plugin-SDK (Grand Theft Auto San Andreas) source file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

// 0x61A390
CTaskSimple::CTaskSimple() {
    m_pParentTask = nullptr;
}

// 0x61A3A0
CTaskSimple::~CTaskSimple() {
    // nothing here
}

// 0x43E300
CTask* CTaskSimple::GetSubTask() {
    return nullptr;
}

// 0x43E310
bool CTaskSimple::IsSimple() {
    return true;
}

// 0x43E320
bool CTaskSimple::SetPedPosition(CPed* ped) {
    return false;
}

void CTaskSimple::InjectHooks() {
    ReversibleHooks::Install("CTaskSimple", "CTaskSimple", 0x61A390, &CTaskSimple::Constructor);
    ReversibleHooks::Install("CTaskSimple", "~CTaskSimple", 0x61A3A0, &CTaskSimple::Destructor);
    ReversibleHooks::Install("CTaskSimple", "GetSubTask", 0x43E300, &CTaskSimple::GetSubTask_Reversed);
    ReversibleHooks::Install("CTaskSimple", "IsSimple", 0x43E310, &CTaskSimple::IsSimple_Reversed);
    ReversibleHooks::Install("CTaskSimple", "SetPedPosition", 0x43E320, &CTaskSimple::SetPedPosition_Reversed);
}

CTaskSimple* CTaskSimple::Constructor() {
    this->CTaskSimple::CTaskSimple();
    return this;
}

CTaskSimple* CTaskSimple::Destructor() {
    this->CTaskSimple::~CTaskSimple();
    return this;
}

CTask* CTaskSimple::GetSubTask_Reversed() {
    return CTaskSimple::GetSubTask();
}

bool CTaskSimple::IsSimple_Reversed() {
    return CTaskSimple::IsSimple();
}

bool CTaskSimple::SetPedPosition_Reversed(CPed* ped) {
    return CTaskSimple::SetPedPosition(ped);
}
