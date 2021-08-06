#pragma once

#include "dsound.h"

#include "AESoundManager.h"
#include "Vector.h"

#ifdef PlaySound
#undef PlaySound
#endif

union CAEAudioHardwarePlayFlags
{
    uint16_t m_nFlags;
    struct
    {
        uint16_t m_bIsFrontend : 1;
        uint16_t m_bIsUncompressable : 1;
        uint16_t m_bIsUnduckable : 1;
        uint16_t m_bIsStartPercentage : 1;
        uint16_t m_bIsMusicMastered : 1;
        uint16_t : 1;
        uint16_t m_bIsRolledOff : 1;
        uint16_t m_bIsSmoothDucking : 1;

        uint16_t m_bIsForcedFront : 1;
        uint16_t m_bUnpausable : 1;
    };
};

class CAEAudioHardware {


public:
    uint8_t  field_0;
    bool     m_bDisableEffectsLoading;
    uint8_t  field_2;
    uint8_t  field_3;
    uint8_t  field_4;
    uint8_t  m_nReverbEnvironment;
    int16_t  m_awChannelFlags[MAX_NUM_AUDIO_CHANNELS];
    uint16_t field_86;
    int32_t  m_nReverbDepth;
    uint16_t m_wNumAvailableChannels;
    int16_t  m_nNumChannels;
    int16_t  m_anNumChannelsInSlot[MAX_NUM_AUDIO_CHANNELS];
    float    m_afChannelVolumes[MAX_NUM_AUDIO_CHANNELS];
    float    m_afUnkn[MAX_NUM_AUDIO_CHANNELS];
    float    m_afChannelsFrqScalingFactor[MAX_NUM_AUDIO_CHANNELS];
    float    m_fMusicMasterScalingFactor;
    float    m_fEffectMasterScalingFactor;
    float    m_fMusicFaderScalingFactor;
    float    m_fEffectsFaderScalingFactor;
    float    m_fStreamFaderScalingFactor;
    float    m_fNonStreamFaderScalingFactor;
    float    field_428;
    float    field_42C;
    int16_t  m_aBankSlotIds[MAX_NUM_SOUNDS];
    int16_t  m_aSoundIdsInSlots[MAX_NUM_SOUNDS];
    int16_t  m_anVirtualChannelSoundLoopStartTimes[MAX_NUM_SOUNDS];
    int16_t  m_anVirtualChannelSoundLengths[MAX_NUM_SOUNDS];
    uint8_t  m_nBassSet;
    uint8_t  __pad1__[3];
    float    m_fBassEqGain;
    struct CAEMP3BankLoader* m_pMP3BankLoader;
    void*                    m_pMP3TrackLoader;
    IDirectSound8*    m_pDirectSound;
    void*                    m_dwSpeakerConfig;
    void*                    m_n3dEffectsQueryResult;
    DSCAPS                   m_dsCaps;
    IDirectSound3DListener* m_pDirectSound3dListener;
    void*                          m_pStreamingChannel;
    struct CAEStreamThread*        m_pStreamThread;
    uint8_t  gapE14[76];
    void*    m_aChannels[MAX_NUM_AUDIO_CHANNELS];
    uint32_t m_aBeatInfo[40];
    int32_t  field_1004;
    int32_t  field_1008;
    int32_t  field_100C;
    uint8_t  field_1010;
    int32_t  field_1014;

public:
    static void InjectHooks();

    CAEAudioHardware();

    // Return types aren't real, I've just copied the signatures for now
    void GetActualNumberOfHardwareChannels();
    void InitOpenALListener();
    void Initialise();
    void Terminate();
    void PlaySound(short channel, uint16_t channelSlot, uint16_t soundIdInSlot, uint16_t bankSlot, short playPosition, short flags, float speed);
    uint16_t GetNumAvailableChannels() { return m_wNumAvailableChannels; };
    void GetChannelPlayTimes(short channel, short* outArr);
    void SetChannelVolume(short channel, uint16_t channelSlot, float volume, uint8_t unused);
    void LoadSoundBank(uint16_t bankId, short bankSlotId);
    bool IsSoundBankLoaded(uint16_t bankId, short bankSlotId);
    void GetSoundBankLoadingStatus(uint16_t, short);
    void StopSound(short channel, uint16_t channelSlot);
    void SetChannelPosition(short channel, uint16_t channelSlot, CVector* vecPos, uint8_t unused);
    void SetChannelFrequencyScalingFactor(short channel, uint16_t channelSlot, float freqFactor);
    void RescaleChannelVolumes();
    void Service();
    void UpdateReverbEnvironment();
    float GetSoundHeadroom(uint16_t soundId, short bankSlotId);
    void EnableEffectsLoading();
    void DisableEffectsLoading();
    void RequestVirtualChannelSoundInfo(uint16_t soundIndex, uint16_t soundIdInSlot, uint16_t bankSlotId);
    void GetVirtualChannelSoundLengths(short* outArr);
    void GetVirtualChannelSoundLoopStartTimes(short* outArr);
    void LoadSound(uint16_t, uint16_t, short);
    void IsSoundLoaded(uint16_t, uint16_t, short);
    void GetSoundLoadingStatus(uint16_t, uint16_t, short);
    void PlayTrack(uint32_t, int, uint32_t, char, bool, bool);
    void StartTrackPlayback();
    void StopTrack();
    void GetTrackPlayTime();
    void GetTrackLengthMs();
    void GetActiveTrackID();
    void GetPlayingTrackID();
    void GetBeatInfo(struct tBeatInfo*);
    void SetBassSetting(signed char, float);
    void DisableBassEq();
    void EnableBassEq();
    void SetChannelFlags(short, uint16_t, short);
    void SetMusicMasterScalingFactor(float);
    void SetEffectsMasterScalingFactor(float);
    void SetMusicFaderScalingFactor(float);
    void SetEffectsFaderScalingFactor(float);
    void GetEffectsMasterScalingFactor();
    void GetMusicMasterScalingFactor();
    void GetEffectsFaderScalingFactor();
    void SetStreamFaderScalingFactor(float);
    void SetNonStreamFaderScalingFactor(float);
    void IsStreamingFromDVD();
    void GetDVDDriveLetter();
    void CheckDVD();
    void PauseAllSounds();
    void ResumeAllSounds();
    int16_t AllocateChannels(uint16_t numChannels);
};
VALIDATE_SIZE(CAEAudioHardware, 0x1018);

extern CAEAudioHardware& AEAudioHardware;
