/*
Plugin-SDK (Grand Theft Auto San Andreas) header file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Pool.h"
#include "CopPed.h"
#include "Heli.h"
#include "Building.h"
#include "CutsceneObject.h"
#include "Dummy.h"
#include "ColModel.h"
#include "Task.h"
#include "PedIntelligence.h"
#include "PtrNodeSingleLink.h"
#include "PtrNodeDoubleLink.h"
#include "EntryInfoNode.h"
#include "PedGeometryAnalyser.h"
#include "TaskSimpleSlideToCoord.h"

#ifdef GetObject
#undef GetObject
#endif

class CPools {
public:
    static CPool<CPed, CCopPed>                  *&ms_pPedPool;
    static CPool<CVehicle, CHeli>                *&ms_pVehiclePool;
    static CPool<CBuilding>                      *&ms_pBuildingPool;
    static CPool<CObject, CCutsceneObject>       *&ms_pObjectPool;
    static CPool<CDummy>                         *&ms_pDummyPool;
    static CPool<CColModel>                      *&ms_pColModelPool;
    static CPool<CTask, CTaskSimpleSlideToCoord> *&ms_pTaskPool;
    static CPool<CPedIntelligence>               *&ms_pPedIntelligencePool;
    static CPool<CPtrNodeSingleLink>             *&ms_pPtrNodeSingleLinkPool;
    static CPool<CPtrNodeDoubleLink>             *&ms_pPtrNodeDoubleLinkPool;
    static CPool<CEntryInfoNode>                 *&ms_pEntryInfoNodePool;
    static CPool<CPointRoute>                    *&ms_pPointRoutePool;

public:
    static void InjectHooks();

    // dummy function; returns "-1"
    static int CheckBuildingAtomics();
    static void CheckPoolsEmpty();
    static CObject* GetObject(int handle);
    static int GetObjectRef(CObject* object);
    static CPed* GetPed(int handle);
    static int GetPedRef(CPed* ped);
    static CVehicle* GetVehicle(int handle);
    static int GetVehicleRef(CVehicle* vehicle);
    static void Initialise();
    // returns "true"
    static bool Load();
    // returns "true"
    static bool LoadObjectPool();
    // returns "true"
    static bool LoadPedPool();
    // returns "true"
    static bool LoadVehiclePool();
    static void MakeSureSlotInObjectPoolIsEmpty(int slot);
    // returns "true"
    static bool Save();
    // returns "true"
    static bool SaveObjectPool();
    // returns "true"
    static bool SavePedPool();
    // returns "true"
    static bool SaveVehiclePool();
    static void ShutDown();
};
