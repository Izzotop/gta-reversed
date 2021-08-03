/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

template <typename ObjectType, unsigned int Capacity>
class CStore {
public:
    uint32_t   m_nCount;
    ObjectType m_aObjects[Capacity];

    CStore() {
        m_nCount = 0;
    }

    inline ObjectType& GetItemAtIndex(uint32_t index) { return m_aObjects[index]; }
    inline ObjectType& AddItem() {
        auto& pObj = m_aObjects[m_nCount];
        ++m_nCount;
        return pObj;
    }
};
