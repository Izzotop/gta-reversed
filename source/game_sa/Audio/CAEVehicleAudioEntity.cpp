#include "StdInc.h"


#include "CAEAudioHardware.h"
#include "CAEAudioUtility.h"
#include "CAESoundManager.h"

#define FLOAT_AT(adr) (*(float*)(adr))

CPed*& CAEVehicleAudioEntity::s_pPlayerAttachedForRadio = *(CPed**)0xB6B98C;
CPed*& CAEVehicleAudioEntity::s_pPlayerDriver = *(CPed**)0xB6B990;
bool& CAEVehicleAudioEntity::s_HelicoptorsDisabled = *(bool*)0xB6B994;
short& CAEVehicleAudioEntity::s_NextDummyEngineSlot = *(short*)0xB6B998;
tVehicleAudioSettings*& CAEVehicleAudioEntity::s_pVehicleAudioSettingsForRadio = *reinterpret_cast<tVehicleAudioSettings**>(0xB6B99C);
tEngineDummySlot(&CAEVehicleAudioEntity::s_DummyEngineSlots)[NUM_DUMMY_ENGINE_SLOTS] = *reinterpret_cast<tEngineDummySlot(*)[NUM_DUMMY_ENGINE_SLOTS]>(0xB6B9A0);

tVehicleAudioSettings const(&gVehicleAudioSettings)[NUM_VEH_AUDIO_SETTINGS] = *reinterpret_cast<tVehicleAudioSettings const(*)[232]>(0x860AF0);

void CAEVehicleAudioEntity::InjectHooks()
{
    ReversibleHooks::Install("CAEVehicleAudioEntity", "UpdateParameters", 0x4FB6C0, &CAEVehicleAudioEntity::UpdateParameters_Reversed);

    ReversibleHooks::Install("CAEVehicleAudioEntity", "Initialise", 0x4F7670, &CAEVehicleAudioEntity::Initialise);
    ReversibleHooks::Install("CAEVehicleAudioEntity", "Terminate", 0x4FB8C0, &CAEVehicleAudioEntity::Terminate);
    ReversibleHooks::Install("CAEVehicleAudioEntity", "GetAircraftNearPosition", 0x4F96A0, &CAEVehicleAudioEntity::GetAircraftNearPosition);
    ReversibleHooks::Install("CAEVehicleAudioEntity", "GetFlyingMetalVolume", 0x4F6150, &CAEVehicleAudioEntity::GetFlyingMetalVolume);

    ReversibleHooks::Install("CAEVehicleAudioEntity", "GetVehicleAudioSettings", 0x4F5C10, &CAEVehicleAudioEntity::GetVehicleAudioSettings);
    ReversibleHooks::Install("CAEVehicleAudioEntity", "RequestBankSlot", 0x4F4D10, &CAEVehicleAudioEntity::RequestBankSlot);
    ReversibleHooks::Install("CAEVehicleAudioEntity", "DemandBankSlot", 0x4F4E60, &CAEVehicleAudioEntity::DemandBankSlot);
    ReversibleHooks::Install("CAEVehicleAudioEntity", "DoesBankSlotContainThisBank", 0x4F4E30, &CAEVehicleAudioEntity::DoesBankSlotContainThisBank);
    ReversibleHooks::Install("CAEVehicleAudioEntity", "StoppedUsingBankSlot", 0x4F4DF0, &CAEVehicleAudioEntity::StoppedUsingBankSlot);
    ReversibleHooks::Install("CAEVehicleAudioEntity", "EnableHelicoptors", 0x4F4EF0, &CAEVehicleAudioEntity::EnableHelicoptors);
    ReversibleHooks::Install("CAEVehicleAudioEntity", "DisableHelicoptors", 0x4F4EE0, &CAEVehicleAudioEntity::DisableHelicoptors);
    ReversibleHooks::Install("CAEVehicleAudioEntity", "StaticGetPlayerVehicleAudioSettingsForRadio", 0x4F4ED0, &CAEVehicleAudioEntity::StaticGetPlayerVehicleAudioSettingsForRadio);
    ReversibleHooks::Install("CAEVehicleAudioEntity", "StaticInitialise", 0x5B99F0, &CAEVehicleAudioEntity::StaticInitialise);

    //ReversibleHooks::Install("CAEVehicleAudioEntity", "StaticService", 0x4F4EC0, &CAEVehicleAudioEntity::StaticService);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "GetVehicleTypeForAudio", 0x4F4F00, &CAEVehicleAudioEntity::GetVehicleTypeForAudio);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "IsAccInhibited", 0x4F4F70, &CAEVehicleAudioEntity::IsAccInhibited);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "IsAccInhibitedBackwards", 0x4F4FC0, &CAEVehicleAudioEntity::IsAccInhibitedBackwards);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "IsAccInhibitedForLowSpeed", 0x4F4FF0, &CAEVehicleAudioEntity::IsAccInhibitedForLowSpeed);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "IsAccInhibitedForTime", 0x4F5020, &CAEVehicleAudioEntity::IsAccInhibitedForTime);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "InhibitAccForTime", 0x4F5030, &CAEVehicleAudioEntity::InhibitAccForTime);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "IsCrzInhibitedForTime", 0x4F5050, &CAEVehicleAudioEntity::IsCrzInhibitedForTime);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "GetAccelAndBrake", 0x4F5080, &CAEVehicleAudioEntity::GetAccelAndBrake);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "GetVolumeForDummyIdle", 0x4F51F0, &CAEVehicleAudioEntity::GetVolumeForDummyIdle);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "GetFrequencyForDummyIdle", 0x4F5310, &CAEVehicleAudioEntity::GetFrequencyForDummyIdle);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "GetVolumeForDummyRev", 0x4F53D0, &CAEVehicleAudioEntity::GetVolumeForDummyRev);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "GetFrequencyForDummyRev", 0x4F54F0, &CAEVehicleAudioEntity::GetFrequencyForDummyRev);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "CancelVehicleEngineSound", 0x4F55C0, &CAEVehicleAudioEntity::CancelVehicleEngineSound);
    ReversibleHooks::Install("CAEVehicleAudioEntity", "UpdateVehicleEngineSound", 0x4F56D0, &CAEVehicleAudioEntity::UpdateVehicleEngineSound);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "JustGotInVehicleAsDriver", 0x4F5700, &CAEVehicleAudioEntity::JustGotInVehicleAsDriver);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "TurnOnRadioForVehicle", 0x4F5B20, &CAEVehicleAudioEntity::TurnOnRadioForVehicle);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "TurnOffRadioForVehicle", 0x4F5B60, &CAEVehicleAudioEntity::TurnOffRadioForVehicle);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "PlayerAboutToExitVehicleAsDriver", 0x4F5BA0, &CAEVehicleAudioEntity::PlayerAboutToExitVehicleAsDriver);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "CopHeli", 0x4F5C40, &CAEVehicleAudioEntity::CopHeli);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "GetFreqForIdle", 0x4F5C60, &CAEVehicleAudioEntity::GetFreqForIdle);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "GetVolForPlayerEngineSound", 0x4F5D00, &CAEVehicleAudioEntity::GetVolForPlayerEngineSound);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "JustFinishedAccelerationLoop", 0x4F5E50, &CAEVehicleAudioEntity::JustFinishedAccelerationLoop);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "UpdateGasPedalAudio", 0x4F5EB0, &CAEVehicleAudioEntity::UpdateGasPedalAudio);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "GetVehicleDriveWheelSkidValue", 0x4F5F30, &CAEVehicleAudioEntity::GetVehicleDriveWheelSkidValue);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "GetVehicleNonDriveWheelSkidValue", 0x4F6000, &CAEVehicleAudioEntity::GetVehicleNonDriveWheelSkidValue);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "GetBaseVolumeForBicycleTyre", 0x4F60B0, &CAEVehicleAudioEntity::GetBaseVolumeForBicycleTyre);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "GetHornState", 0x4F61E0, &CAEVehicleAudioEntity::GetHornState);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "GetSirenState", 0x4F62A0, &CAEVehicleAudioEntity::GetSirenState);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "StopGenericEngineSound", 0x4F6320, &CAEVehicleAudioEntity::StopGenericEngineSound);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "CAEVehicleAudioEntity", 0x4F63E0, &CAEVehicleAudioEntity::CAEVehicleAudioEntity);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "AddAudioEvent", 0x4F6420, &CAEVehicleAudioEntity::AddAudioEvent);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "AddAudioEvent", 0x4F7580, &CAEVehicleAudioEntity::AddAudioEvent);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "RequestNewPlayerCarEngineSound", 0x4F7A50, &CAEVehicleAudioEntity::RequestNewPlayerCarEngineSound);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "StartVehicleEngineSound", 0x4F7F20, &CAEVehicleAudioEntity::StartVehicleEngineSound);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "GetFreqForPlayerEngineSound", 0x4F8070, &CAEVehicleAudioEntity::GetFreqForPlayerEngineSound);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "PlaySkidSound", 0x4F8360, &CAEVehicleAudioEntity::PlaySkidSound);
    ReversibleHooks::Install("CAEVehicleAudioEntity", "PlayRoadNoiseSound", 0x4F84D0, &CAEVehicleAudioEntity::PlayRoadNoiseSound);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "PlayFlatTyreSound", 0x4F8650, &CAEVehicleAudioEntity::PlayFlatTyreSound);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "PlayReverseSound", 0x4F87D0, &CAEVehicleAudioEntity::PlayReverseSound);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "ProcessVehicleFlatTyre", 0x4F8940, &CAEVehicleAudioEntity::ProcessVehicleFlatTyre);
    ReversibleHooks::Install("CAEVehicleAudioEntity", "ProcessVehicleRoadNoise", 0x4F8B00, &CAEVehicleAudioEntity::ProcessVehicleRoadNoise);
    ReversibleHooks::Install("CAEVehicleAudioEntity", "ProcessReverseGear", 0x4F8DF0, &CAEVehicleAudioEntity::ProcessReverseGear);
    ReversibleHooks::Install("CAEVehicleAudioEntity", "ProcessVehicleSkidding", 0x4F8F10, &CAEVehicleAudioEntity::ProcessVehicleSkidding);
    ReversibleHooks::Install("CAEVehicleAudioEntity", "ProcessRainOnVehicle", 0x4F92C0, &CAEVehicleAudioEntity::ProcessRainOnVehicle);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "PlayAircraftSound", 0x4F93C0, &CAEVehicleAudioEntity::PlayAircraftSound);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "PlayBicycleSound", 0x4F9710, &CAEVehicleAudioEntity::PlayBicycleSound);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "PlayHornOrSiren", 0x4F99D0, &CAEVehicleAudioEntity::PlayHornOrSiren);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "UpdateBoatSound", 0x4F9E90, &CAEVehicleAudioEntity::UpdateBoatSound);
    ReversibleHooks::Install("CAEVehicleAudioEntity", "ProcessBoatMovingOverWater", 0x4FA0C0, &CAEVehicleAudioEntity::ProcessBoatMovingOverWater);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "UpdateTrainSound", 0x4FA1C0, &CAEVehicleAudioEntity::UpdateTrainSound);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "ProcessTrainTrackSound", 0x4FA3F0, &CAEVehicleAudioEntity::ProcessTrainTrackSound);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "PlayTrainBrakeSound", 0x4FA630, &CAEVehicleAudioEntity::PlayTrainBrakeSound);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "ProcessDummyRCPlane", 0x4FA7C0, &CAEVehicleAudioEntity::ProcessDummyRCPlane);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "ProcessDummyRCHeli", 0x4FAA80, &CAEVehicleAudioEntity::ProcessDummyRCHeli);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "UpdateGenericVehicleSound", 0x4FAD40, &CAEVehicleAudioEntity::UpdateGenericVehicleSound);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "ProcessEngineDamage", 0x4FAE20, &CAEVehicleAudioEntity::ProcessEngineDamage);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "ProcessNitro", 0x4FB070, &CAEVehicleAudioEntity::ProcessNitro);
    ReversibleHooks::Install("CAEVehicleAudioEntity", "ProcessMovingParts", 0x4FB260, &CAEVehicleAudioEntity::ProcessMovingParts);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "ProcessPlayerVehicleEngine", 0x4FBB10, &CAEVehicleAudioEntity::ProcessPlayerVehicleEngine);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "ProcessDummyStateTransition", 0x4FCA10, &CAEVehicleAudioEntity::ProcessDummyStateTransition);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "JustGotOutOfVehicleAsDriver", 0x4FCF40, &CAEVehicleAudioEntity::JustGotOutOfVehicleAsDriver);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "JustWreckedVehicle", 0x4FD0B0, &CAEVehicleAudioEntity::JustWreckedVehicle);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "ProcessPlayerProp", 0x4FD290, &CAEVehicleAudioEntity::ProcessPlayerProp);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "ProcessDummyProp", 0x4FD8F0, &CAEVehicleAudioEntity::ProcessDummyProp);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "ProcessAIProp", 0x4FDFD0, &CAEVehicleAudioEntity::ProcessAIProp);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "ProcessPlayerHeli", 0x4FE420, &CAEVehicleAudioEntity::ProcessPlayerHeli);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "ProcessDummyHeli", 0x4FE940, &CAEVehicleAudioEntity::ProcessDummyHeli);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "ProcessAIHeli", 0x4FEE20, &CAEVehicleAudioEntity::ProcessAIHeli);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "ProcessPlayerSeaPlane", 0x4FF320, &CAEVehicleAudioEntity::ProcessPlayerSeaPlane);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "ProcessDummySeaPlane", 0x4FF7C0, &CAEVehicleAudioEntity::ProcessDummySeaPlane);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "ProcessGenericJet", 0x4FF900, &CAEVehicleAudioEntity::ProcessGenericJet);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "ProcessDummyBicycle", 0x4FFDC0, &CAEVehicleAudioEntity::ProcessDummyBicycle);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "ProcessPlayerBicycle", 0x500040, &CAEVehicleAudioEntity::ProcessPlayerBicycle);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "ProcessVehicleSirenAlarmHorn", 0x5002C0, &CAEVehicleAudioEntity::ProcessVehicleSirenAlarmHorn);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "ProcessBoatEngine", 0x5003A0, &CAEVehicleAudioEntity::ProcessBoatEngine);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "ProcessDummyTrainEngine", 0x500710, &CAEVehicleAudioEntity::ProcessDummyTrainEngine);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "ProcessPlayerTrainBrakes", 0x500AB0, &CAEVehicleAudioEntity::ProcessPlayerTrainBrakes);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "ProcessPlayerCombine", 0x500CE0, &CAEVehicleAudioEntity::ProcessPlayerCombine);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "ProcessDummyRCCar", 0x500DC0, &CAEVehicleAudioEntity::ProcessDummyRCCar);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "ProcessDummyHovercraft", 0x500F50, &CAEVehicleAudioEntity::ProcessDummyHovercraft);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "ProcessDummyGolfCart", 0x501270, &CAEVehicleAudioEntity::ProcessDummyGolfCart);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "ProcessDummyVehicleEngine", 0x501480, &CAEVehicleAudioEntity::ProcessDummyVehicleEngine);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "ProcessPlayerJet", 0x501650, &CAEVehicleAudioEntity::ProcessPlayerJet);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "ProcessDummyJet", 0x501960, &CAEVehicleAudioEntity::ProcessDummyJet);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "ProcessSpecialVehicle", 0x501AB0, &CAEVehicleAudioEntity::ProcessSpecialVehicle);
    ReversibleHooks::Install("CAEVehicleAudioEntity", "ProcessAircraft", 0x501C50, &CAEVehicleAudioEntity::ProcessAircraft);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "ProcessVehicle", 0x501E10, &CAEVehicleAudioEntity::ProcessVehicle);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "Service", 0x502280, &CAEVehicleAudioEntity::Service);
    //ReversibleHooks::Install("CAEVehicleAudioEntity", "~CAEVehicleAudioEntity", 0x6D0A10, &CAEVehicleAudioEntity::~CAEVehicleAudioEntity);
}

