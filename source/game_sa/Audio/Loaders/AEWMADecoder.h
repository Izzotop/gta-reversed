#pragma once

#include <cstdint>

// WMA
#include <wmsdkidl.h>
#include <wmsdk.h>

#include "AEStreamingDecoder.h"

class CAEWMADecoder : public CAEStreamingDecoder {
private:
    static constexpr size_t TEMPBUFSIZE = 131072;

    bool initialized;
    int _unknown;
    uint64_t sampleTime;
    uint64_t sampleDuration;
    char buffer[TEMPBUFSIZE];
    size_t tempBufferUsed;
    uint16_t streamNumber;
    int sampleRate;
    long lengthMs;
    IWMSyncReader* syncReader;
    int _unknown2;

    HRESULT SelectStreamIndex(IWMProfile* profile);

    static HRESULT(__stdcall*& WMCreateSyncReader)(IUnknown*, DWORD, IWMSyncReader**);
    static HMODULE& wmvCoreModule;

public:
    CAEWMADecoder(CAEDataStream* dataStream);
    ~CAEWMADecoder() override;

    bool Initialise() override;
    size_t FillBuffer(void* dest, size_t size) override;
    long GetStreamLengthMs() override;
    long GetStreamPlayTimeMs() override;
    void SetCursor(unsigned long pos) override;
    int GetSampleRate() override;
    int GetStreamID() override;

    static bool InitLibrary();
    static void Shutdown();

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CAEWMADecoder* ctor(CAEDataStream* dataStream);
    CAEWMADecoder* dtor();
};

VALIDATE_SIZE(CAEWMADecoder, 0x20038);
