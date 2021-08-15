/*
Plugin-SDK (Grand Theft Auto San Andreas) source file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

#include "CCarGenerator.h"
#include "CTheCarGenerators.h"

char (&CFileLoader::ms_line)[512] = *reinterpret_cast<char (*)[512]>(0xB71848);
unsigned int& gAtomicModelId = *reinterpret_cast<unsigned int*>(0xB71840);

char (&colFileReadBuffer)[32768] = *(char (*)[32768])0xBC40D8;


void CFileLoader::InjectHooks() {
    ReversibleHooks::Install("CFileLoader", "AddTexDictionaries", 0x5B3910, &CFileLoader::AddTexDictionaries);
    ReversibleHooks::Install("CFileLoader", "LoadTexDictionary", 0x5B3860, &CFileLoader::LoadTexDictionary);
    // ReversibleHooks::Install("CFileLoader", "LoadAnimatedClumpObject", 0x0, &CFileLoader::LoadAnimatedClumpObject);
    ReversibleHooks::Install("CFileLoader", "LoadAtomicFile_stream", 0x5371F0, static_cast<bool(*)(RwStream*, unsigned)>(&CFileLoader::LoadAtomicFile));
    ReversibleHooks::Install("CFileLoader", "LoadAtomicFile", 0x5B39D0, static_cast<void(*)(const char*)>(&CFileLoader::LoadAtomicFile));
    // ReversibleHooks::Install("CFileLoader", "LoadLine_0", 0x536F80, static_cast<char*(*)(FILESTREAM)>(&CFileLoader::LoadLine));
    // ReversibleHooks::Install("CFileLoader", "LoadLine_1", 0x536FE0, static_cast<char*(*)(char**, int&)>(&CFileLoader::LoadLine));
    ReversibleHooks::Install("CFileLoader", "LoadAudioZone", 0x5B4D70, &CFileLoader::LoadAudioZone);
    ReversibleHooks::Install("CFileLoader", "LoadCarGenerator_0", 0x537990, static_cast<void(*)(CFileCarGenerator*, int)>(&CFileLoader::LoadCarGenerator));
    ReversibleHooks::Install("CFileLoader", "LoadCarGenerator_1", 0x5B4740, static_cast<void(*)(const char*, int)>(&CFileLoader::LoadCarGenerator));
    // ReversibleHooks::Install("CFileLoader", "LoadCarPathNode", 0x5B4380, &CFileLoader::LoadCarPathNode);
    ReversibleHooks::Install("CFileLoader", "StartLoadClumpFile", 0x5373F0, &CFileLoader::StartLoadClumpFile);
    ReversibleHooks::Install("CFileLoader", "FinishLoadClumpFile", 0x537450, &CFileLoader::FinishLoadClumpFile);
    ReversibleHooks::Install("CFileLoader", "LoadClumpFile", 0x5B3A30, static_cast<void(*)(const char*)>(&CFileLoader::LoadClumpFile));
    ReversibleHooks::Install("CFileLoader", "LoadClumpObject", 0x5B4040, &CFileLoader::LoadClumpObject);
    // ReversibleHooks::Install("CFileLoader", "LoadCollisionFile_0", 0x538440, static_cast<bool(*)(unsigned char*, unsigned int, unsigned char)>(&CFileLoader::LoadCollisionFile));
    // ReversibleHooks::Install("CFileLoader", "LoadCollisionFile_1", 0x5B4E60, static_cast<bool(*)(const char*, unsigned char)>(&CFileLoader::LoadCollisionFile));
    // ReversibleHooks::Install("CFileLoader", "LoadCollisionFileFirstTime", 0x5B5000, &CFileLoader::LoadCollisionFileFirstTime);
    // ReversibleHooks::Install("CFileLoader", "LoadCollisionModel", 0x537580, &CFileLoader::LoadCollisionModel);
    // ReversibleHooks::Install("CFileLoader", "LoadCollisionModelVer2", 0x537EE0, &CFileLoader::LoadCollisionModelVer2);
    // ReversibleHooks::Install("CFileLoader", "LoadCollisionModelVer3", 0x537CE0, &CFileLoader::LoadCollisionModelVer3);
    // ReversibleHooks::Install("CFileLoader", "LoadCollisionModelVer4", 0x537AE0, &CFileLoader::LoadCollisionModelVer4);
    ReversibleHooks::Install("CFileLoader", "LoadCullZone", 0x5B4B40, &CFileLoader::LoadCullZone);
    ReversibleHooks::Install("CFileLoader", "LoadEntryExit", 0x5B8030, &CFileLoader::LoadEntryExit);
    // ReversibleHooks::Install("CFileLoader", "LoadGarage", 0x5B4530, &CFileLoader::LoadGarage);
    // ReversibleHooks::Install("CFileLoader", "LoadLevel", 0x5B9030, &CFileLoader::LoadLevel);
    ReversibleHooks::Install("CFileLoader", "LoadObject", 0x5B3C60, &CFileLoader::LoadObject);
    ReversibleHooks::Install("CFileLoader", "LoadObjectInstance_inst", 0x538090, static_cast<CEntity* (*)(CFileObjectInstance*, const char*)>(&CFileLoader::LoadObjectInstance));
    ReversibleHooks::Install("CFileLoader", "LoadObjectInstance_file", 0x538690, static_cast<CEntity* (*)(const char*)>(&CFileLoader::LoadObjectInstance));
    ReversibleHooks::Install("CFileLoader", "LoadOcclusionVolume", 0x5B4C80, &CFileLoader::LoadOcclusionVolume);
    ReversibleHooks::Install("CFileLoader", "LoadPathHeader", 0x5B41C0, &CFileLoader::LoadPathHeader);
    // ReversibleHooks::Install("CFileLoader", "LoadPedObject", 0x5B7420, &CFileLoader::LoadPedObject);
    // ReversibleHooks::Install("CFileLoader", "LoadPedPathNode", 0x5B41F0, &CFileLoader::LoadPedPathNode);
    // ReversibleHooks::Install("CFileLoader", "LoadPickup", 0x5B47B0, &CFileLoader::LoadPickup);
    ReversibleHooks::Install("CFileLoader", "LoadStuntJump", 0x5B45D0, &CFileLoader::LoadStuntJump);
    ReversibleHooks::Install("CFileLoader", "LoadTXDParent", 0x5B75E0, &CFileLoader::LoadTXDParent);
    ReversibleHooks::Install("CFileLoader", "LoadTimeCyclesModifier", 0x5B81D0, &CFileLoader::LoadTimeCyclesModifier);
    ReversibleHooks::Install("CFileLoader", "LoadTimeObject", 0x5B3DE0, &CFileLoader::LoadTimeObject);
    // ReversibleHooks::Install("CFileLoader", "LoadVehicleObject", 0x5B6F30, &CFileLoader::LoadVehicleObject);
    ReversibleHooks::Install("CFileLoader", "LoadWeaponObject", 0x5B3FB0, &CFileLoader::LoadWeaponObject);
    ReversibleHooks::Install("CFileLoader", "LoadZone", 0x5B4AB0, &CFileLoader::LoadZone);
    // ReversibleHooks::Install("CFileLoader", "LoadScene", 0x5B8700, &CFileLoader::LoadScene);
    // ReversibleHooks::Install("CFileLoader", "LoadObjectTypes", 0x5B8400, &CFileLoader::LoadObjectTypes);
    ReversibleHooks::Install("CFileLoader", "FindRelatedModelInfoCB", 0x5B3930, &CFileLoader::FindRelatedModelInfoCB);
    ReversibleHooks::Install("CFileLoader", "SetRelatedModelInfoCB", 0x537150, &CFileLoader::SetRelatedModelInfoCB);
}

// copy textures from dictionary to baseDictionary
// 0x5B3910
void CFileLoader::AddTexDictionaries(RwTexDictionary* dictionary, RwTexDictionary* baseDictionary) {
    RwTexDictionaryForAllTextures(baseDictionary, AddTextureCB, dictionary);
}

// save txd to file
// unused
// 0x5B38C0
void CFileLoader::SaveTexDictionary(RwTexDictionary* dictionary, const char* filename) {
    RwStream* stream = RwStreamOpen(rwSTREAMFILENAME, rwSTREAMWRITE, filename);
    if (stream) {
        RwTexDictionaryStreamWrite(dictionary, stream);
        RwStreamClose(stream, nullptr);
    }
}

// load txd from file
// 0x5B3860
RwTexDictionary* CFileLoader::LoadTexDictionary(const char* filename) {
    RwStream* stream = RwStreamOpen(rwSTREAMFILENAME, rwSTREAMREAD, filename);
    if (stream) {
        bool chunk = RwStreamFindChunk(stream, rwID_TEXDICTIONARY, nullptr, nullptr);
        if (chunk) {
            RwTexDictionary* txd = RwTexDictionaryGtaStreamRead(stream);
            RwStreamClose(stream, nullptr);
            if (txd) {
                return txd;
            }
        }
        RwStreamClose(stream, nullptr);
    }
    return RwTexDictionaryCreate();
}

// 0x5B40C0
int CFileLoader::LoadAnimatedClumpObject(const char* line) {
    return plugin::CallAndReturn<int, 0x5B40C0, const char*>(line);
}

// 0x5371F0
bool CFileLoader::LoadAtomicFile(RwStream* stream, unsigned int modelId) {
    auto pAtomicModelInfo = CModelInfo::ms_modelInfoPtrs[modelId]->AsAtomicModelInfoPtr();
    bool bUseCommonVehicleTexDictionary = false;
    if (pAtomicModelInfo && pAtomicModelInfo->bUseCommonVehicleDictionary) {
        bUseCommonVehicleTexDictionary = true;
        CVehicleModelInfo::UseCommonVehicleTexDicationary();
    }

    if (RwStreamFindChunk(stream, rwID_CLUMP, nullptr, nullptr)) {
        RpClump* pReadClump = RpClumpStreamRead(stream);
        if (!pReadClump) {
            if (bUseCommonVehicleTexDictionary) {
                CVehicleModelInfo::StopUsingCommonVehicleTexDicationary();
            }
            return false;
        }
        gAtomicModelId = modelId;
        RpClumpForAllAtomics(pReadClump, (RpAtomicCallBack)SetRelatedModelInfoCB, pReadClump);
        RpClumpDestroy(pReadClump);
    }

    if (!pAtomicModelInfo->m_pRwObject)
        return false;

    if (bUseCommonVehicleTexDictionary)
        CVehicleModelInfo::StopUsingCommonVehicleTexDicationary();

    return true;
}

// 0x5B39D0
void CFileLoader::LoadAtomicFile(const char* filename) {
    RwStream* stream = RwStreamOpen(rwSTREAMFILENAME, rwSTREAMREAD, filename);
    if (RwStreamFindChunk(stream, rwID_CLUMP, nullptr, nullptr)) {
        RpClump* clump = RpClumpStreamRead(stream);
        if (clump) {
            RpClumpForAllAtomics(clump, FindRelatedModelInfoCB, clump);
            RpClumpDestroy(clump);
        }
    }
    RwStreamClose(stream, nullptr);
}

// unused
// 0x537060
RpClump* CFileLoader::LoadAtomicFile2Return(const char* filename) {
    RpClump* clump = nullptr;
    RwStream* stream = RwStreamOpen(rwSTREAMFILENAME, rwSTREAMREAD, filename);
    if (RwStreamFindChunk(stream, rwID_CLUMP, nullptr, nullptr))
        clump = RpClumpStreamRead(stream);

    RwStreamClose(stream, nullptr);
    return clump;
}

// 0x536F80
char* CFileLoader::LoadLine(FILESTREAM file) {
    return plugin::CallAndReturn<char*, 0x536F80, FILESTREAM>(file);

    // fails
    assert(file != nullptr);

    if (CFileMgr::ReadLine(file, ms_line, 512) == false)
        return nullptr;

    for (int i = 0; ms_line[i] != '\0'; i++)
        if (ms_line[i] < ' ' || ms_line[i] == ',')
            ms_line[i] = ' ';

        char* line;
        for (line = ms_line; *line <= ' ' && *line != '\0'; line++) {
            //
        }

        return line;
}

// 0x536FE0
char* CFileLoader::LoadLine(char** outLine, int& outSize) {
    return plugin::CallAndReturn<char*, 0x536FE0, char**, int&>(outLine, outSize);;
}

// IPL -> AUZO
// 0x5B4D70
void CFileLoader::LoadAudioZone(const char* line) {
    char    name[16];
    int32_t id;
    int32_t enabled;
    float   x1, y1, z1;
    float   x2, y2, z2;
    float   radius;

    int iNumRead = sscanf(line, "%s %d %d %f %f %f %f %f %f", name, &id, &enabled, &x1, &y1, &z1, &x2, &y2, &z2);
    if (iNumRead == 9) {
        CAudioZones::RegisterAudioBox(name, id, enabled != 0, x1, y1, z1, x2, y2, z2);
        return;
    }

    sscanf(line, "%s %d %d %f %f %f %f", name, &id, &enabled, &x1, &y1, &z1, &radius);
    CAudioZones::RegisterAudioSphere(name, id, enabled != 0, x1, y1, z1, radius);
}

// unused?
// 0x0
void CFileLoader::LoadBoundingBox(unsigned char* data, CBoundingBox& outBoundBox) {

}

// 0x537990
void CFileLoader::LoadCarGenerator(CFileCarGenerator* carGen, int iplId) {
    auto index = CTheCarGenerators::CreateCarGenerator(
        carGen->m_vecPosn,
        RWRAD2DEG(carGen->m_fAngle),
        carGen->m_nModelId,
        carGen->m_nPrimaryColor,
        carGen->m_nSecondaryColor,
        carGen->m_bForceSpawn,
        carGen->m_nAlarmChance,
        carGen->m_nDoorLockChance,
        carGen->m_nMinDelay,
        carGen->m_nMaxDelay,
        iplId,
        carGen->m_bIgnorePopulationLimit
    );
    if (index >= 0)
        CTheCarGenerators::Get(index)->SwitchOn();
}

// IPL -> CARS
// 0x5B4740
void CFileLoader::LoadCarGenerator(const char* line, int iplId) {
    CFileCarGenerator carGen;
    auto iNumRead = sscanf(
        line,
        "%f %f %f %f %d %d %d %d %d %d %d %d",
        &carGen.m_vecPosn.x,
        &carGen.m_vecPosn.y,
        &carGen.m_vecPosn.z,
        &carGen.m_fAngle,
        &carGen.m_nModelId,
        &carGen.m_nPrimaryColor,
        &carGen.m_nSecondaryColor,
        &carGen.m_nFlags,
        &carGen.m_nAlarmChance,
        &carGen.m_nDoorLockChance,
        &carGen.m_nMinDelay,
        &carGen.m_nMaxDelay
    );
    if (iNumRead == 12)
        LoadCarGenerator(&carGen, iplId);
}

// 0x5B4380
void CFileLoader::LoadCarPathNode(const char* line, int objModelIndex, int pathEntryIndex, bool a4) {
    plugin::Call<0x5B4380, const char*, int, int, bool>(line, objModelIndex, pathEntryIndex, a4);
}

// 0x5373F0
bool CFileLoader::StartLoadClumpFile(RwStream* stream, unsigned int modelIndex) {
    auto chunk = RwStreamFindChunk(stream, rwID_CLUMP, nullptr, nullptr);
    if (!chunk) {
        return false;
    }

    CBaseModelInfo* modelInfo = CModelInfo::GetModelInfo(modelIndex);
    bool isVehicle = modelInfo->GetModelType() == MODEL_INFO_VEHICLE;

    if (isVehicle)
        CVehicleModelInfo::UseCommonVehicleTexDicationary();

    auto clumpReaded = RpClumpGtaStreamRead1(stream);

    if (isVehicle)
        CVehicleModelInfo::StopUsingCommonVehicleTexDicationary();

    return clumpReaded;
}

// 0x537450
bool CFileLoader::FinishLoadClumpFile(RwStream* stream, unsigned int modelIndex) {
    auto modelInfo = static_cast<CClumpModelInfo*>(CModelInfo::ms_modelInfoPtrs[modelIndex]);
    bool isVehicle = modelInfo->GetModelType() == MODEL_INFO_VEHICLE;

    if (isVehicle)
        CVehicleModelInfo::UseCommonVehicleTexDicationary();

    RpClump* clump = RpClumpGtaStreamRead2(stream);

    if (isVehicle)
        CVehicleModelInfo::StopUsingCommonVehicleTexDicationary();

    if (!clump)
        return false;

    modelInfo->SetClump(clump);
    return true;
}

// 0x5372D0
bool CFileLoader::LoadClumpFile(RwStream* stream, unsigned int modelIndex) {
    return plugin::CallAndReturn<bool, 0x5372D0, RwStream*, unsigned int>(stream, modelIndex);

    // fails, hook not needed
    auto modelInfo = static_cast<CVehicleModelInfo*>(CModelInfo::ms_modelInfoPtrs[modelIndex]);
    bool isVehicle = modelInfo->GetModelType() == MODEL_INFO_VEHICLE;

    if ((modelInfo->m_nFlags & 0x200) != 0) { // todo: m_nFlags & 0x200
        RpClump* parentClump = RpClumpCreate();
        RwFrame* parentFrame = RwFrameCreate();
        parentClump->object.parent = parentFrame;
        if (!RwStreamFindChunk(stream, rwID_CLUMP, nullptr, nullptr)) {
            modelInfo->SetClump(parentClump);
            return true;
        }

        while (true) {
            RpClump* childClump = RpClumpStreamRead(stream);
            if (!childClump)
                return false;

            RwFrame* childFrame = _rwFrameCloneAndLinkClones(static_cast<RwFrame*>(childClump->object.parent));
            RwFrameAddChild(parentFrame, childFrame);
            RpClumpForAllAtomics(childClump, CloneAtomicToClumpCB, parentClump);
            RpClumpDestroy(childClump);

            if (!RwStreamFindChunk(stream, rwID_CLUMP, nullptr, nullptr)) {
                modelInfo->SetClump(parentClump);
                return true;
            }
        }
    }

    if (!RwStreamFindChunk(stream, rwID_CLUMP, nullptr, nullptr))
        return false;

    if (isVehicle) {
        CCollisionPlugin::SetModelInfo(modelInfo);
        CVehicleModelInfo::UseCommonVehicleTexDicationary();
    }

    RpClump* clump = RpClumpStreamRead(stream);

    if (isVehicle) {
        CCollisionPlugin::SetModelInfo(nullptr);
        CVehicleModelInfo::StopUsingCommonVehicleTexDicationary();
    }

    if (!clump)
        return false;

    modelInfo->SetClump(clump);

    if (modelIndex == MODEL_JOURNEY)
        modelInfo->m_nNumDoors = 2;

    return true;
}

// 0x5B3A30
void CFileLoader::LoadClumpFile(const char* filename) {
    RwStream* stream = RwStreamOpen(rwSTREAMFILENAME, rwSTREAMREAD, filename);
    while (RwStreamFindChunk(stream, rwID_CLUMP, nullptr, nullptr)) {
        RpClump* clump = RpClumpStreamRead(stream);
        if (clump) {
            const char* nodeName = GetFrameNodeName(RpClumpGetFrame(clump));
            auto modelInfo = static_cast<CClumpModelInfo*>(CModelInfo::GetModelInfo(nodeName, nullptr));
            if (modelInfo)
                modelInfo->SetClump(clump);
            else
                RpClumpDestroy(clump);
        }
    }
    RwStreamClose(stream, nullptr);
}

// 0x5B4040
int CFileLoader::LoadClumpObject(const char* line) {
    char    modelName[24];
    char    texName[24];
    int32_t objId = MODEL_INVALID;

    auto iNumRead = sscanf(line, "%d %s %s", &objId, modelName, texName);
    if (iNumRead != 3)
        return MODEL_INVALID;

    auto modelInfo = static_cast<CVehicleModelInfo*>(CModelInfo::AddClumpModel(objId));
    modelInfo->SetModelName(modelName);
    modelInfo->SetTexDictionary(texName);
    modelInfo->SetColModel(&CTempColModels::ms_colModelBBox, false);
    return objId;
}

// 0x538440
bool CFileLoader::LoadCollisionFile(unsigned char* data, unsigned int dataSize, unsigned char colId) {
    return plugin::CallAndReturn<bool, 0x538440, unsigned char*, unsigned int, unsigned char>(data, dataSize, colId);
}

// 0x5B4E60
bool CFileLoader::LoadCollisionFile(const char* filename, unsigned char colId) {
    return plugin::CallAndReturn<bool, 0x5B4E60, const char*, unsigned char>(filename, colId);
}

// 0x5B5000
bool CFileLoader::LoadCollisionFileFirstTime(unsigned char* data, unsigned int dataSize, unsigned char colId) {
    return plugin::CallAndReturn<bool, 0x5B5000, unsigned char*, unsigned int, unsigned char>(data, dataSize, colId);
}

// 0x537580
void CFileLoader::LoadCollisionModel(unsigned char* data, CColModel& outColModel) {
    plugin::Call<0x537580, unsigned char*, CColModel&>(data, outColModel);
}

// 0x537EE0
void CFileLoader::LoadCollisionModelVer2(unsigned char* data, unsigned int dataSize, CColModel& outColModel, const char* modelName) {
    plugin::Call<0x537EE0, unsigned char*, unsigned int, CColModel&, const char*>(data, dataSize, outColModel, modelName);
}

// 0x537CE0
void CFileLoader::LoadCollisionModelVer3(unsigned char* data, unsigned int dataSize, CColModel& outColModel, const char* modelName) {
    plugin::Call<0x537CE0, unsigned char*, unsigned int, CColModel&, const char*>(data, dataSize, outColModel, modelName);
}

// 0x537AE0
void CFileLoader::LoadCollisionModelVer4(unsigned char* data, unsigned int dataSize, CColModel& outColModel, const char* modelName) {
    plugin::Call<0x537AE0, unsigned char*, unsigned int, CColModel&, const char*>(data, dataSize, outColModel, modelName);
}

// 0x5B3C60
int CFileLoader::LoadObject(const char* line) {
    int32_t  modelId;
    char     modelName[24];
    char     texName[24];
    float    fDrawDist;
    uint32_t nFlags;

    auto iNumRead = sscanf(line, "%d %s %s %f %d", &modelId, modelName, texName, &fDrawDist, &nFlags);
    if (iNumRead != 5 || fDrawDist < 4.0f)
    {
        int objType;
        float fDrawDist2_unused, fDrawDist3_unused;
        iNumRead = sscanf((char*)line, "%d %s %s %d", &modelId, modelName, texName, &objType);
        if (iNumRead != 4)
            return -1;

        switch (objType)
        {
        case 1:
            sscanf(line, "%d %s %s %d %f %d", &modelId, modelName, texName, &objType, &fDrawDist, &nFlags);
            break;
        case 2:
            sscanf(line, "%d %s %s %d %f %f %d", &modelId, modelName, texName, &objType, &fDrawDist, &fDrawDist2_unused, &nFlags);
            break;
        case 3:
            sscanf(line, "%d %s %s %d %f %f %f %d", &modelId, modelName, texName, &objType, &fDrawDist, &fDrawDist2_unused, &fDrawDist3_unused, &nFlags);
            break;
        }
    }

    sItemDefinitionFlags flags(nFlags);
    CAtomicModelInfo* pModelInfo;
    if (flags.bIsDamageable)
        pModelInfo = CModelInfo::AddDamageAtomicModel(modelId);
    else
        pModelInfo = CModelInfo::AddAtomicModel(modelId);

    pModelInfo->m_fDrawDistance = fDrawDist;
    pModelInfo->SetModelName(modelName);
    pModelInfo->SetTexDictionary(texName);
    SetAtomicModelInfoFlags(pModelInfo, nFlags);
    return modelId;
}

// 0x5B7670
void CFileLoader::Load2dEffect(const char* line) {
    plugin::Call<0x5B7670, const char*>(line);
}

// 0x538090
CEntity* CFileLoader::LoadObjectInstance(CFileObjectInstance* objInstance, const char* modelName) {
    auto* pInfo = CModelInfo::GetModelInfo(objInstance->m_nModelId);
    if (!pInfo)
        return nullptr;

    CEntity* pNewEntity = nullptr;
    if (pInfo->m_nObjectInfoIndex == -1)
    {
        if (pInfo->GetModelType() == ModelInfoType::MODEL_INFO_CLUMP && pInfo->bHasAnimBlend)
            pNewEntity = new CAnimatedBuilding();
        else
            pNewEntity = new CBuilding();

        pNewEntity->SetModelIndexNoCreate(objInstance->m_nModelId);
        if (pInfo->bDontCastShadowsOn)
            pNewEntity->m_bDontCastShadowsOn = true;

        if (pInfo->m_fDrawDistance < 2.0F)
            pNewEntity->m_bIsVisible = false;
    }
    else
    {
        pNewEntity = new CDummyObject();
        pNewEntity->SetModelIndexNoCreate(objInstance->m_nModelId);
        if (IsGlassModel(pNewEntity) && !CModelInfo::GetModelInfo(pNewEntity->m_nModelIndex)->IsGlassType2())
            pNewEntity->m_bIsVisible = false;
    }

    if (fabs(objInstance->m_qRotation.imag.x) > 0.05F
        || fabs(objInstance->m_qRotation.imag.y) > 0.05F
        || (objInstance->m_bDontStream && objInstance->m_qRotation.imag.x != 0.0f && objInstance->m_qRotation.imag.y != 0.0f))
    {
        objInstance->m_qRotation.imag = -objInstance->m_qRotation.imag;
        pNewEntity->AllocateStaticMatrix();

        auto tempQuat = objInstance->m_qRotation;
        pNewEntity->GetMatrix().SetRotate(tempQuat);
    }
    else
    {
        const auto fMult = objInstance->m_qRotation.imag.z < 0.0f ? 2.0f : -2.0f;
        const auto fHeading = acos(objInstance->m_qRotation.real) * fMult;
        pNewEntity->SetHeading(fHeading);
    }

    pNewEntity->SetPosn(objInstance->m_vecPosition);

    if (objInstance->m_bUnderwater)
        pNewEntity->m_bUnderwater = true;
    if (objInstance->m_bTunnel)
        pNewEntity->m_bTunnel = true;
    if (objInstance->m_bTunnelTransition)
        pNewEntity->m_bTunnelTransition = true;
    if (objInstance->m_bRedundantStream)
        pNewEntity->m_bUnimportantStream = true;

    pNewEntity->m_nAreaCode = objInstance->m_nAreaCode;
    pNewEntity->m_nLodIndex = objInstance->m_nLodInstanceIndex;

    if (objInstance->m_nModelId == ModelIndices::MI_TRAINCROSSING)
    {
        pNewEntity->GetMatrix();
        pNewEntity->AllocateStaticMatrix();
        CObject::SetMatrixForTrainCrossing(&pNewEntity->GetMatrix(), PI * 0.43f);
    }

    auto* pColModel = pInfo->GetColModel();
    if (pColModel)
    {
        if (pColModel->m_boundSphere.m_bFlag0x01)
        {
            if (pColModel->m_boundSphere.m_nColSlot)
            {
                CRect rect;
                pNewEntity->GetBoundRect(&rect);
                auto* pColDef = CColStore::ms_pColPool->GetAt(pColModel->m_boundSphere.m_nColSlot);
                pColDef->m_Area.Restrict(rect);
            }
        }
        else
        {
            pNewEntity->m_bUsesCollision = false;
        }

        if (pColModel->GetBoundingBox().m_vecMin.z + pNewEntity->GetPosition().z < 0.0f)
            pNewEntity->m_bUnderwater = true;
    }

    return pNewEntity;
}

// 0x538090
CEntity* CFileLoader::LoadObjectInstance(const char* line) {
    char modelName[24];
    CFileObjectInstance instance;
    sscanf(
        line,
        "%d %s %d %f %f %f %f %f %f %f %d",
        &instance.m_nModelId,
        modelName,
        &instance.m_nInstanceType,
        &instance.m_vecPosition.x,
        &instance.m_vecPosition.y,
        &instance.m_vecPosition.z,
        &instance.m_qRotation.imag.x,
        &instance.m_qRotation.imag.y,
        &instance.m_qRotation.imag.z,
        &instance.m_qRotation.real,
        &instance.m_nLodInstanceIndex
    );
    return LoadObjectInstance(&instance, modelName);
}

// 0x5B4B40
void CFileLoader::LoadCullZone(const char* line) {
    CVector center;
    float unknown;
    float length;
    float bottom;
    float width;
    float unknown2;
    float zTop;
    CVector mirrorDirection;
    float cm;
    int flags, flags2 = 0;

    int iNumRead = sscanf(
        line,
        "%f %f %f %f %f %f %f %f %f %d %f %f %f %f",
        &center.x,
        &center.y,
        &center.z,
        &unknown,
        &length,
        &bottom,
        &width,
        &unknown2,
        &zTop,
        &flags,
        &mirrorDirection.x,
        &mirrorDirection.y,
        &mirrorDirection.z,
        &cm
    );
    if (iNumRead == 14) {
        CCullZones::AddMirrorAttributeZone(
            center,
            unknown,
            length,
            bottom,
            width,
            unknown2,
            zTop,
            static_cast<eZoneAttributes>(flags),
            cm,
            mirrorDirection.x, mirrorDirection.y, mirrorDirection.z
        );
        return;
    }

    sscanf(
        line,
        "%f %f %f %f %f %f %f %f %f %d %d",
        &center.x,
        &center.y,
        &center.z,
        &unknown,
        &length,
        &bottom,
        &width,
        &unknown2,
        &zTop,
        &flags,
        &flags2
    );
    CCullZones::AddCullZone(center, unknown, length, bottom, width, unknown2, zTop, flags);
}

// IPL -> ENEX
// 0x5B8030
void CFileLoader::LoadEntryExit(const char* line) {
    float   enter_x, enter_y, enter_z;
    float   enter_rotation;
    float   x_radius, y_radius;
    int32_t c8; // constant 8
    float   exit_x, exit_y, exit_z;
    float   exitRotation;
    int32_t interiorId;
    int32_t markerType;
    char    interiorName[32];
    int32_t skyColor;
    int32_t flags; // unknown integer flags, could be weather related
    int32_t timeOn, timeOff;

    flags = 2;
    timeOn = 0;
    timeOff = 24;
    sscanf(
        line,
        "%f %f %f %f %f %f %f %f %f %f %f %d %d %s %d %d %d %d",
        &enter_x, &enter_y, &enter_z, &enter_rotation,
        &x_radius, &y_radius,
        &c8,
        &exit_x, &exit_y, &exit_z, &exitRotation,
        &interiorId,
        &markerType,
        interiorName,
        &skyColor,
        &flags,
        &timeOn, &timeOff
    );
    char* name = strrchr(interiorName, '"'); // double quotes
    if (name) {
        *name = 0;
        name = &interiorName[1];
    }
    int id = CEntryExitManager::AddOne(
        enter_x, enter_y, enter_z, enter_rotation,
        x_radius, y_radius,
        c8,
        exit_x, exit_y, exit_z, exitRotation,
        interiorId,
        markerType,
        skyColor,
        timeOn, timeOff,
        flags,
        name
    );

    CEntryExit* entryExit = CEntryExitManager::mp_poolEntryExits->GetAt(id);
    if ((markerType & 0x1) != 0)
        entryExit->m_nFlags.bUnknownInterior = true;

    if ((markerType & 0x2) != 0)
        entryExit->m_nFlags.bUnknownPairing = true;

    if ((markerType & 0x4) != 0)
        entryExit->m_nFlags.bCreateLinkedPair = true;

    if ((markerType & 0x8) != 0)
        entryExit->m_nFlags.bRewardInterior = true;

    if ((markerType & 0x10) != 0)
        entryExit->m_nFlags.bUsedRewardEntrance = true;

    if ((markerType & 0x20) != 0)
        entryExit->m_nFlags.bCarsAndAircraft = true;

    if ((markerType & 0x40) != 0)
        entryExit->m_nFlags.bBikesAndMotorcycles = true;

    if ((markerType & 0x80u) != 0)
        entryExit->m_nFlags.bDisableOnFoot = true;
}

// IPL -> GRGE
// 0x5B4530
void CFileLoader::LoadGarage(const char* line) {
    return plugin::Call<0x5B4530, const char*>(line);

    // fails
    CVector  vec1, vec2;
    float    frontX, frontY;
    uint32_t door;
    int32_t  type;
    char*    name;

    auto iNumRead = sscanf(
        line,
        "%f %f %f %f %f %f %f %f %d %d %s",
        &vec1.x,
        &vec1.y,
        &vec1.z,
        &frontX,
        &frontY,
        &vec2.x,
        &vec2.y,
        &vec2.z,
        &door,
        &type,
        &name
    );
    if (iNumRead == 11) {
        CGarages::AddOne(vec1.x, vec1.y, vec1.z, frontX, frontY, vec2.x, vec2.y, vec2.z, static_cast<eGarageType>(type), 0, name, door);
    }
}

// 0x5B9030
void CFileLoader::LoadLevel(const char* filename) {
    RwTexDictionary* currentTXD = RwTexDictionaryGetCurrent();
    if (!currentTXD) {
        currentTXD = RwTexDictionaryCreate();
        RwTexDictionarySetCurrent(currentTXD);
    }

    char buf[64];

    bool bFirstIplLoaded = false;
    FILESTREAM file = CFileMgr::OpenFile(filename, "r");
    for (char* line = LoadLine(file); line; line = LoadLine(file)) {
        if (*line == '#')
            continue;

        if (strncmp("EXIT", line, 4) == 0)
            break;

        if (strncmp("TEXDICTION", line, 10) == 0) {
            strcpy(buf, line + 11);
            LoadingScreenLoadingFile(buf);
            RwTexDictionary* txd = LoadTexDictionary(buf);
            AddTexDictionaries(currentTXD, txd);
            RwTexDictionaryDestroy(txd);
        } else if (strncmp("IMG", line, 3) == 0) {
            const char* fname = line + 4; // skips "IMG "
            if (strcmp(fname, "MODELS\\GTA_INT.IMG") != 0) {
                CStreaming::AddImageToList(fname, true);
            }
        } else if (strncmp("COLFILE", line, 7) == 0)
        {
            const char* fname = line + 10; // skips "COLFILE 0 "
            LoadingScreenLoadingFile(fname);
            LoadCollisionFile(fname, 0);
        }
        else if (strncmp("MODELFILE", line, 9) == 0)
        {
            const char* fname = line + 10;
            LoadingScreenLoadingFile(fname);
            LoadAtomicFile(fname);
        }
        else if (strncmp("HIERFILE", line, 8) == 0)
        {
            const char* fname = line + 9;
            LoadingScreenLoadingFile(fname);
            LoadClumpFile(fname);
        }
        else if (strncmp("IDE", line, 3) == 0)
        {
            const char* fname = line + 4; // skips "IDE "
            LoadingScreenLoadingFile(fname);
            LoadObjectTypes(fname);
        }
        else if (strncmp("IPL", line, 3) == 0)
        {
            if (!bFirstIplLoaded) {
                MatchAllModelStrings();
            }

            strcpy(buf, line + 4); // skips "IPL "

            if (!bFirstIplLoaded) {
                LoadingScreenLoadingFile("Object Data");
                CObjectData::Initialise("DATA\\OBJECT.DAT", false);

                LoadingScreenLoadingFile("Setup vehicle info data");
                CVehicleModelInfo::SetupCommonData();

                LoadingScreenLoadingFile("Streaming Init");
                CStreaming::Init2();
                CLoadingScreen::NewChunkLoaded();

                LoadingScreenLoadingFile("Collision");
                CColStore::LoadAllBoundingBoxes();

                for (auto& mi : CModelInfo::ms_modelInfoPtrs) {
                    if (mi) {
                        mi->ConvertAnimFileIndex();
                    }
                }

                bFirstIplLoaded = true;
            }
            LoadingScreenLoadingFile(buf);
            LoadScene(buf);
        }
        else
        {
            strncmp("SPLASH", line, 6); // R*ight
        }
    }

    CFileMgr::CloseFile(file);
    RwTexDictionarySetCurrent(currentTXD);
    if (bFirstIplLoaded) {
        CIplStore::LoadAllRemainingIpls();
        CColStore::BoundingBoxesPostProcess();
        CTrain::InitTrains();
        CColStore::RemoveAllCollision();
    }
}

// IPL -> OCCL
// 0x5B4C80
void CFileLoader::LoadOcclusionVolume(const char* line, const char* filename) {
    float   directMidX, directMidY;
    float   bottomZ;
    float   widthX, widthY;
    float   height;
    float   rotX, rotY, rotZ = 0.0f;
    int32_t flags = 0;

    sscanf(line, "%f %f %f %f %f %f %f %f %f %d ", &directMidX, &directMidY, &bottomZ, &widthX, &widthY, &height, &rotX, &rotY, &rotZ, &flags);

    bool isInterior = false;
    uint32_t len = strlen(filename);
    if (filename[len - 7] == 'i' && filename[len - 6] == 'n' && filename[len - 5] == 't')
        isInterior = true;

    bottomZ = height * 0.5f + bottomZ;
    COcclusion::AddOne(directMidX, directMidY, bottomZ, widthX, widthY, height, rotX, rotY, rotZ, flags, isInterior);
}

// 0x5B41C0
int CFileLoader::LoadPathHeader(const char* line, int& outPathType) {
    int id;
    char modelName[32];

    sscanf(line, "%d %d %s", &outPathType, &id, modelName);
    return id;
}

// PEDS
// 0x5B7420
int CFileLoader::LoadPedObject(const char* line) {
    return plugin::CallAndReturn<int, 0x5B7420, const char*>(line);
}

// useless
// 0x5B41F0
void CFileLoader::LoadPedPathNode(const char* line, int objModelIndex, int pathEntryIndex) {
    plugin::Call<0x5B41F0, const char*, int, int>(line, objModelIndex, pathEntryIndex);
}

// 0x5B47B0
void CFileLoader::LoadPickup(const char* line) {
    plugin::Call<0x5B47B0, const char*>(line);
}

// 0x5B45D0
void CFileLoader::LoadStuntJump(const char* line) {
    CVector b1Min;
    CVector b1Max;
    CVector b2Min;
    CVector b2Max;
    CVector cameraPosn;
    int32_t reward;

    int iNumRead = sscanf(
        line,
        "%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %d",
        &b1Min.x,
        &b1Min.y,
        &b1Min.z,
        &b1Max.x,
        &b1Max.y,
        &b1Max.z,

        &b2Min.x,
        &b2Min.y,
        &b2Min.z,
        &b2Max.x,
        &b2Max.y,
        &b2Max.z,

        &cameraPosn.x,
        &cameraPosn.y,
        &cameraPosn.z,
        &reward
    );
    if (iNumRead == 16) {
        CBoundingBox start{b1Min, b1Max};
        CBoundingBox target{b2Min, b2Max};
        CStuntJumpManager::AddOne(start, target, cameraPosn, reward);
    }
}

// 0x5B75E0
int CFileLoader::LoadTXDParent(const char* line) {
    char name[32];
    char parentName[32];

    sscanf(line, "%s %s", name, parentName);
    int txdSlot = CTxdStore::FindTxdSlot(name);
    if (txdSlot == INVALID_POOL_SLOT)
        txdSlot = CTxdStore::AddTxdSlot(name);

    int parentSlot = CTxdStore::FindTxdSlot(parentName);
    if (parentSlot == INVALID_POOL_SLOT)
        parentSlot = CTxdStore::AddTxdSlot(parentName);

    CTxdStore::ms_pTxdPool->GetAt(txdSlot)->m_wParentIndex = parentSlot;

    return parentSlot;
}

// IPL -> TCYC
// 0x5B81D0
void CFileLoader::LoadTimeCyclesModifier(const char* line) {
    CVector vec1, vec2;
    int32_t farClip;
    int32_t extraColor;
    float   extraColorIntensity;
    float   falloffDist = 100.0f;
    float   unused = 1.0f;
    float   lodDistMult = 1.0f;

    auto iNumRead = sscanf(
        line,
        "%f %f %f %f %f %f %d %d %f %f %f %f",
        &vec1.x,
        &vec1.y,
        &vec1.z,
        &vec2.x,
        &vec2.y,
        &vec2.z,
        &farClip,
        &extraColor,
        &extraColorIntensity,
        &falloffDist,
        &unused,
        &lodDistMult
    );
    if (iNumRead < 12)
        lodDistMult = unused;

    CBox box;
    box.Set(vec1, vec2);
    return CTimeCycle::AddOne(box, farClip, extraColor, extraColorIntensity, falloffDist, lodDistMult);
}

// 0x5B6F30
int CFileLoader::LoadVehicleObject(const char* line) {
    // wrong

    int32_t  objId = MODEL_INVALID;
    char     modelName[24];
    char     textureName[24];
    char     type[8];
    char     handlingId[16];
    char     gameName[32];
    char     animations[16];
    char     group[16];
    int32_t  freq;
    int32_t  flags;
    uint32_t compRules;
    int32_t  wheelModelId = MODEL_INVALID;
    float    wheelScaleFront;
    float    wheelScaleRear;
    int32_t  wheelUpgradeClass = -1;

    int txdSlot = CTxdStore::FindTxdSlot("vehicle");
    if (txdSlot == -1)
        txdSlot = CTxdStore::AddTxdSlot("vehicle");

    sscanf(
        line,
        "%d %s %s %s %s %s %s %s %d %d %x %d %f %f %d",
        &objId,
        modelName, textureName,
        type,
        handlingId,
        gameName,
        animations,
        group,
        &freq,
        &flags,
        &compRules,
        &wheelModelId,
        &wheelScaleFront,
        &wheelScaleRear,
        &wheelUpgradeClass
    );
    CVehicleModelInfo* modelInfo = CModelInfo::AddVehicleModel(objId);
    modelInfo->SetModelName(modelName);
    modelInfo->SetTexDictionary(textureName);

    TxdDef* txd = CTxdStore::ms_pTxdPool->GetAt(modelInfo->m_nTxdIndex);
    txd->m_wParentIndex = txdSlot;

    modelInfo->SetAnimFile(animations);

    char* p;
    for (p = gameName; *p; p++)
        if (*p == '_')
            *p = ' ';

        strncpy(modelInfo->m_szGameName, gameName, 8u);

        modelInfo->m_nFlags = flags;
        tVehicleCompsUnion comps{};
        comps.m_nComps = compRules;
        modelInfo->m_extraComps = comps;

        if (strcmp(type, "car") == 0)
        {
            modelInfo->m_nVehicleType = VEHICLE_AUTOMOBILE;
            modelInfo->m_nWheelModelIndex = wheelModelId;
            modelInfo->m_fWheelSizeFront = wheelScaleFront;
            modelInfo->m_fWheelSizeRear = wheelScaleRear;
        }
        else if (strcmp(type, "mtruck") == 0)
        {
            modelInfo->m_nVehicleType = VEHICLE_MTRUCK;
            modelInfo->m_nWheelModelIndex = wheelModelId;
            modelInfo->m_fWheelSizeFront = wheelScaleFront;
            modelInfo->m_fWheelSizeRear = wheelScaleRear;
        }
        else if (strcmp(type, "quad") == 0)
        {
            modelInfo->m_nVehicleType = VEHICLE_QUAD;
            modelInfo->m_nWheelModelIndex = wheelModelId;
            modelInfo->m_fWheelSizeFront = wheelScaleFront;
            modelInfo->m_fWheelSizeRear = wheelScaleRear;
        }
        else if (strcmp(type, "heli") == 0)
        {
            modelInfo->m_nVehicleType = VEHICLE_HELI;
            modelInfo->m_nWheelModelIndex = wheelModelId;
            modelInfo->m_fWheelSizeFront = wheelScaleFront;
            modelInfo->m_fWheelSizeRear = wheelScaleRear;
        }
        else if (strcmp(type, "plane") == 0)
        {
            modelInfo->m_nVehicleType = VEHICLE_PLANE;
            modelInfo->m_nWheelModelIndex = wheelModelId;
            modelInfo->m_fWheelSizeFront = wheelScaleFront;
            modelInfo->m_fWheelSizeRear = wheelScaleRear;
        }
        else if (strcmp(type, "boat") == 0)
        {
            modelInfo->m_nVehicleType = VEHICLE_BOAT;
            modelInfo->m_nHandlingId = gHandlingDataMgr.GetHandlingId(handlingId);
            modelInfo->m_nWheelUpgradeClass = wheelUpgradeClass;
        }
        else if (strcmp(type, "train") == 0)
        {
            modelInfo->m_nVehicleType = VEHICLE_TRAIN;
            modelInfo->m_nHandlingId = gHandlingDataMgr.GetHandlingId(handlingId);
            modelInfo->m_nWheelUpgradeClass = wheelUpgradeClass;
        }
        else if (strcmp(type, "f_heli") == 0)
        {
            modelInfo->m_nVehicleType = VEHICLE_HELI; // Izzotop: Why not F_HELI?
            modelInfo->m_nHandlingId = gHandlingDataMgr.GetHandlingId(handlingId);
            modelInfo->m_nWheelUpgradeClass = wheelUpgradeClass;
        }
        else if (strcmp(type, "f_plane") == 0)
        {
            modelInfo->m_nVehicleType = VEHICLE_FPLANE;
            modelInfo->m_nWheelModelIndex = wheelModelId;
            modelInfo->m_fWheelSizeFront = 1.0f;
            modelInfo->m_fWheelSizeRear = 1.0f;
            modelInfo->m_nHandlingId = gHandlingDataMgr.GetHandlingId(handlingId);
            modelInfo->m_nWheelUpgradeClass = wheelUpgradeClass;
        }
        else if (strcmp(type, "bike") == 0)
        {
            modelInfo->m_nVehicleType = VEHICLE_BIKE;
            modelInfo->m_fBikeSteerAngle = wheelModelId;
        }
        else if (strcmp(type, "bmx") == 0)
        {
            modelInfo->m_nVehicleType = VEHICLE_BMX;
            modelInfo->m_fBikeSteerAngle = wheelModelId;
        }
        else if (strcmp(type, "trailer") == 0)
        {
            modelInfo->m_nVehicleType = VEHICLE_TRAILER;
            modelInfo->m_nWheelModelIndex = wheelModelId;
            modelInfo->m_fWheelSizeFront = wheelScaleFront;
            modelInfo->m_fWheelSizeRear = wheelScaleRear;
        }
        else
        {
            assert(false); // "Unknown vehicle type"
        }

        if (strcmp(group, "normal") == 0)
        {
            modelInfo->m_nVehicleClass = VEHICLE_CLASS_NORMAL;
        }
        else if (strcmp(group, "poorfamily") == 0)
        {
            modelInfo->m_nVehicleClass = VEHICLE_CLASS_POORFAMILY;
        }
        else if (strcmp(group, "richfamily") == 0)
        {
            modelInfo->m_nVehicleClass = VEHICLE_CLASS_RICHFAMILY;
        }
        else if (strcmp(group, "executive") == 0)
        {
            modelInfo->m_nVehicleClass = VEHICLE_CLASS_EXECUTIVE;
        }
        else if (strcmp(group, "worker") == 0)
        {
            modelInfo->m_nVehicleClass = VEHICLE_CLASS_WORKER;
        }
        else if (strcmp(group, "big") == 0)
        {
            modelInfo->m_nVehicleClass = VEHICLE_CLASS_BIG;
        }
        else if (strcmp(group, "taxi") == 0)
        {
            modelInfo->m_nVehicleClass = VEHICLE_CLASS_TAXI;
        }
        else if (strcmp(group, "moped") == 0)
        {
            modelInfo->m_nVehicleClass = VEHICLE_CLASS_MOPED;
        }
        else if (strcmp(group, "motorbike") == 0)
        {
            modelInfo->m_nVehicleClass = VEHICLE_CLASS_MOTORBIKE;
        }
        else if (strcmp(group, "leisureboat") == 0)
        {
            modelInfo->m_nVehicleClass = VEHICLE_CLASS_LEISUREBOAT;
        }
        else if (strcmp(group, "workerboat") == 0)
        {
            modelInfo->m_nVehicleClass = VEHICLE_CLASS_WORKERBOAT;
        }
        else if (strcmp(group, "bicycle") == 0)
        {
            modelInfo->m_nVehicleClass = VEHICLE_CLASS_BICYCLE;
        }
        else if (strcmp(group, "ignore") == 0)
        {
            modelInfo->m_nVehicleClass = VEHICLE_CLASS_IGNORE;
        }

        modelInfo->m_nFrq = freq;
        return objId;
}

// 0x5B3FB0
int CFileLoader::LoadWeaponObject(const char* line) {
    int32_t objId;
    char    modelName[24];
    char    texName[24];
    char    animName[16];
    int32_t weaponType;
    float   drawDist;

    sscanf(line, "%d %s %s %s %d %f", &objId, modelName, texName, animName, &weaponType, &drawDist);
    CWeaponModelInfo* weaponModel = CModelInfo::AddWeaponModel(objId);
    weaponModel->SetModelName(modelName);
    weaponModel->m_fDrawDistance = drawDist;
    weaponModel->SetTexDictionary(texName);
    weaponModel->SetAnimFile(animName);
    weaponModel->SetColModel(&CTempColModels::ms_colModelWeapon, false);
    return objId;
}

// 0x5B4AB0
void CFileLoader::LoadZone(const char* line) {
    char    name[24];
    int32_t type;
    CVector min, max;
    int32_t island;
    char    zoneName[12];

    auto iNumRead = sscanf(line, "%s %d %f %f %f %f %f %f %d %s", name, &type, &min.x, &min.y, &min.z, &max.x, &max.y, &max.z, &island, zoneName);
    if (iNumRead == 10)
        CTheZones::CreateZone(name, static_cast<eZoneType>(type), min.x, min.y, min.z, max.x, max.y, max.z, static_cast<eLevelName>(island), zoneName);
}

// 0x5B51E0
void LinkLods(int a1) {
    plugin::Call<0x5B51E0, int>(a1);
}

// 0x5B8700
void CFileLoader::LoadScene(const char* filename) {
    int32_t pathIndex = -1;
    int32_t pathType;
    eIPL    section = IPL_NONE;

    gCurrIplInstancesCount = 0;

    FILESTREAM file = CFileMgr::OpenFile(filename, "rb");
    for (char* line = LoadLine(file); line; line = LoadLine(file)) {
        if (*line == '\0' || *line == '#')
            continue;

        if (section == IPL_NONE) {
            if (make_fourcc4(line, "inst")) {
                section = IPL_INST;
            } else if (make_fourcc4(line, "mult")) {
                section = IPL_MULT;
            } else if (make_fourcc4(line, "zone")) {
                section = IPL_ZONE;
            } else if (make_fourcc4(line, "cull")) {
                section = IPL_CULL;
            } else if (make_fourcc4(line, "path")) {
                section = IPL_PATH;
            } else if (make_fourcc4(line, "occl")) {
                section = IPL_OCCL;
            } else if (make_fourcc4(line, "grge")) {
                section = IPL_GRGE;
            } else if (make_fourcc4(line, "enex")) {
                section = IPL_ENEX;
            } else if (make_fourcc4(line, "pick")) {
                section = IPL_PICK;
            } else if (make_fourcc4(line, "cars")) {
                section = IPL_CARS;
            } else if (make_fourcc4(line, "jump")) {
                section = IPL_JUMP;
            } else if (make_fourcc4(line, "tcyc")) {
                section = IPL_TCYC;
            } else if (make_fourcc4(line, "auzo")) {
                section = IPL_AUZO;
            } else if (make_fourcc3(line, "end")) {
                section = IPL_NONE;
            } else {
                switch (section) {
                case IPL_INST:
                    gCurrIplInstances[gCurrIplInstancesCount] = LoadObjectInstance(line);
                    gCurrIplInstancesCount = gCurrIplInstancesCount + 1;
                    break;
                case IPL_ZONE:
                    LoadZone(line);
                    break;
                case IPL_CULL:
                    LoadCullZone(line);
                    break;
                case IPL_PATH:
                    break;
                case IPL_OCCL:
                    LoadOcclusionVolume(line, filename);
                    break;
                case IPL_UNK7:
                    if (pathIndex == -1) {
                        LoadPathHeader(line, pathType);
                        pathIndex = 0;
                    } else {
                        if (pathType) {
                            if (pathType == 1) {
                                LoadCarPathNode(line, -1, pathIndex, false);
                            } else if (pathType == 2) {
                                LoadCarPathNode(line, -1, pathIndex, true);
                            }
                        } else {
                            LoadPedPathNode(line, -1, pathIndex);
                        }
                        if (++pathIndex == 12)
                            pathIndex = -1;
                    }
                    break;
                case IPL_GRGE:
                    LoadGarage(line);
                    break;
                case IPL_ENEX:
                    LoadEntryExit(line);
                    break;
                case IPL_PICK:
                    LoadPickup(line);
                    break;
                case IPL_CARS:
                    LoadCarGenerator(line, 0);
                    break;
                case IPL_JUMP:
                    LoadStuntJump(line);
                    break;
                case IPL_TCYC:
                    LoadTimeCyclesModifier(line);
                    break;
                case IPL_AUZO:
                    LoadAudioZone(line);
                    break;
                default:
                    break;
                }
            }
        }
    }

    CFileMgr::CloseFile(file);

    int32_t indexArrayId = -1;
    if (gCurrIplInstancesCount > 0) {
        indexArrayId = CIplStore::GetNewIplEntityIndexArray(gCurrIplInstancesCount);
        auto paIndexArray = (CEntity**)(CIplStore::GetIplEntityIndexArray(indexArrayId));
        for (int i = 0; i < gCurrIplInstancesCount; ++i) {
            paIndexArray[i] = gCurrIplInstances[i];
        }
    }

    int32_t ipls = CIplStore::SetupRelatedIpls(filename, indexArrayId, (gCurrIplInstances + gCurrIplInstancesCount));
    LinkLods(ipls);
    CIplStore::RemoveRelatedIpls(indexArrayId);
}

// 0x5B8400
void CFileLoader::LoadObjectTypes(const char* filename) {
    // unused
    char path[256] = {0};
    strcpy(path, filename);

    int minId = -1;
    int maxId = 0x7FFFFFF;

    int id, pathType;
    int pathIndex = -1;

    FILESTREAM file = CFileMgr::OpenFile(filename, "rb");

    eIDE section = IDE_NONE;
    while (true) {
        const char* line = LoadLine(file);
        if (!line)
            break;

        if (!line[0] || line[0] == '#')
            continue;

        if (section == IDE_NONE) {
            switch (*(unsigned int*)line) {
            case make_fourcc4("objs"):
                section = IDE_OBJS;
                break;
            case make_fourcc4("tobj"):
                section = IDE_TOBJ;
                break;
            case make_fourcc4("weap"):
                section = IDE_WEAP;
                break;
            case make_fourcc4("hier"):
                section = IDE_HIER;
                break;
            case make_fourcc4("anim"):
                section = IDE_ANIM;
                break;
            case make_fourcc4("cars"):
                section = IDE_CARS;
                break;
            case make_fourcc4("peds"):
                section = IDE_PEDS;
                break;
            case make_fourcc4("path"):
                section = IDE_PATH;
                break;
            case make_fourcc4("2dfx"):
                section = IDE_2DFX;
                break;
            case make_fourcc4("txdp"):
                section = IDE_TXDP;
                break;
            }
            continue;
        }

        if (make_fourcc3(line, "end")) {
            section = IDE_NONE;
            continue;
        }

        int modelId = MODEL_INVALID;
        switch (section) {
        case IDE_OBJS:
            modelId = LoadObject(line);
            break;
        case IDE_TOBJ:
            modelId = LoadTimeObject(line);
            break;
        case IDE_WEAP:
            modelId = LoadWeaponObject(line);
            break;
        case IDE_HIER:
            modelId = LoadClumpObject(line);
            break;
        case IDE_ANIM:
            modelId = LoadAnimatedClumpObject(line);
            break;
        case IDE_CARS:
            modelId = LoadVehicleObject(line);
            break;
        case IDE_PEDS:
            modelId = LoadPedObject(line);
            break;
        case IDE_PATH:
            if (pathIndex == -1) {
                id = LoadPathHeader(line, pathType);
                pathIndex = 0;
            } else {
                if (pathType == 0) {
                    LoadPedPathNode(line, id, pathIndex);
                } else if (pathType == 1) {
                    LoadCarPathNode(line, id, pathIndex, false);
                } else if (pathType == 2) {
                    LoadCarPathNode(line, id, pathIndex, true);
                }
                pathIndex++;
                if (pathIndex == 12)
                    pathIndex = -1;
            }
            break;
        case IDE_2DFX:
            Load2dEffect(line);
            break;
        case IDE_TXDP:
            LoadTXDParent(line);
            break;
        }

        if (modelId != MODEL_INVALID) {
            if (modelId > minId)
                minId = modelId;
            if (modelId < maxId)
                maxId = modelId;
        }
    }

    CFileMgr::CloseFile(file);
}

// 0x5B3AC0
void CFileLoader::ReloadObjectTypes(const char* arg1) {
    // NOP
}

// Izzotop: Untested and may be wrong, see at your own risk
// unused
// 0x5B6E10
void CFileLoader::ReloadPaths(const char* filename) {
    int32_t objModelIndex;
    int32_t id;
    char    unused[4];

    bool pathAllocated = false;
    int32_t pathEntryIndex = -1;
    FILESTREAM file = CFileMgr::OpenFile(filename, "r");
    for (char* line = LoadLine(file); line; line = LoadLine(file)) {
        if (*line == '#' || !*line)
            continue;

        if (pathAllocated) {
            if (make_fourcc3(line, "end")) {
                pathAllocated = false;
            } else if (pathEntryIndex == -1) {
                sscanf(line, "%d %d %s", &id, &objModelIndex, unused);
                pathEntryIndex = 0;
            } else {
                if (id) {
                    if (id == 1) {
                        LoadCarPathNode(line, objModelIndex, pathEntryIndex, false);
                    } else if (id == 2) {
                        LoadCarPathNode(line, objModelIndex, pathEntryIndex, true);
                    }
                } else {
                    LoadPedPathNode(line, objModelIndex, pathEntryIndex);
                }

                if (++pathEntryIndex == 12)
                    pathEntryIndex = -1;
            }
        } else if (make_fourcc4(line, "path")) {
            pathAllocated = true;
            CPathFind::AllocatePathFindInfoMem();
        }
    }

    CFileMgr::CloseFile(file);
}

/**
 * @param atomic callback atomic
 * @param data clump object (RpClump*)
 * @return callback atomic
 * @addr 0x5B3930
 */
