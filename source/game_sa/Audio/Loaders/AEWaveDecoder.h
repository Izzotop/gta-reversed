#pragma once

#include <cstdint>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <MMReg.h> // WAVEFORMAT

#include "AEStreamingDecoder.h"

class CAEWaveDecoder : public CAEStreamingDecoder {
public:
    CAEWaveDecoder(CAEDataStream* dataStream);
    virtual ~CAEWaveDecoder();

    bool Initialise() override;
    size_t FillBuffer(void* dest, size_t size) override;
    long GetStreamLengthMs() override;
    long GetStreamPlayTimeMs() override;
    void SetCursor(unsigned long pos) override;
    int GetSampleRate() override;
    int GetStreamID() override;

private:
    bool initialized;
    CAEDataStream* _dataStreamCopy;

    // RIFF header
    union {
        struct {
            char riffFourCC[4];
            uint32_t fileSize;
            char waveFourCC[4];
            char fmtFourCC[4];
            uint32_t fmtChunkSize;
            uint16_t formatTag;
            uint16_t channelCount;
            uint32_t sampleRate;
            uint32_t bytesPerSecond;
            uint16_t blockAlign;
            uint16_t bitsPerSample;
            uint32_t dataPosition;
            uint32_t dataChunkSize;
        };
        char fileHeaderArray[44];
    };

private:
    friend void InjectHooksMain(void);

    CAEWaveDecoder* ctor(CAEDataStream* dataStream);
    void dtor();

    static void InjectHooks();
};

VALIDATE_SIZE(CAEWaveDecoder, 0x3c);
