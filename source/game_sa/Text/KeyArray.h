#pragma once

struct CKeyEntry {
    char*    string; // relative to TKEY block; need to call update after reading
    uint32_t hash;   // name hash
};

// TKEY block
class CKeyArray {
public:
    CKeyEntry* data;
    uint32_t   size;

public:
    CKeyArray();
    ~CKeyArray();

    void Unload();
    void Load(uint32_t length, FILESTREAM file, uint32_t* offset, uint8_t nSkipBytes);

    void /* inline */ Update(char* offset);

    CKeyEntry* BinarySearch(uint32_t key, CKeyEntry* entries, short firstIndex, short lastIndex);
    char* Search(const char* key, bool* found);
};