RpAtomic* CFileLoader::FindRelatedModelInfoCB(RpAtomic* atomic, void* data) {
    char name[24] = {0};
    bool bDamage = false;

    const char* nodeName = GetFrameNodeName(RpAtomicGetFrame(atomic));
    GetNameAndDamage(nodeName, name, bDamage);

    int modelId = MODEL_INVALID;
    CBaseModelInfo* modelInfo = CModelInfo::GetModelInfo(name, &modelId);
    if (modelInfo) {
        CAtomicModelInfo* atomicModelInfo = modelInfo->AsAtomicModelInfoPtr();
        CVisibilityPlugins::SetAtomicRenderCallback(atomic, nullptr);
        if (bDamage) {
            atomicModelInfo->AsDamageAtomicModelInfoPtr()->SetDamagedAtomic(atomic);
        } else {
            atomicModelInfo->SetAtomic(atomic);
        }
        RpClumpRemoveAtomic(static_cast<RpClump*>(data), atomic);
        RwFrame* pRwFrame = RwFrameCreate();
        RpAtomicSetFrame(atomic, pRwFrame);
        CVisibilityPlugins::SetAtomicId(atomic, modelId);
    }
    return atomic;
}

/**
 * @param atomic callback atomic
 * @param data clump object (RpClump*)
 * @return callback atomic
 * @addr 0x537150
 */