CAEVehicleAudioEntity::CAEVehicleAudioEntity() : CAEAudioEntity(), m_twinSkidSound()
{
    m_bEnabled = false;
    m_pEntity = nullptr;
}

// 0x6D0A10
CAEVehicleAudioEntity::~CAEVehicleAudioEntity()
{
    if (m_bEnabled)
        Terminate();
}

void CAEVehicleAudioEntity::UpdateParameters(CAESound* sound, short curPlayPos)
{
    UpdateParameters_Reversed(sound, curPlayPos);
}

// 0x5B99F0
void CAEVehicleAudioEntity::StaticInitialise()
{
    for (auto& dummyEng : s_DummyEngineSlots)
    {
        dummyEng.m_nBankId = -1;
        dummyEng.m_nUsageCount = 0;
    }

    AEAudioHardware.LoadSoundBank(138, 19);
    AEAudioHardware.LoadSoundBank(13, 18);
    AEAudioHardware.LoadSoundBank(74, 17);

    s_pVehicleAudioSettingsForRadio = nullptr;
    s_pPlayerAttachedForRadio = nullptr;
    s_pPlayerDriver = nullptr;;
    s_NextDummyEngineSlot = 0;
    s_HelicoptorsDisabled = false;
}

tVehicleAudioSettings* CAEVehicleAudioEntity::StaticGetPlayerVehicleAudioSettingsForRadio()
{
    return s_pVehicleAudioSettingsForRadio;
}

// 0x4F4EE0
void CAEVehicleAudioEntity::EnableHelicoptors() {
    s_HelicoptorsDisabled = false;
}

// 0x4F4EF0
void CAEVehicleAudioEntity::DisableHelicoptors() {
    s_HelicoptorsDisabled = true;
}

// 0x4F4E30
bool CAEVehicleAudioEntity::DoesBankSlotContainThisBank(short bankSlot, short bankId)
{
    const auto usedSlot = bankSlot - 7;
    if (usedSlot < 0 || usedSlot > NUM_DUMMY_ENGINE_SLOTS)
        return false;

    return s_DummyEngineSlots[usedSlot].m_nBankId == bankId;
}

// 0x4F4E60
short CAEVehicleAudioEntity::DemandBankSlot(short bankId)
{
    const auto requestResult = RequestBankSlot(bankId);
    if (requestResult != -1)
        return requestResult;

    auto slotToFree = 0;
    for (auto i = 1; i < NUM_DUMMY_ENGINE_SLOTS; ++i)
    {
        if (s_DummyEngineSlots[i].m_nUsageCount < s_DummyEngineSlots[0].m_nUsageCount)
        {
            slotToFree = i;
            break;
        }
    }

    s_DummyEngineSlots[slotToFree].m_nUsageCount = 0;
    return RequestBankSlot(bankId);
}

