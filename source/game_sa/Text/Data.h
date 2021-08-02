#pragma once

// TDAT block
class CData {
public:
    char*    data;
    uint32_t size;

public:
    CData();
    ~CData();

    void Unload();
    void Load(uint32_t length, FILESTREAM file, uint32_t* offset, uint8_t nSkipBytes);
};
