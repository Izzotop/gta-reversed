/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CPed.h"

class CPedGroup;

const std::int32_t TOTAL_PED_GROUP_MEMBERS = 8;
// -1 because every ped group has a leader, and the leader cannot be a follower
const std::int32_t TOTAL_PED_GROUP_FOLLOWERS = TOTAL_PED_GROUP_MEMBERS - 1;

class CPedGroupMembership {
    PLUGIN_NO_DEFAULT_CONSTRUCTION(CPedGroupMembership)

public:
    CPedGroup *m_pPedGroup;
    CPed *m_apMembers[TOTAL_PED_GROUP_MEMBERS]; //!< m_apMembers[7] is a leader

     static float const &ms_fMaxSeparation;
     static float const &ms_fPlayerGroupMaxSeparation;

     void AddFollower(CPed *ped);
     void AddMember(CPed *member, int memberID);
     void AppointNewLeader();
     int CountMembers();
     int CountMembersExcludingLeader();
     void Flush();
    //! copy constructor subfunction
     void From(CPedGroupMembership const *obj);
     CPed *GetLeader();
     CPed *GetMember(int memberId);
     bool IsFollower(CPed const *ped);
     bool IsLeader(CPed const *ped);
     bool IsMember(CPed const *ped);
     void Process();
     void RemoveAllFollowers(bool bCreatedByGameOnly);
     void RemoveMember(int memberID);
     char RemoveNFollowers(int count);
     void SetLeader(CPed *ped);

     static signed int GetObjectForPedToHold();
};

VALIDATE_SIZE(CPedGroupMembership, 0x24);

//#include "meta/meta.CPedGroupMembership.h"