// 0x4F4D10
short CAEVehicleAudioEntity::RequestBankSlot(short bankId)
{
    auto freeSlot = -1;
    for (auto i = 0; i < NUM_DUMMY_ENGINE_SLOTS; ++i)
    {
        auto& dummyEng = s_DummyEngineSlots[i];
        if (dummyEng.m_nBankId == bankId) {
            dummyEng.m_nUsageCount++;
            return i + 7;
        }

        if (dummyEng.m_nUsageCount <= 0)
            freeSlot = i;
    }

    if (freeSlot == -1)
        return -1;

    for (auto i = 0; i < NUM_DUMMY_ENGINE_SLOTS; ++i)
    {
        const auto iSlot = (s_NextDummyEngineSlot + i) % NUM_DUMMY_ENGINE_SLOTS;
        auto& dummyEng = s_DummyEngineSlots[iSlot];
        if (dummyEng.m_nUsageCount > 0)
            continue;

        freeSlot = iSlot;
        ++dummyEng.m_nUsageCount;
        s_NextDummyEngineSlot = (freeSlot + 1) % NUM_DUMMY_ENGINE_SLOTS;
        break;
    }

    AESoundManager.CancelSoundsInBankSlot(freeSlot + 7, true);
    AEAudioHardware.LoadSoundBank(bankId, freeSlot + 7);
    s_DummyEngineSlots[freeSlot].m_nBankId = bankId;
    s_DummyEngineSlots[freeSlot].m_nUsageCount = 1;
    return freeSlot + 7;
}

void CAEVehicleAudioEntity::StoppedUsingBankSlot(short bankSlot)
{
    const auto usedSlot = bankSlot - 7;
    if (usedSlot < 0 || usedSlot > NUM_DUMMY_ENGINE_SLOTS)
        return;

    auto& dummyEng = s_DummyEngineSlots[usedSlot];
    dummyEng.m_nUsageCount = std::max(0, dummyEng.m_nUsageCount - 1);
}

// 0x4F5C10
tVehicleAudioSettings CAEVehicleAudioEntity::GetVehicleAudioSettings(short vehId)
{
    return gVehicleAudioSettings[vehId - 400];
}

void CAEVehicleAudioEntity::UpdateParameters_Reversed(CAESound* sound, short curPlayPos)
{
    if (!sound)
        return;

    if (sound->m_nEvent == eAudioEvents::AE_BONNET_FLUBBER_FLUBBER)
    {
        if (!sound->m_pPhysicalEntity)
            return;

        const auto fBaseVolume = static_cast<float>(m_pAudioEventVolumes[eAudioEvents::AE_BONNET_FLUBBER_FLUBBER]);
        sound->m_fVolume = fBaseVolume + CAEVehicleAudioEntity::GetFlyingMetalVolume(sound->m_pPhysicalEntity->AsPhysical());
    }

    if (sound->m_nEvent == eAudioEvents::AE_BOAT_HIT_WAVE)
    {
        if (curPlayPos == -1)
            return;

        sound->SetPosition(m_pEntity->GetPosition());
        if (CWeather::UnderWaterness >= 0.5F)
            sound->StopSound();
    }

    if (curPlayPos == -1)
    {
        if (sound == m_pSkidSoundMaybe)
            m_pSkidSoundMaybe = nullptr;
        else if (sound == m_pRoadNoiseSound)
            m_pRoadNoiseSound = nullptr;
        else if (sound == m_pFlatTyreSound)
            m_pFlatTyreSound = nullptr;
        else if (sound == m_pReverseGearSound)
            m_pReverseGearSound = nullptr;
        else if (sound == m_pHornTonSound)
            m_pHornTonSound = nullptr;
        else if (sound == m_pSirenSound)
            m_pSirenSound = nullptr;
        else if (sound == m_pPoliceSirenSound)
            m_pPoliceSirenSound = nullptr;
        else
        {
            for (auto& engSound : m_aEngineSounds)
            {
                if (engSound.m_pSound == sound)
                {
                    engSound.m_pSound = nullptr;
                    break;
                }
            }
        }
    }
    else
    {
        if ((m_settings.IsFlyingVehicle() || m_settings.IsNonVeh()) && m_aEngineSounds[3].m_pSound)
            sound->SetPosition(CAEVehicleAudioEntity::GetAircraftNearPosition());
        else
            sound->SetPosition(m_pEntity->GetPosition());
    }

    if ((m_settings.IsCar() || m_settings.IsMotorcycle()) && sound == m_aEngineSounds[4].m_pSound)
    {
        m_nSomePrevPlayPos = m_nSomeCurPlayPos;
        m_nSomeCurPlayPos = curPlayPos;
    }
}

void CAEVehicleAudioEntity::AddAudioEvent(eAudioEvents audioEvent, float fVolume)
{
    plugin::CallMethod<0x4F6420, CAEVehicleAudioEntity*, int, float>(this, audioEvent, fVolume);
}

// 0x4F7580
void CAEVehicleAudioEntity::AddAudioEvent(int soundId, CVehicle* pVehicle) {
    plugin::CallMethod<0x4F7580, CAEVehicleAudioEntity*, int, CVehicle*>(this, soundId, pVehicle);
}

void CAEVehicleAudioEntity::Service()
{
    plugin::CallMethod<0x502280, CAEVehicleAudioEntity*>(this);
}

void CAEVehicleAudioEntity::Initialise(CEntity* entity)
{
    field_144 = 0;
    m_pEntity = entity;
    m_bPlayerDriver = false;
    m_bPlayerPassenger = false;
    m_bVehicleRadioPaused = false;
    m_bSoundsStopped = false;
    m_nEngineState = 0;
    field_AA = 0;
    field_AC = 0;
    m_nEngineBankSlotId = -1;
    m_nRainDropCounter = 0;
    field_7C = 0;
    field_B4 = 0;
    field_B8 = 0;
    field_BC = 0;
    m_nBoatHitWaveLastPlayedTime = 0;
    m_nTimeToInhibitAcc = 0;
    m_nTimeToInhibitCrz = 0;
    m_bNitroSoundPresent = false;
    m_bDisableHeliEngineSounds = false;
    m_nSomeCurPlayPos = -1;
    m_nSomePrevPlayPos = -1;
    field_154 = 0;
    field_14E = 0;
    field_14C = 0;

    for (auto i = 0; i < 12; ++i)
    {
        m_aEngineSounds[i].m_nIndex = i;
        m_aEngineSounds[i].m_pSound = nullptr;
    }

    m_fSirenVolume = -100.0;
    field_230 = -100.0;
    m_nSkidSoundType = -1;
    m_nRoadNoiseSoundType = -1;
    m_nFlatTyreSoundType = -1;
    m_nReverseGearSoundType = -1;
    field_234 = -1.0;
    field_22C = -1.0;
    field_248 = -1.0;
    m_pSkidSoundMaybe = nullptr;
    m_pRoadNoiseSound = nullptr;
    m_pFlatTyreSound = nullptr;
    m_pReverseGearSound = nullptr;
    m_pHornTonSound = nullptr;
    m_pSirenSound = nullptr;
    m_pPoliceSirenSound = nullptr;
    field_238 = 0.0;
    field_23C = 1.0;
    field_240 = 0;

    m_settings = GetVehicleAudioSettings(entity->m_nModelIndex);
    m_bModelWithSiren = entity->AsVehicle()->UsesSiren();
    if (m_settings.m_nRadioType == eRadioType::RADIO_UNKNOWN)
        m_settings.m_nRadioID = eRadioID::RADIO_NONE;

    m_fGeneralVehicleSoundVolume = CAEAudioEntity::GetDefaultVolume(eAudioEvents::AE_GENERAL_VEHICLE_SOUND);

    switch (entity->m_nModelIndex)
    {
    case MODEL_PIZZABOY:
    case MODEL_CADDY:
    case MODEL_FAGGIO:
    case MODEL_BAGGAGE:
    case MODEL_FORKLIFT:
    case MODEL_VORTEX:
    case MODEL_KART:
    case MODEL_MOWER:
    case MODEL_SWEEPER:
    case MODEL_TUG:
        m_bInhibitAccForLowSpeed = true;
        break;
    default:
        m_bInhibitAccForLowSpeed = false;
        break;
    }

    switch (m_settings.m_nVehicleSoundType)
    {
    case VEHICLE_SOUND_CAR:
        m_fGeneralVehicleSoundVolume -= 1.5F;
        m_nEngineAccelerateSoundBankId = m_settings.m_nEngineOnSoundBankId;
        m_nEngineDecelerateSoundBankId = m_settings.m_nEngineOffSoundBankId;
        if (m_bEnabled)
            return;

        if (m_settings.m_nEngineOffSoundBankId != -1 && m_settings.m_nEngineOffSoundBankId != 129)
            m_nEngineBankSlotId = RequestBankSlot(m_settings.m_nEngineOffSoundBankId);

        m_bEnabled = true;
        return;

    case VEHICLE_SOUND_MOTORCYCLE:
    case VEHICLE_SOUND_BICYCLE:
        m_nEngineAccelerateSoundBankId = m_settings.m_nEngineOnSoundBankId;

        if (m_settings.IsMotorcycle())
            m_fGeneralVehicleSoundVolume = m_fGeneralVehicleSoundVolume - 1.5F;

        if (m_bEnabled)
            return;

        m_nEngineDecelerateSoundBankId = m_settings.m_nEngineOffSoundBankId;
        if (m_nEngineDecelerateSoundBankId != -1)
            m_nEngineBankSlotId = RequestBankSlot(m_settings.m_nEngineOffSoundBankId);

        m_bEnabled = true;
        return;

    case VEHICLE_SOUND_BOAT:
    case VEHICLE_SOUND_TRAIN:
        m_nEngineAccelerateSoundBankId = m_settings.m_nEngineOnSoundBankId;
        m_nEngineDecelerateSoundBankId = m_settings.m_nEngineOffSoundBankId;
        if (m_bEnabled)
            return;

        if (m_settings.m_nEngineOffSoundBankId != -1 && m_settings.m_nEngineOffSoundBankId != 129)
            m_nEngineBankSlotId = RequestBankSlot(m_settings.m_nEngineOffSoundBankId);

        m_bEnabled = true;
        return;

    case VEHICLE_SOUND_HELI:
    case VEHICLE_SOUND_NON_VEH:
        m_nEngineDecelerateSoundBankId = m_settings.m_nEngineOffSoundBankId;
        m_nEngineAccelerateSoundBankId = m_settings.m_nEngineOnSoundBankId;

        m_bEnabled = true;
        return;

    case VEHICLE_SOUND_PLANE:
        m_nEngineDecelerateSoundBankId = m_settings.m_nEngineOffSoundBankId;
        m_nEngineAccelerateSoundBankId = m_settings.m_nEngineOnSoundBankId;
        if (m_bEnabled)
            return;

        if (m_settings.m_nEngineOffSoundBankId != -1)
            m_nEngineBankSlotId = RequestBankSlot(m_settings.m_nEngineOffSoundBankId);

        m_bEnabled = true;
        return;

    case VEHICLE_SOUND_TRAILER:
        m_nEngineAccelerateSoundBankId = m_settings.m_nEngineOnSoundBankId;
        m_fGeneralVehicleSoundVolume = m_fGeneralVehicleSoundVolume - 1.5F;
        if (m_bEnabled)
            return;

        m_nEngineDecelerateSoundBankId = m_settings.m_nEngineOffSoundBankId;
        if (m_nEngineDecelerateSoundBankId != -1)
            m_nEngineBankSlotId = RequestBankSlot(m_settings.m_nEngineOffSoundBankId);

        m_bEnabled = true;
        return;

    default:
        return;
    }
}

