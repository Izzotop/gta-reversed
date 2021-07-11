/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include <cstdio>

// For backward compatibility
typedef FILE* FILESTREAM;
constexpr size_t DIRNAMELENGTH = 128;

class CFileMgr {
public:
    // variables
    // length: 128
    static char* ms_dirName;
    // length: 128
    static char* ms_rootDirName;
    // functions
    static void Initialise();
    static int ChangeDir(const char* path);
    static int SetDir(const char* path);
    static int SetDirMyDocuments();
    static size_t LoadFile(const char* path, unsigned char* buf, size_t size, const char* mode);
    static FILESTREAM OpenFile(const char* path, const char* mode);
    static FILESTREAM OpenFileForWriting(const char* path);
    static FILESTREAM OpenFileForAppending(const char* path);
    static size_t Read(FILESTREAM file, void* buf, size_t size);
    static size_t Write(FILESTREAM file, const void* buf, size_t size);
    static bool Seek(FILESTREAM file, long offset, int origin);
    static bool ReadLine(FILESTREAM file, char* str, int num);
    static int CloseFile(FILESTREAM file);
    static int GetFileLength(FILESTREAM file);
    static int Tell(FILESTREAM file);
    static bool GetErrorReadWrite(FILESTREAM file);

private:
    friend void InjectHooksMain();
    static void InjectHooks();
};