RpAtomic* CFileLoader::SetRelatedModelInfoCB(RpAtomic* atomic, void* data) {
    char name[24] = {0};
    bool bDamage = false;

    auto pAtomicModelInfo = CModelInfo::GetModelInfo(gAtomicModelId)->AsAtomicModelInfoPtr();
    const char* frameNodeName = GetFrameNodeName(RpAtomicGetFrame(atomic));

    GetNameAndDamage(frameNodeName, name, bDamage);
    CVisibilityPlugins::SetAtomicRenderCallback(atomic, nullptr);
    if (bDamage) {
        pAtomicModelInfo->AsDamageAtomicModelInfoPtr()->SetDamagedAtomic(atomic);
    } else {
        pAtomicModelInfo->SetAtomic(atomic);
    }
    RpClumpRemoveAtomic(static_cast<RpClump*>(data), atomic);
    RwFrame* newFrame = RwFrameCreate();
    RpAtomicSetFrame(atomic, newFrame);
    CVisibilityPlugins::SetAtomicId(atomic, gAtomicModelId);
    return atomic;
}

/**
 * Adds texture to the dictionary
 * @param texture callback texture
 * @param dict texture dictionary (RwTexDictionary*)
 * @return callback texture
 * @addr 0x5B38F0
 */
RwTexture* AddTextureCB(RwTexture* texture, void* dict) {
    RwTexDictionaryAddTexture((RwTexDictionary*)dict, texture);
    return texture;
}

/**
 * Makes a copy of atomic and adds it to clump
 * @param atomic callback atomic
 * @param data clump object (RpClump*)
 * @return callback atomic
 * @addr 0x537290
 */
RpAtomic* CloneAtomicToClumpCB(RpAtomic* atomic, void* data) {
    RpAtomic* clone = RpAtomicClone(atomic);
    auto frame = static_cast<RwFrame*>(atomic->object.object.parent);
    RpAtomicSetFrame(clone, frame->root);
    RpClumpAddAtomic(static_cast<RpClump*>(data), clone);
    return atomic;
}

// Gets file name from a path
// 0x5B3660
const char* GetFilename(const char* filepath) {
    const char* pch = strrchr(filepath, '\\');
    return pch ? pch + 1 : filepath;
}

// 0x5B3680
void LoadingScreenLoadingFile(const char* str) {
    const char* screenName = GetFilename(str);
    sprintf(gString, "Loading %s", screenName);
    LoadingScreen("Loading the Game", gString);
}