// 0x4FB8C0
void CAEVehicleAudioEntity::Terminate()
{
    if (!m_bEnabled)
        return;

    for (auto& engSound : m_aEngineSounds)
    {
        if (engSound.m_pSound)
        {
            engSound.m_pSound->SetIndividualEnvironment(eSoundEnvironment::SOUND_REQUEST_UPDATES, false);
            engSound.m_pSound->StopSound();
            engSound.m_pSound = nullptr;
        }
    }

    PlaySkidSound(-1, 1.0F, -100.0F);
    PlayTrainBrakeSound(-1, 1.0F, -100.0F);

    if (m_pSkidSoundMaybe)
    {
        m_pSkidSoundMaybe->SetIndividualEnvironment(eSoundEnvironment::SOUND_REQUEST_UPDATES, false);
        m_pSkidSoundMaybe->StopSound();
        m_pSkidSoundMaybe = nullptr;
        m_nSkidSoundType = -1;
    }

    if (m_pRoadNoiseSound)
    {
        m_pRoadNoiseSound->SetIndividualEnvironment(eSoundEnvironment::SOUND_REQUEST_UPDATES, false);
        m_pRoadNoiseSound->StopSound();
        m_pRoadNoiseSound = nullptr;
        m_nRoadNoiseSoundType = -1;
    }

    if (m_pFlatTyreSound)
    {
        m_pFlatTyreSound->SetIndividualEnvironment(eSoundEnvironment::SOUND_REQUEST_UPDATES, false);
        m_pFlatTyreSound->StopSound();
        m_pFlatTyreSound = nullptr;
        m_nFlatTyreSoundType = -1;
    }

    if (m_pReverseGearSound)
    {
        m_pReverseGearSound->SetIndividualEnvironment(eSoundEnvironment::SOUND_REQUEST_UPDATES, false);
        m_pReverseGearSound->StopSound();
        m_pReverseGearSound = nullptr;
        m_nReverseGearSoundType = -1;
    }

    if (m_pHornTonSound)
    {
        m_pHornTonSound->StopSoundAndForget();
        m_pHornTonSound = nullptr;
    }

    if (m_pSirenSound)
    {
        m_pSirenSound->StopSoundAndForget();
        m_pSirenSound = nullptr;
    }

    if (m_pPoliceSirenSound)
    {
        m_pPoliceSirenSound->StopSoundAndForget();
        m_pPoliceSirenSound = nullptr;
    }

    auto const radioType = m_settings.m_nRadioType;
    if (m_bPlayerDriver && (radioType == RADIO_CIVILIAN || radioType == RADIO_UNKNOWN || radioType == RADIO_EMERGENCY))
        AudioEngine.StopRadio(&m_settings, false);

    if (m_nEngineBankSlotId != -1)
    {
        const auto usedSlot = m_nEngineBankSlotId - 7;
        auto& dummyEng = s_DummyEngineSlots[usedSlot];
        if (usedSlot >= 0 && usedSlot < NUM_DUMMY_ENGINE_SLOTS && dummyEng.m_nBankId == m_nEngineDecelerateSoundBankId)
            dummyEng.m_nUsageCount = std::max(0, dummyEng.m_nUsageCount - 1);

        m_nEngineBankSlotId = -1;
    }

    m_nEngineDecelerateSoundBankId = -1;
    m_nEngineAccelerateSoundBankId = -1;
    m_pEntity = nullptr;
    m_nEngineState = 0;

    if (m_bPlayerDriver)
    {
        m_bPlayerDriver = false;
        s_pPlayerDriver = nullptr;
    }
    else if (m_bPlayerPassenger)
    {
        m_bPlayerPassenger = false;
    }
    else
    {
        m_bVehicleRadioPaused = false;
        m_bEnabled = false;
        return;
    }

    s_pPlayerAttachedForRadio = nullptr;
    s_pVehicleAudioSettingsForRadio = nullptr;
    m_bVehicleRadioPaused = false;
    m_bEnabled = false;
}

CVector CAEVehicleAudioEntity::GetAircraftNearPosition()
{
    static const short snHeliAudioComponent = tComponent::COMPONENT_WING_RR;

    CVector result;
    if (m_settings.IsHeli())
        m_pEntity->AsVehicle()->GetComponentWorldPosition(snHeliAudioComponent, result);
    else
        result = m_pEntity->GetPosition();

    return result;
}

// 0x4F6150
float CAEVehicleAudioEntity::GetFlyingMetalVolume(CPhysical* physical)
{
    const auto fTurnSpeedSquared = physical->m_vecTurnSpeed.SquaredMagnitude();
    if (fTurnSpeedSquared >= 0.5625F)
        return CAEAudioUtility::AudioLog10(1.0F) * 10.0F;

    const auto fVol = fTurnSpeedSquared / 0.5625F;
    if (fVol < 1.0e-10F)
        return -100.0F;

    return CAEAudioUtility::AudioLog10(fVol) * 10.0F;
}

// 0x4FA630
void CAEVehicleAudioEntity::PlayTrainBrakeSound(short soundType, float speed, float volume)
{
    plugin::CallMethod<0x4FA630, CAEAudioEntity*, short, float, float>(this, soundType, speed, volume);
}

// 0x4F4F00
void CAEVehicleAudioEntity::GetVehicleTypeForAudio() {
    return plugin::Call<0x4F4F00>();
}

// 0x4F4F70
bool CAEVehicleAudioEntity::IsAccInhibited(cVehicleParams& params) {
    return plugin::CallAndReturn<bool, 0x4F4F70, cVehicleParams&>(params);
}

// 0x4F4FC0
bool CAEVehicleAudioEntity::IsAccInhibitedBackwards(cVehicleParams& params) {
    return params.m_fWheelSpinForAudio > 5.0 || !params.m_nWheelsOnGround;
}

// 0x4F4FF0
bool CAEVehicleAudioEntity::IsAccInhibitedForLowSpeed(cVehicleParams& params) {
    return !m_bInhibitAccForLowSpeed && params.m_fVelocity < 0.1;
}

// 0x4F5020
bool CAEVehicleAudioEntity::IsAccInhibitedForTime() {
    return m_nTimeToInhibitAcc < CTimer::m_snTimeInMilliseconds;
}

// unused
// [ANDROID IDB] used in CAEVehicleAudioEntity::ProcessPlayerVehicleEngine
// 0x4F5030
void CAEVehicleAudioEntity::InhibitAccForTime(unsigned int time) {
    m_nTimeToInhibitAcc = time + CTimer::m_snTimeInMilliseconds;
}

// 0x4F5050
bool CAEVehicleAudioEntity::IsCrzInhibitedForTime() {
    return m_nTimeToInhibitCrz < CTimer::m_snTimeInMilliseconds;
}

// 0x4F5080
double CAEVehicleAudioEntity::GetAccelAndBrake(cVehicleParams& vehParams) {
    return plugin::CallMethodAndReturn<double, 0x4F5080, CAEVehicleAudioEntity*, cVehicleParams&>(this, vehParams);
}

// 0x4F51F0
double CAEVehicleAudioEntity::GetVolumeForDummyIdle(float gearRevProgress, float revProgressBaseline) {
    return plugin::CallMethodAndReturn<double, 0x4F51F0, float, float>(gearRevProgress, revProgressBaseline);
}

// 0x4F5310
double CAEVehicleAudioEntity::GetFrequencyForDummyIdle(float gearRevProgress, float revProgressBaseline) {
    return plugin::CallMethodAndReturn<double, 0x4F5310, float, float>(gearRevProgress, revProgressBaseline);
}

// 0x4F53D0
double CAEVehicleAudioEntity::GetVolumeForDummyRev(float a, float b) {
    return plugin::CallMethodAndReturn<double, 0x4F53D0, float, float>(a, b);
}

// 0x4F54F0
double CAEVehicleAudioEntity::GetFrequencyForDummyRev(float a, float b) {
    return plugin::CallMethodAndReturn<double, 0x4F54F0, float, float>(a, b);
}

// 0x4F55C0
void CAEVehicleAudioEntity::CancelVehicleEngineSound(short engineSoundStateId) {
    plugin::Call<0x4F55C0, short>(engineSoundStateId);
}

