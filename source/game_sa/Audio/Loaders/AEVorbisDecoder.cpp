#include "StdInc.h" // TODO: Remove

#include "AEVorbisDecoder.h"

ov_callbacks CAEVorbisDecoder::staticCallbacks = {
    &CAEVorbisDecoder::ReadCallback,
    &CAEVorbisDecoder::SeekCallback,
    &CAEVorbisDecoder::CloseCallback,
    &CAEVorbisDecoder::TellCallback
};

// 0x5026b0
CAEVorbisDecoder::CAEVorbisDecoder(CAEDataStream* dataStream, int userTrack)
: CAEStreamingDecoder(dataStream)
, callbacks(staticCallbacks)
, vorbisFileHandle(nullptr)
, initialized(false)
, isUserTrack(static_cast<bool> (userTrack))
, _dataStreamCopy(dataStream)
, vorbisInfo(nullptr)
{
}

// 0x5023f0
CAEVorbisDecoder::~CAEVorbisDecoder()
{
    if (vorbisFileHandle)
    {
        ov_clear(vorbisFileHandle);
        delete vorbisFileHandle;
        vorbisFileHandle = nullptr;
    }
}

// 0x5024d0
bool CAEVorbisDecoder::Initialise()
{
    vorbisFileHandle = new OggVorbis_File();
    if (ov_open_callbacks(dataStream, vorbisFileHandle, nullptr, 0, callbacks) != 0)
        return false;

    vorbisInfo = ov_info(vorbisFileHandle, -1);

    // Not support channels > 2
    if (vorbisInfo->channels > 2)
        return false;

    initialized = true;

    if (isUserTrack)
    {
        if (GetStreamLengthMs() < 7000)
            return initialized = false;
    }

    return true;
}

// 0x502470
size_t CAEVorbisDecoder::FillBuffer(void *dest, size_t size)
{
    size_t readedTotal = 0;
    char *buffer = reinterpret_cast<char *> (dest);

    // In case of mono stream, only read half of it
    if (vorbisInfo->channels == 1)
        size /= 2;

    if (size > 0)
    {
        int dummy;

        while (readedTotal < size)
        {
            long readed = ov_read(vorbisFileHandle, buffer + readedTotal, size - readedTotal, 0, sizeof(int16_t), 1, &dummy);
            if (readed <= 0)
                break;

            readedTotal += static_cast<size_t> (readed);
        }
    }

    if (vorbisInfo->channels == 1)
    {
        // Duplicate channel data
        int16_t *bufShort = reinterpret_cast<int16_t *> (buffer);

        for (int i = static_cast<int> (readedTotal / sizeof(int16_t)) - 1; i >= 0; i--)
            bufShort[i * 2] = bufShort[i * 2 + 1] = bufShort[i];

        readedTotal *= 2;
    }

    return readedTotal;
}

// 0x502610
long CAEVorbisDecoder::GetStreamLengthMs()
{
    if (initialized)
    {
        double length = ov_time_total(vorbisFileHandle, -1);
        return (long) (length * 1000.0);
    }

    return -1;
}

// 0x502640
long CAEVorbisDecoder::GetStreamPlayTimeMs()
{
    if (initialized)
    {
        double length = ov_time_tell(vorbisFileHandle);
        return (long) (length * 1000.0);
    }

    return -1;
}

// 0x502670
void CAEVorbisDecoder::SetCursor(unsigned long pos)
{
    if (initialized)
        ov_time_seek(vorbisFileHandle, pos * 0.001);
}

// 0x502560
int CAEVorbisDecoder::GetSampleRate()
{
    return initialized ? static_cast<int> (vorbisInfo->rate) : -1;
}

// 0x502460
int CAEVorbisDecoder::GetStreamID()
{
    return dataStream->m_nTrackId;
}

// 0x502580
size_t CAEVorbisDecoder::ReadCallback(void *ptr, size_t size, size_t nmemb, void *opaque)
{
    if (opaque == nullptr)
        return 0;

    CAEDataStream *dataStream = reinterpret_cast<CAEDataStream *> (opaque);
    return dataStream->FillBuffer(ptr, size * nmemb) / size;
}

// 0x5025d0
int CAEVorbisDecoder::CloseCallback(void *opaque)
{
    if (opaque == nullptr)
        return -1;

    CAEDataStream *dataStream = reinterpret_cast<CAEDataStream *> (opaque);
    return dataStream->Close();
}

// 0x5025b0
int CAEVorbisDecoder::SeekCallback(void *opaque, ogg_int64_t offset, int whence)
{
    if (opaque == nullptr)
        return -1;

    CAEDataStream *dataStream = reinterpret_cast<CAEDataStream *> (opaque);
    unsigned long result = dataStream->Seek(static_cast<long> (offset), whence);

    return static_cast<int> (result);
}

// 0x5025f0
long CAEVorbisDecoder::TellCallback(void *opaque)
{
    if (opaque == nullptr)
        return -1;

    CAEDataStream *dataStream = reinterpret_cast<CAEDataStream *> (opaque);

    return static_cast<int> (dataStream->GetCurrentPosition());
}

void CAEVorbisDecoder::InjectHooks()
{
    ReversibleHooks::Install("CAEVorbisDecoder", "CAEVorbisDecoder", 0x5026b0, &CAEVorbisDecoder::ctor);
    ReversibleHooks::Install("CAEVorbisDecoder", "~CAEVorbisDecoder", 0x5023f0, &CAEVorbisDecoder::dtor);
    ReversibleHooks::Install("CAEVorbisDecoder", "GetStreamID", 0x502460, &CAEVorbisDecoder::GetStreamID);
    ReversibleHooks::Install("CAEVorbisDecoder", "FillBuffer", 0x502470, &CAEVorbisDecoder::FillBuffer);
    ReversibleHooks::Install("CAEVorbisDecoder", "Initialise", 0x5024d0, &CAEVorbisDecoder::Initialise);
    ReversibleHooks::Install("CAEVorbisDecoder", "GetSampleRate", 0x502560, &CAEVorbisDecoder::GetSampleRate);
    ReversibleHooks::Install("CAEVorbisDecoder", "ReadCallback", 0x502580, &CAEVorbisDecoder::ReadCallback);
    ReversibleHooks::Install("CAEVorbisDecoder", "CloseCallback", 0x5025d0, &CAEVorbisDecoder::CloseCallback);
    ReversibleHooks::Install("CAEVorbisDecoder", "SeekCallback", 0x5025b0, &CAEVorbisDecoder::SeekCallback);
    ReversibleHooks::Install("CAEVorbisDecoder", "TellCallback", 0x5025f0, &CAEVorbisDecoder::TellCallback);
    ReversibleHooks::Install("CAEVorbisDecoder", "GetStreamLengthMs", 0x502610, &CAEVorbisDecoder::GetStreamLengthMs);
    ReversibleHooks::Install("CAEVorbisDecoder", "GetStreamPlayTimeMs", 0x502640, &CAEVorbisDecoder::GetStreamPlayTimeMs);
    ReversibleHooks::Install("CAEVorbisDecoder", "SetCursor", 0x502670, &CAEVorbisDecoder::SetCursor);
}

CAEVorbisDecoder* CAEVorbisDecoder::ctor(CAEDataStream* dataStream, int unknown) {
    this->CAEVorbisDecoder::CAEVorbisDecoder(dataStream, unknown);
    return this;
}

CAEVorbisDecoder* CAEVorbisDecoder::dtor() {
    this->CAEVorbisDecoder::~CAEVorbisDecoder();
    return this;
}
