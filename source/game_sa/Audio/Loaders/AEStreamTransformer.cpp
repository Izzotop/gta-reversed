#include "StdInc.h" // TODO: Remove

#include <cstring>

#include "AEStreamTransformer.h"

CAEStreamTransformer &CAEStreamTransformer::instance = *(CAEStreamTransformer *) 0xb612d8;

void CAEStreamTransformer::Initialise()
{
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallMethod<0x4f1750, CAEStreamTransformer*>(this);
#else
    static uint8_t t[] = {0xEA, 0x3A, 0xC4, 0xA1, 0x9A, 0xA8, 0x14, 0xF3, 0x48, 0xB0, 0xD7, 0x23, 0x9D, 0xE8, 0xFF, 0xF1};
    memcpy(table, t, sizeof(t));
#endif
}

void CAEStreamTransformer::TransformBuffer(void *buffer, size_t size, uint32_t position)
{
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallMethod<0x4f17d0, CAEStreamTransformer*, void*, size_t, uint32_t>(this, buffer, size, position);
#else
    uint8_t *buf = reinterpret_cast<uint8_t *> (buffer);

    for (size_t i = 0; i < size; i++)
        buf[i] ^= table[(position + i) & 0xF];
#endif
}

void CAEStreamTransformer::InjectHooks()
{
    HookInstall(0x4f1750, &CAEStreamTransformer::Initialise);
    HookInstall(0x4f17d0, &CAEStreamTransformer::TransformBuffer);
}