// 0x4F56D0
void CAEVehicleAudioEntity::UpdateVehicleEngineSound(short engineState, float speed, float volumeDelta)
{
    if (CAESound* pCurrSound = m_aEngineSounds[engineState].m_pSound) {
        pCurrSound->m_fVolume = m_fGeneralVehicleSoundVolume + volumeDelta;
        pCurrSound->m_fSpeed = speed;
    }
}

// 0x4F5700
void CAEVehicleAudioEntity::JustGotInVehicleAsDriver() {
    return plugin::Call<0x4F5700>();
}

// 0x4F5B20
void CAEVehicleAudioEntity::TurnOnRadioForVehicle() {
    return plugin::Call<0x4F5B20>();
}

// 0x4F5B60
void CAEVehicleAudioEntity::TurnOffRadioForVehicle() {
    return plugin::Call<0x4F5B60>();
}

// 0x4F5BA0
void CAEVehicleAudioEntity::PlayerAboutToExitVehicleAsDriver() {
    return plugin::Call<0x4F5BA0>();
}

// 0x4F5C40
bool CAEVehicleAudioEntity::CopHeli() {
    auto modelIndex = m_pEntity->m_nModelIndex;
    return modelIndex == MODEL_MAVERICK || modelIndex == MODEL_VCNMAV;
}

// 0x4F5C60
double CAEVehicleAudioEntity::GetFreqForIdle(float paramVelocityPercentage) {
    return plugin::CallAndReturn<double, 0x4F5C60>();
}

// 0x4F5D00
double CAEVehicleAudioEntity::GetVolForPlayerEngineSound(cVehicleParams&  vehParams, short engineState_QuestioMark) {
    return plugin::CallAndReturn<double, 0x4F5D00, cVehicleParams&, short>(vehParams, engineState_QuestioMark);
}

// 0x4F5E50
bool CAEVehicleAudioEntity::JustFinishedAccelerationLoop() {
    return plugin::CallMethodAndReturn<bool, 0x4F5E50, CAEVehicleAudioEntity*>(this);
}

// 0x4F5EB0
void CAEVehicleAudioEntity::UpdateGasPedalAudio(CAutomobile* pAuto, int vehType) {
    plugin::Call<0x4F5EB0, CAutomobile*, int>(pAuto, vehType);
}

// 0x4F5F30
double CAEVehicleAudioEntity::GetVehicleDriveWheelSkidValue(CVehicle* pVeh, int wheelState, float fUnk, cTransmission& transmission, float fVelocity) {
    return plugin::CallMethodAndReturn<double, 0x4F5F30, CAEVehicleAudioEntity*, CVehicle*, tWheelState, float, cTransmission&, float>(this, pVeh, (tWheelState)wheelState, fUnk, transmission, fVelocity);
}

// 0x4F6000
double CAEVehicleAudioEntity::GetVehicleNonDriveWheelSkidValue(CVehicle* pVeh, int wheelState, cTransmission& transmission, float fVelocity) {
    return plugin::CallMethodAndReturn<double, 0x4F6000, CAEVehicleAudioEntity*, CVehicle*, tWheelState, cTransmission&, float>(this, pVeh, (tWheelState)wheelState, transmission, fVelocity);
}

// 0x4F60B0
double CAEVehicleAudioEntity::GetBaseVolumeForBicycleTyre(float fGearVelocityProgress) {
    return plugin::CallMethodAndReturn<double, 0x4F60B0, CAEVehicleAudioEntity*, float>(this, fGearVelocityProgress);
}

// 0x4F61E0
void CAEVehicleAudioEntity::GetHornState(bool* pbOut, cVehicleParams& vehParams) {
    plugin::CallMethod<0x4F61E0, CAEVehicleAudioEntity*, bool*, cVehicleParams&>(this, pbOut, vehParams);
}

// 0x4F62A0
void CAEVehicleAudioEntity::GetSirenState(uchar* playSirenOrAlarm, uchar* playHorn, cVehicleParams& vehicleParams) {
    return plugin::CallMethod<0x4F62A0, CAEVehicleAudioEntity*, uchar*, uchar*, cVehicleParams&>(this, playSirenOrAlarm, playHorn, vehicleParams);
}

// unused
// 0x4F6320
void CAEVehicleAudioEntity::StopGenericEngineSound(short index) {
    auto sound = m_aEngineSounds[index].m_pSound;
    if (sound)
    {
        sound->SetIndividualEnvironment(eSoundEnvironment::SOUND_REQUEST_UPDATES, false);
        sound->StopSound();
        sound = nullptr;
    }
}

// 0x4F7A50
void CAEVehicleAudioEntity::RequestNewPlayerCarEngineSound(short vehicleSoundId, float speed, float changeSound) {
    plugin::CallMethod<0x4F7A50, CAEVehicleAudioEntity*, short, float, float>(this, vehicleSoundId, speed, changeSound);
}

// 0x4F7F20
void CAEVehicleAudioEntity::StartVehicleEngineSound(short engineState, float engineSoundSpeed, float volume) {
    plugin::CallMethod<0x4F7F20, CAEVehicleAudioEntity*, short, float, float>(this, engineState, engineSoundSpeed, volume);
}

// 0x4F8070
double CAEVehicleAudioEntity::GetFreqForPlayerEngineSound(cVehicleParams& vehParams, short engineState_QuestionMark) {
    return plugin::CallMethodAndReturn<double, 0x4F8070, CAEVehicleAudioEntity*, cVehicleParams&, int>(this, vehParams, engineState_QuestionMark);
}

// 0x4F8360
void CAEVehicleAudioEntity::PlaySkidSound(short newSkidSoundType, float speed, float volume) {
    plugin::CallMethod<0x4F8360, CAEVehicleAudioEntity*, short, float, float>(this, newSkidSoundType, speed, volume);
}

// 0x4F84D0
void CAEVehicleAudioEntity::PlayRoadNoiseSound(short newRoadNosiseSoundType, float speed, float volumeDelta)
{
    const float volume = m_fGeneralVehicleSoundVolume + volumeDelta;
    if (m_nRoadNoiseSoundType != newRoadNosiseSoundType)
    {
        if (m_pRoadNoiseSound)
        {
            m_pRoadNoiseSound->SetIndividualEnvironment(4, false);
            m_pRoadNoiseSound->StopSound();
            m_pRoadNoiseSound = nullptr;
        }

        // Create new sound
        m_nRoadNoiseSoundType = newRoadNosiseSoundType;
        if (newRoadNosiseSoundType != -1)
        {
            CVector pos = m_pEntity->GetPosition();
            CAESound toRequest;
            toRequest.Initialise(
                19,
                newRoadNosiseSoundType,
                this,
                pos,
                volume,
                1.0,
                1.0,
                1.0,
                false,
                4, // IndividualEnvironment 
                0.0,
                0
            );
            toRequest.m_fSpeed = speed;
            toRequest.m_fSoundDistance = 3.0f;
            m_pRoadNoiseSound = AESoundManager.RequestNewSound(&toRequest);
        }
    } else if (m_nRoadNoiseSoundType != -1 && m_pRoadNoiseSound) {
        // Same sound type already initialised, just set speed and volume
        m_pRoadNoiseSound->m_fSpeed = speed;
        m_pRoadNoiseSound->m_fVolume = volume;
    }
}


// 0x4F8650
void CAEVehicleAudioEntity::PlayFlatTyreSound(short soundId, float speed, float volumeDelta) {
    return plugin::CallMethod<0x4F8650, CAEVehicleAudioEntity*, short, float, float>(this, soundId, speed, volumeDelta);
}

// 0x4F87D0
void CAEVehicleAudioEntity::PlayReverseSound(short soundId, float speed, float volumeDelta) {
    return plugin::CallMethod<0x4F87D0, CAEVehicleAudioEntity*, short, float, float>(this, soundId, speed, volumeDelta);
}

// 0x4F9E90
void CAEVehicleAudioEntity::UpdateBoatSound(short engineState, short bankSlotId, short soundId, float speed, float volumeDelta) {
    return plugin::CallMethod<0x4F9E90, CAEVehicleAudioEntity*, short, short, short, float, float>(this, engineState, bankSlotId, soundId, speed, volumeDelta);
}

// 0x4FA1C0
void CAEVehicleAudioEntity::UpdateTrainSound(short engineState, short bankSlotId, short soundId, float speed, float volumeDelta) {
    return plugin::CallMethod<0x4FA1C0, CAEVehicleAudioEntity*, short, short, short, float, float>(this, engineState, bankSlotId, soundId, speed, volumeDelta);
}

// 0x4F93C0
void CAEVehicleAudioEntity::PlayAircraftSound(short engineState, short bankSlotId, short soundId, float speed, float volumeDelta) {
    return plugin::CallMethod<0x4F93C0, CAEVehicleAudioEntity*, short, short, short, float, float>(this, engineState, bankSlotId, soundId, speed, volumeDelta);
}

// 0x4F9710
void CAEVehicleAudioEntity::PlayBicycleSound(short engineState, short bankSlotId, short soundId, float speed, float volumeDelta) {
    return plugin::CallMethod<0x4F9710, CAEVehicleAudioEntity*, short, short, short, float, float>(this, engineState, bankSlotId, soundId, speed, volumeDelta);
}

// 0x4F99D0
void CAEVehicleAudioEntity::PlayHornOrSiren(bool hornState, char sirenOrAlarm, bool mrWhoopie, cVehicleParams& vehicleParams) {
    return plugin::CallMethod<0x4F99D0, CAEVehicleAudioEntity*, bool, char, bool, cVehicleParams&>(this, hornState, sirenOrAlarm, mrWhoopie, vehicleParams);
}

// 0x4FCF40
void CAEVehicleAudioEntity::JustGotOutOfVehicleAsDriver() {
    return plugin::CallMethod<0x4FCF40, CAEVehicleAudioEntity*>(this);
}

