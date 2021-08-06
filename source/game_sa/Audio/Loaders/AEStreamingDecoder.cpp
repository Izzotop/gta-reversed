#include "StdInc.h" // TODO: Remove

#include "AEStreamingDecoder.h"

// 0x4f2810
CAEStreamingDecoder::CAEStreamingDecoder(CAEDataStream* dataStream)
{
    dataStream = dataStream;
    if (dataStream)
        dataStream->Initialise();
}

#ifdef USE_DEFAULT_FUNCTIONS
void CAEStreamingDecoder::operator delete(void* mem)
{
    ((void(__thiscall *)(void*, int)) (0x4f2860))(mem, 1);
}
#endif

// 0x4f2830
CAEStreamingDecoder::~CAEStreamingDecoder()
{
    // The game checks if dataStream is nullptr, but
    // deleting null pointer is perfectly safe.
    delete dataStream;
    dataStream = nullptr;
}

void CAEStreamingDecoder::InjectHooks()
{
    ReversibleHooks::Install("CAEStreamingDecoder", "CAEStreamingDecoder", 0x4f2810, &CAEStreamingDecoder::ctor);
    ReversibleHooks::Install("CAEStreamingDecoder", "~CAEStreamingDecoder", 0x4f2830, &CAEStreamingDecoder::dtor);
}

CAEStreamingDecoder* CAEStreamingDecoder::ctor(CAEDataStream* dataStream) {
    this->CAEStreamingDecoder::CAEStreamingDecoder(dataStream);
    return this;
}

CAEStreamingDecoder* CAEStreamingDecoder::dtor() {
    this->CAEStreamingDecoder::~CAEStreamingDecoder();
    return this;
}