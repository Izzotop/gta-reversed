/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Ped.h"
#include "PedGroupMembership.h"

class CPedList {
public:
    int m_nCount;
    CPed* m_apPeds[30];

public:
    void BuildListFromGroup_NoLeader(CPedGroupMembership* pedGroupMemberShip);
    void BuildListFromGroup_NotInCar_NoLeader(CPedGroupMembership* pedGroupMembership);
    void BuildListOfPedsOfPedType(int pedtype);
    void Empty();
    void ExtractPedsWithGuns(CPedList* pedlist);
    void FillUpHoles();
    void RemovePedsAttackingPedType(int pedtype);
    void RemovePedsThatDontListenToPlayer();
};

VALIDATE_SIZE(CPedList, 0x7C);