// 0x4FD0B0
void CAEVehicleAudioEntity::JustWreckedVehicle() {
    plugin::Call<0x4FD0B0>();
}

// 0x4FAD40
void CAEVehicleAudioEntity::UpdateGenericVehicleSound(short soundId, short bankSlotId, short bankId, short sfxId, float speed, float volume, float distance) {
    plugin::CallMethod<0x4FAD40, CAEVehicleAudioEntity*, short, short, short, short, float, float, float>(this, soundId, bankSlotId, bankId, sfxId, speed, volume, distance);
}

// 0x4F8940
void CAEVehicleAudioEntity::ProcessVehicleFlatTyre(cVehicleParams& vehicleParams) {
    plugin::CallMethod<0x4F8940, CAEVehicleAudioEntity*, cVehicleParams&>(this, vehicleParams);
}

bool IsSurfaceAudioGrass(char surface) {
    return g_surfaceInfos->IsAudioGrass(surface) || g_surfaceInfos->IsAudioLongGrass(surface);
}

bool IsSurfaceAudioEitherGravelWaterSand(char surface) {
    return g_surfaceInfos->IsAudioGravel(surface) ||
        g_surfaceInfos->IsAudioSand(surface) ||
        g_surfaceInfos->IsAudioWater(surface);
}

// 0x4F8B00
void CAEVehicleAudioEntity::ProcessVehicleRoadNoise(cVehicleParams& vehicleParams) {
    //plugin::CallMethod<0x4F8B00, CAEVehicleAudioEntity*, cVehicleParams&>(this, vehicleParams);

    CVehicle* pVehicle = vehicleParams.m_pVehicle;

    const auto CancelRoadNoise = [=] { PlayRoadNoiseSound(-1, 0.0f, 0.0f); };

    // Check if any wheels touch the ground. (Perhaps vehicleParams.m_nWheelsOnGround could be used?)
    switch (vehicleParams.m_vehicleType) {
    case VEHICLE_AUTOMOBILE: {
        if (!static_cast<CAutomobile*>(pVehicle)->m_nNumContactWheels) {
            CancelRoadNoise();
            return;
        }
    }
    case VEHICLE_BIKE: {
        if (!static_cast<CBike*>(pVehicle)->m_nNumContactWheels) {
            CancelRoadNoise();
            return;
        }
    }
    }

    switch (pVehicle->m_nModelIndex) {
    case MODEL_ARTICT1:
    case MODEL_ARTICT2:
    case MODEL_PETROTR:
    case MODEL_ARTICT3:
        break; // No transmission check for these models
    default: {
        if (!vehicleParams.m_pTransmission) {
            CancelRoadNoise();
            return;
        }
    }
    }

    const float fAbsVelocity = fabs(vehicleParams.m_fVelocity);
    if (fAbsVelocity <= 0.0f) {
        CancelRoadNoise();
        return;
    }

    float fSpeed = 1.0f;
    {
        const CVector camPos = TheCamera.GetPosition();
        const CVector vehAudioPos = m_pEntity->GetPosition();

        const float someDistance = *(float*)0x8CBD10; // 72.0f by default. TODO: Remains to test if value ever changes
        const float distanceProgress = (vehAudioPos - camPos).Magnitude() / someDistance;

        fSpeed = 0.75f + std::max(1.0f, distanceProgress) / 2.0f;
    }

    short nRoadNoiseSound = -1;
    float fVolumeBase = -12.0f;
    if (IsSurfaceAudioGrass(pVehicle->m_nContactSurface))
    {
        fSpeed *= 1.3f;
        fVolumeBase += *(float*)0xB6B9E4; // TODO: Insert value of var. here
        nRoadNoiseSound = 21;
    } else if (IsSurfaceAudioEitherGravelWaterSand(pVehicle->m_nContactSurface))
    {
        fVolumeBase += 4.5f; // TODO: Insert value of var. here
        nRoadNoiseSound = 22;
    }

    const float logaritmicVolume = std::min(1.0f, 2 * fAbsVelocity);
    float fVolume = -100.0f;
    if (logaritmicVolume > 0.0008f) {
        fVolume = fVolumeBase + CAEAudioUtility::AudioLog10(logaritmicVolume) * 20.0f;
    }

    // Playing sound with -100.0f volume, in case logaritmicVolume <= 0.0008f, doesn't make much sense..
    PlayRoadNoiseSound(nRoadNoiseSound, fSpeed, fVolume);
}

// 0x4F8DF0
void CAEVehicleAudioEntity::ProcessReverseGear(cVehicleParams& vehicleParams) {
    //plugin::CallMethod<0x4F8DF0, CAEVehicleAudioEntity*, cVehicleParams&>(this, vehicleParams);
    const auto pAuto = static_cast<CAutomobile*>(vehicleParams.m_pVehicle);
    if (pAuto->vehicleFlags.bEngineOn && (pAuto->m_fGasPedal < 0.0f || !pAuto->m_nCurrentGear)) { // Check if we are reversing

        float fReverseGearVelocityProgress = 0.0f;
        if (pAuto->m_nWheelsOnGround) {
            fReverseGearVelocityProgress = vehicleParams.m_fVelocity / vehicleParams.m_pTransmission->m_maxReverseGearVelocity;
        } else {
            if (pAuto->m_wheelsOnGrounPrev)
                pAuto->field_964 *= 0.4;
            fReverseGearVelocityProgress = pAuto->field_964;
        }
        fReverseGearVelocityProgress = fabs(fReverseGearVelocityProgress);

        PlayReverseSound(
            pAuto->m_fGasPedal >= 0.0f ? 20 : 19, // soundId
            FLOAT_AT(0x8CBD24) + fReverseGearVelocityProgress * FLOAT_AT(0x8CBD28), // speed
            fReverseGearVelocityProgress > 0.0f ? FLOAT_AT(0x8CBD2C) + CAEAudioUtility::AudioLog10(fReverseGearVelocityProgress) * 20.0: -100.0f // volume
        );
    } else { // Cancel sound otherwise
        PlayReverseSound(-1, 0.0f, 0.0f);
    }
}

// 0x4F8F10
void CAEVehicleAudioEntity::ProcessVehicleSkidding(cVehicleParams& vehicleParams) {
    //plugin::CallMethod<0x4F8F10, CAEVehicleAudioEntity*, cVehicleParams&>(this, vehicleParams);

    CVehicle* pVehicle = vehicleParams.m_pVehicle;


    tWheelState* wheelStates = nullptr;
    float* aWheelTimers = nullptr;

    bool bAreRearWheelsNotSkidding = false;
    float fUnk = 0.0f;
    auto nWheels = 0;

    switch (vehicleParams.m_vehicleType) {
    case VEHICLE_AUTOMOBILE: {
        nWheels = 4;

        auto pAuto = static_cast<CAutomobile*>(pVehicle);
        fUnk = pAuto->field_964;

        bAreRearWheelsNotSkidding = pAuto->m_aWheelState[CARWHEEL_REAR_LEFT] != WHEEL_STATE_SKIDDING &&
                                    pAuto->m_aWheelState[CARWHEEL_REAR_RIGHT] != WHEEL_STATE_SKIDDING;
        aWheelTimers = pAuto->m_aWheelTimer;
        wheelStates = pAuto->m_aWheelState;
        break;
    }
    case VEHICLE_BIKE: {
        nWheels = 2;

        auto pBike = static_cast<CBike*>(pVehicle);
        fUnk = pBike->field_808;
        bAreRearWheelsNotSkidding = pBike->m_anWheelState[1] != WHEEL_STATE_SKIDDING;
        wheelStates = pBike->m_anWheelState;
        aWheelTimers = pBike->m_wheelCollisionState;
        break;
    }
    default:
        return;
    }

    // Calcualte skid values sum of all wheels
    float fTotalSkidValue = 0.0f;
    for (auto i = 0; i < nWheels; i++) {
        const bool bIsFrontWheel = i == CARWHEEL_FRONT_LEFT || i == CARWHEEL_FRONT_RIGHT;
        const tWheelState thisWheelState = wheelStates[i];

        if (thisWheelState == WHEEL_STATE_NORMAL)
            continue;
        if (aWheelTimers[i] == 0.0f)
            continue;
        if (bAreRearWheelsNotSkidding)
            if (bIsFrontWheel)
                if (thisWheelState == WHEEL_STATE_SKIDDING)
                    continue;

        const auto dt = vehicleParams.m_pTransmission->m_nDriveType;
        if (dt == '4' ||
            dt == 'F' && bIsFrontWheel ||
            dt == 'R' && !bIsFrontWheel
        ) {
            fTotalSkidValue += GetVehicleDriveWheelSkidValue(
                vehicleParams.m_pVehicle, thisWheelState, fUnk, *vehicleParams.m_pTransmission, vehicleParams.m_fVelocity);
        } else {
            fTotalSkidValue += GetVehicleNonDriveWheelSkidValue(
                vehicleParams.m_pVehicle, thisWheelState, *vehicleParams.m_pTransmission, vehicleParams.m_fVelocity);
        }
    }

    const auto StopSkidSound = [&] { PlaySkidSound(-1, 0.0f, 0.0f); };
    if (fTotalSkidValue <= 0.0) {
        StopSkidSound();
        return;
    }

    short soundId = -1;
    float fBaseVolume = 0.0f, fSpeed = 1.0f;

    if (m_settings.m_nVehicleSoundType == VEHICLE_SOUND_BICYCLE) {
        soundId = 0;
        fBaseVolume = FLOAT_AT(0x8CBCF8);
        fSpeed = FLOAT_AT(0x8CBCEC) + fTotalSkidValue * FLOAT_AT(0x8CBCF0);
    } else {
        if (IsSurfaceAudioGrass(pVehicle->m_nContactSurface))
        {
            soundId = 6;
            fBaseVolume = -12.0f;
            fSpeed = FLOAT_AT(0x8CBCE0) * fTotalSkidValue + FLOAT_AT(0x8CBCDC);
        }
        else if (IsSurfaceAudioEitherGravelWaterSand(pVehicle->m_nContactSurface))
        {
            soundId = 8;
            fBaseVolume = -9.0;
            fSpeed = FLOAT_AT(0x8CBCD8) * fTotalSkidValue + FLOAT_AT(0x8CBCD4);
        } else {
            soundId = 24;
            fSpeed = FLOAT_AT(0x8CBCE8) * fTotalSkidValue + FLOAT_AT(0x8CBCE4);

            if (m_settings.m_nVehicleSoundType == VEHICLE_SOUND_MOTORCYCLE)
                fSpeed *= 1.2f;
        }

        switch (m_settings.m_nVehicleSoundType) {
        case VEHICLE_SOUND_PLANE:
        case VEHICLE_SOUND_HELI: {
            fBaseVolume += FLOAT_AT(0x8CBCF4);
            break;
        }
        }
    } 

    const float fAvgSkidValPerWheel = fTotalSkidValue / (float)nWheels;
    if (fAvgSkidValPerWheel > 0.00001f) {
        const float fVolume = FLOAT_AT(0xB6B9E0) + fBaseVolume + CAEAudioUtility::AudioLog10(fAvgSkidValPerWheel) * 20.0f;
        if (fVolume >= -100.0f) {
            PlaySkidSound(soundId, fSpeed, fVolume);
        } else
            StopSkidSound();
    } else
        StopSkidSound();
}

