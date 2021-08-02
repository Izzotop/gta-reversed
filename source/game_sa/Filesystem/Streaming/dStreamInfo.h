#pragma once

#include <Windows.h>
#include "Queue.h"

enum class eCdStreamStatus : int32_t
{
    READING_SUCCESS = 0,
    WAITING_TO_READ = 250,
    READING_FAILURE = 254,
    READING = 255,
};

union SyncObj
{
    HANDLE hSemaphore;
    CONDITION_VARIABLE cv;
};

struct CdStream
{
    uint32_t nSectorOffset;
    uint32_t nSectorsToRead;
    LPVOID lpBuffer;
    BYTE field_C;
    bool bLocked;
    bool bInUse;
    BYTE field_F;
    eCdStreamStatus status;
    SyncObj sync;
    HANDLE hFile;
    OVERLAPPED overlapped;
};

struct CdStreamInfoSA
{
    DWORD streamCreateFlags;
    BOOL streamingInitialized;
    BOOL overlappedIO;
    Queue m_queue;
    CdStream* pStreams;
    DWORD thread_id;
    HANDLE semaphore;
    HANDLE thread;
    HANDLE streamHandles[32];
    DWORD streamCount;
    DWORD openStreamCount;
    CHAR  streamNames[2048];
    DWORD field_8A8;
    DWORD lastPosn;
    DWORD field_8B0;
    DWORD field_8B4;
    DWORD gtaint_id;
    DWORD gta3_id;
};

VALIDATE_SIZE(SyncObj, sizeof(HANDLE));
VALIDATE_SIZE(CdStreamInfoSA, 0x8CC);
VALIDATE_SIZE(CdStream, 0x30);

const int32_t MAX_CD_STREAM_HANDLES = 32;
const int32_t MAX_CD_STREAM_IMAGE_NAME_SIZE = 64;

extern HANDLE(&gStreamFileHandles)[MAX_CD_STREAM_HANDLES];
extern char(&gCdImageNames)[MAX_CD_STREAM_HANDLES][MAX_CD_STREAM_IMAGE_NAME_SIZE];
extern uint32_t& gStreamFileCreateFlags;
extern CdStream*& gCdStreams;
extern int32_t& gStreamCount;
extern int32_t& gOpenStreamCount;
extern int32_t& gStreamingInitialized;
extern int32_t& gOverlappedIO;
extern Queue& gStreamQueue;
extern HANDLE& gStreamSemaphore;
extern HANDLE& gStreamingThread;
extern DWORD& gStreamingThreadId;
extern uint32_t& gLastCdStreamPosn;

void InjectCdStreamHooks();
int32_t __cdecl CdStreamOpen(const char* lpFileName);
eCdStreamStatus __cdecl CdStreamSync(int32_t streamId);
eCdStreamStatus __cdecl CdStreamGetStatus(int32_t streamId);
bool __cdecl CdStreamRead(int32_t streamId, uint8_t* lpBuffer, uint32_t offsetAndHandle, int32_t sectorCount);
static uint32_t __cdecl CdStreamGetLastPosn() { return gLastCdStreamPosn; }
[[noreturn]] DWORD WINAPI CdStreamThread(LPVOID lpParam);
void __cdecl CdStreamInitThread();
void __cdecl CdStreamInit(int32_t streamCount);
void __cdecl CdStreamRemoveImages();
void __cdecl CdStreamShutdown();