// 0x4F92C0
void CAEVehicleAudioEntity::ProcessRainOnVehicle(cVehicleParams& vehicleParams) {
    //plugin::CallMethod<0x4F92C0, CAEVehicleAudioEntity*, cVehicleParams&>(this, vehicleParams);
    if (!AEAudioHardware.IsSoundBankLoaded((ushort)BANK_RAIN_SOUNDS, 6))
        return;
    if (CAEWeatherAudioEntity::m_sfRainVolume <= -100.0f)
        return;
    if (++m_nRainDropCounter < 3)
        return;
    m_nRainDropCounter = 0;

    m_tempSound.Initialise(
        6,
        CAEAudioUtility::GetRandomNumberInRange(12, 15),
        this,
        m_pEntity->GetPosition(),
        FLOAT_AT(0xB6B9EC) + CAEWeatherAudioEntity::m_sfRainVolume,
        0.1f,
        1.0f,
        1.0f,
        0,
        0,
        0.0f,
        0
    );
    m_tempSound.m_nEvent = AE_RAIN_COLLISION;
    AESoundManager.RequestNewSound(&m_tempSound);
}

// 0x4FA0C0
void CAEVehicleAudioEntity::ProcessBoatMovingOverWater(cVehicleParams& vehicleParams) {
    //plugin::CallMethod<0x4FA0C0, CAEVehicleAudioEntity*, cVehicleParams&>(this, vehicleParams);
    auto pBoat = static_cast<CBoat*>(vehicleParams.m_pVehicle);

    // Originally there was a multiply by 1.33, thats the recp. of 0.75, which makes sense
    // because the abs. velocity is clamped to 0,75
    const float fVelocityProgress = std::min(0.75f, fabs(vehicleParams.m_fVelocity)) / 0.75f;

    float fVolume = -100.0f;
    if (pBoat->m_nBoatFlags.bOnWater && fVelocityProgress >= 0.00001f) {
        fVolume = CAEAudioUtility::AudioLog10(fVelocityProgress) * 20.0f;
        fVolume += (m_settings.m_nVehicleSoundType == VEHICLE_SOUND_NON_VEH) ? 12.0f : 3.0f;
    }

    float fSpeed = 0.8f + fVelocityProgress * 0.2f;
    if (CWeather::UnderWaterness >= 0.5f) {
        fSpeed *= 0.185f;
        fVolume += 6.0f;
    }

    UpdateBoatSound(6, 2, 3, fSpeed, fVolume);
}

// 0x4FA3F0
void CAEVehicleAudioEntity::ProcessTrainTrackSound(cVehicleParams& vehicleParams) {
    plugin::CallMethod<0x4FA3F0, CAEVehicleAudioEntity*, cVehicleParams&>(this, vehicleParams);
}

// 0x4FA7C0
void CAEVehicleAudioEntity::ProcessDummyRCPlane(cVehicleParams& vehicleParams) {
    plugin::CallMethod<0x4FA7C0, CAEVehicleAudioEntity*, cVehicleParams&>(this, vehicleParams);
}

// 0x4FAA80
void CAEVehicleAudioEntity::ProcessDummyRCHeli(cVehicleParams& vehicleParams) {
    plugin::CallMethod<0x4FAA80, CAEVehicleAudioEntity*, cVehicleParams&>(this, vehicleParams);
}

// 0x4FAE20
void CAEVehicleAudioEntity::ProcessEngineDamage(cVehicleParams& vehicleParams) {
    plugin::CallMethod<0x4FAE20, CAEVehicleAudioEntity*, cVehicleParams&>(this, vehicleParams);
}

// 0x4FB070
void CAEVehicleAudioEntity::ProcessNitro(cVehicleParams& vehicleParams) {
    plugin::CallMethod<0x4FB070, CAEVehicleAudioEntity*, cVehicleParams&>(this, vehicleParams);
}

// 0x4FB260
void CAEVehicleAudioEntity::ProcessMovingParts(cVehicleParams& vehicleParams) {
    //plugin::CallMethod<0x4FB260, CAEVehicleAudioEntity*, cVehicleParams&>(this, vehicleParams);
    switch (vehicleParams.m_pVehicle->m_nModelIndex) {
    case MODEL_PACKER:
    case MODEL_DOZER:
    case MODEL_DUMPER:

    // Note: Rockstar originally may have wanted it to have sound,
    // but they've only left it in the first `if` check, it has no `case` in the `switch` below.
    // case MODEL_CEMENT:

    case MODEL_ANDROM:
    case MODEL_FORKLIFT:
        break;
    default:
        return;
    }

    auto pVehicle = static_cast<CAutomobile*>(vehicleParams.m_pVehicle);

    float fComponentMoveProgress = (float)(pVehicle->m_wMiscComponentAngle - pVehicle->m_wMiscComponentAnglePrev) / 30.0f;
    fComponentMoveProgress = clamp<float>(fabs(fComponentMoveProgress), 0.0f, 1.0f);
    if (fComponentMoveProgress <= field_238)
        fComponentMoveProgress = std::max(field_238 - 0.2f, fComponentMoveProgress);
    else
        fComponentMoveProgress = std::min(field_238 + 0.2f, fComponentMoveProgress);
    field_238 = fComponentMoveProgress;


    float fSpeed = 1.0f, fVolume = 0.0f;
    short bankSlot = -1, bank = -1, sfxId = -1;

    switch (pVehicle->m_nModelIndex) {
    case MODEL_DUMPER: {
        bankSlot = 19;
        bank = 138;
        sfxId = 15;
        if (fComponentMoveProgress <= 0.0)
        {
            fSpeed = 0.9f;
            fVolume = 14.0f;
        }
        else
        {
            fSpeed = 1.1f;
            fVolume = 20.f;
        }
        break;
    }
    case MODEL_PACKER: {
        bankSlot = 19;
        bank = 138;
        sfxId = 15;
        if (fComponentMoveProgress <= 0.0)
        {
            fSpeed = 0.8f;
            fVolume = 3.0f;
        }
        else
        {
            fSpeed = 1.0f;
            fVolume = 9.0f;
        }
        break;
    }
    case MODEL_DOZER: {
        bankSlot = 19;
        bank = 138;
        sfxId = 15;
        if (fComponentMoveProgress <= 0.0)
        {
            fSpeed = 0.9f;
            fVolume = 2.0f;
        }
        else
        {
            fSpeed = 1.1f;
            fVolume = 6.0f;
        }
        break;
    }
    case MODEL_FORKLIFT: {
        bankSlot = m_nEngineBankSlotId;
        bank = 57;
        sfxId = 2;
        if (fComponentMoveProgress <= 0.0)
        {
            fSpeed = 0.8f;
            fVolume = -18.0f;
        }
        else
        {
            fSpeed = 1.0f;
            fVolume = -6.0f;
        }
        break;
    }
    case MODEL_ANDROM: {
        bankSlot = 19;
        bank = 138;
        sfxId = 15;
        if (fComponentMoveProgress <= 0.0)
        {
            fSpeed = 0.8f;
            fVolume = 21.0f;
        }
        else
        {
            fSpeed = 1.0f;
            fVolume = 24.0f;
        }
        break;
    }
    }

    fVolume += CAEAudioUtility::AudioLog10(field_238) * 20.0f;
    if (fVolume <= -100.0f) {
        if (auto& pSound = m_aEngineSounds[11].m_pSound)
        {
            pSound->SetIndividualEnvironment(4, 0);
            pSound->StopSound();
            pSound = nullptr;
        }
    } else {
        UpdateGenericVehicleSound(11, bankSlot, bank, sfxId, fSpeed, fVolume, 1.5f);
    }
}

// 0x4FBB10
void CAEVehicleAudioEntity::ProcessPlayerVehicleEngine(cVehicleParams& vehicleParams) {
    plugin::CallMethod<0x4FBB10, CAEVehicleAudioEntity*, cVehicleParams&>(this, vehicleParams);
}

// 0x4FCA10
void CAEVehicleAudioEntity::ProcessDummyStateTransition(short a1, float a2, cVehicleParams& vehicleParams) {
    plugin::CallMethod<0x4FCA10, CAEVehicleAudioEntity*, short, float, cVehicleParams&>(this, a1, a2, vehicleParams);
}

// 0x4FD290
void CAEVehicleAudioEntity::ProcessPlayerProp(cVehicleParams& vehicleParams) {
    plugin::CallMethod<0x4FD290, CAEVehicleAudioEntity*, cVehicleParams&>(this, vehicleParams);
}

// 0x4FD8F0
void CAEVehicleAudioEntity::ProcessDummyProp(cVehicleParams& vehicleParams) {
    plugin::CallMethod<0x4FD8F0, CAEVehicleAudioEntity*, cVehicleParams&>(this, vehicleParams);
}

// 0x4FDFD0
void CAEVehicleAudioEntity::ProcessAIProp(cVehicleParams& vehicleParams) {
    plugin::CallMethod<0x4FDFD0, CAEVehicleAudioEntity*, cVehicleParams&>(this, vehicleParams);
}

// 0x4FE420
void CAEVehicleAudioEntity::ProcessPlayerHeli(cVehicleParams& vehicleParams) {
    plugin::CallMethod<0x4FE420, CAEVehicleAudioEntity*, cVehicleParams&>(this, vehicleParams);
}

// 0x4FE940
void CAEVehicleAudioEntity::ProcessDummyHeli(cVehicleParams& vehicleParams) {
    plugin::CallMethod<0x4FE940, CAEVehicleAudioEntity*, cVehicleParams&>(this, vehicleParams);
}

// 0x4FEE20
void CAEVehicleAudioEntity::ProcessAIHeli(cVehicleParams& vehicleParams) {
    plugin::CallMethod<0x4FEE20, CAEVehicleAudioEntity*, cVehicleParams&>(this, vehicleParams);
}

// 0x4FF320
void CAEVehicleAudioEntity::ProcessPlayerSeaPlane(cVehicleParams& vehicleParams) {
    plugin::CallMethod<0x4FF320, CAEVehicleAudioEntity*, cVehicleParams&>(this, vehicleParams);
}

// 0x4FF7C0
void CAEVehicleAudioEntity::ProcessDummySeaPlane(cVehicleParams& vehicleParams) {
    plugin::CallMethod<0x4FF7C0, CAEVehicleAudioEntity*, cVehicleParams&>(this, vehicleParams);
}

// 0x4FF900
//void CAEVehicleAudioEntity::ProcessGenericJet(cVehicleParams& vehicleParams) {
//    plugin::CallMethod<0x4FF900, CAEVehicleAudioEntity*, cVehicleParams&>(this, vehicleParams);
//}

// 0x4FFDC0
void CAEVehicleAudioEntity::ProcessDummyBicycle(cVehicleParams& vehicleParams) {
    plugin::CallMethod<0x4FFDC0, CAEVehicleAudioEntity*, cVehicleParams&>(this, vehicleParams);
}

// 0x500040
void CAEVehicleAudioEntity::ProcessPlayerBicycle(cVehicleParams& vehicleParams) {
    plugin::CallMethod<0x500040, CAEVehicleAudioEntity*, cVehicleParams&>(this, vehicleParams);
}

// 0x5002C0
void CAEVehicleAudioEntity::ProcessVehicleSirenAlarmHorn(cVehicleParams& vehicleParams) {
    plugin::CallMethod<0x5002C0, CAEVehicleAudioEntity*, cVehicleParams&>(this, vehicleParams);
}

// 0x5003A0
void CAEVehicleAudioEntity::ProcessBoatEngine(cVehicleParams& vehicleParams) {
    plugin::CallMethod<0x5003A0, CAEVehicleAudioEntity*, cVehicleParams&>(this, vehicleParams);
}

// 0x500710
void CAEVehicleAudioEntity::ProcessDummyTrainEngine(cVehicleParams& vehicleParams) {
    plugin::CallMethod<0x500710, CAEVehicleAudioEntity*, cVehicleParams&>(this, vehicleParams);
}

// 0x500AB0
void CAEVehicleAudioEntity::ProcessPlayerTrainBrakes(cVehicleParams& vehicleParams) {
    plugin::CallMethod<0x500AB0, CAEVehicleAudioEntity*, cVehicleParams&>(this, vehicleParams);
}

// 0x500CE0
void CAEVehicleAudioEntity::ProcessPlayerCombine(cVehicleParams& vehicleParams) {
    plugin::CallMethod<0x500CE0, CAEVehicleAudioEntity*, cVehicleParams&>(this, vehicleParams);
}

// 0x500DC0
void CAEVehicleAudioEntity::ProcessDummyRCCar(cVehicleParams& vehicleParams) {
    plugin::CallMethod<0x500DC0, CAEVehicleAudioEntity*, cVehicleParams&>(this, vehicleParams);
}

// 0x500F50
void CAEVehicleAudioEntity::ProcessDummyHovercraft(cVehicleParams& vehicleParams) {
    plugin::CallMethod<0x500F50, CAEVehicleAudioEntity*, cVehicleParams&>(this, vehicleParams);
}

// 0x501270
void CAEVehicleAudioEntity::ProcessDummyGolfCart(cVehicleParams& vehicleParams) {
    plugin::CallMethod<0x501270, CAEVehicleAudioEntity*, cVehicleParams&>(this, vehicleParams);
}

// 0x501480
void CAEVehicleAudioEntity::ProcessDummyVehicleEngine(cVehicleParams& vehicleParams) {
    plugin::CallMethod<0x501480, CAEVehicleAudioEntity*, cVehicleParams&>(this, vehicleParams);
}

// 0x501650
void CAEVehicleAudioEntity::ProcessPlayerJet(cVehicleParams& vehicleParams) {
    plugin::CallMethod<0x501650, CAEVehicleAudioEntity*, cVehicleParams&>(this, vehicleParams);
}

// 0x501960
void CAEVehicleAudioEntity::ProcessDummyJet(cVehicleParams& vehicleParams) {
    plugin::CallMethod<0x501960, CAEVehicleAudioEntity*, cVehicleParams&>(this, vehicleParams);
}

// 0x501C50
void CAEVehicleAudioEntity::ProcessAircraft(cVehicleParams& vehParams) {
    //plugin::CallMethod<0x501C50, CAEVehicleAudioEntity*>(this, vehicleParams);
    if (m_bSoundsStopped)
        return;

    if (!AEAudioHardware.IsSoundBankLoaded(138u, 19))
        return;

    auto pVehicle = vehParams.m_pVehicle;
    switch (m_settings.m_nVehicleSoundType) {
    case VEHICLE_SOUND_HELI: {
        if (s_HelicoptorsDisabled || m_bDisableHeliEngineSounds)
            JustWreckedVehicle();
        else if (m_bPlayerDriver)
            ProcessPlayerHeli(vehParams);
        else if (pVehicle->m_nStatus == STATUS_PHYSICS)
            ProcessAIHeli(vehParams);
        else
            ProcessDummyHeli(vehParams);
        break;
    }
    case VEHICLE_SOUND_PLANE: {
        switch (pVehicle->m_nModelIndex)
        {
        case MODEL_SHAMAL:
        case MODEL_HYDRA:
        case MODEL_AT400:
        case MODEL_ANDROM: { // Originally there was an `isPlane` variable. I just rearranged stuff, to look nicer
            if (m_bPlayerDriver)
                ProcessPlayerJet(vehParams);
            else
                ProcessDummyJet(vehParams);
            break;
        }
        default: {
            if (m_bPlayerDriver)
                ProcessPlayerProp(vehParams);
            else if (pVehicle->m_nStatus == STATUS_PHYSICS || pVehicle->m_autoPilot.m_vehicleRecordingId >= 0)
                ProcessAIProp(vehParams);
            else
                ProcessDummyProp(vehParams);
        }
        }
        break;
    }
    case VEHICLE_SOUND_NON_VEH: {
        if (m_bPlayerDriver)
            ProcessPlayerSeaPlane(vehParams);
        else
            ProcessDummySeaPlane(vehParams);
        break;
    }
    }
}

// 0x501E10
void CAEVehicleAudioEntity::ProcessVehicle(CPhysical* vehicle) {
    return plugin::CallMethod<0x501E10, CAEVehicleAudioEntity*, CPhysical*>(this, vehicle);
}

// 0x501AB0
void CAEVehicleAudioEntity::ProcessSpecialVehicle(cVehicleParams& vehParams) {
    switch (vehParams.m_pVehicle->m_nModelIndex) {
    case MODEL_ARTICT1:
    case MODEL_ARTICT2:
    case MODEL_PETROTR:
    case MODEL_ARTICT3: {
        ProcessVehicleRoadNoise(vehParams);
        ProcessRainOnVehicle(vehParams);
        break;
    }
    case MODEL_RCBANDIT:
    case MODEL_RCTIGER: {
        ProcessDummyRCCar(vehParams);
    }
    case MODEL_CADDY: {
        ProcessVehicleRoadNoise(vehParams);
        ProcessVehicleSkidding(vehParams);
        ProcessVehicleFlatTyre(vehParams);
        ProcessVehicleSirenAlarmHorn(vehParams);
        ProcessDummyGolfCart(vehParams);
        ProcessRainOnVehicle(vehParams);
        if (vehParams.m_pVehicle->m_nStatus != STATUS_SIMPLE)
            ProcessEngineDamage(vehParams);
        break;
    }
    case MODEL_RCBARON: {
        ProcessDummyRCPlane(vehParams);
        break;
    }
    case MODEL_RCRAIDER:
    case MODEL_RCGOBLIN: {
        ProcessDummyRCHeli(vehParams);
        break;
    }
    case MODEL_VORTEX: {
        ProcessDummyHovercraft(vehParams);
        ProcessRainOnVehicle(vehParams);
        ProcessVehicleSirenAlarmHorn(vehParams);
        break;
    }
    }
}
