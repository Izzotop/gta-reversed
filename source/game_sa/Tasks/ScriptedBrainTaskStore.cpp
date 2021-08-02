#include "StdInc.h"

CScriptedBrainTaskEntry (&CScriptedBrainTaskStore::ms_entries)[TOTAL_SCRIPTED_BRAIN_TASK_ENTRIES] = *(CScriptedBrainTaskEntry(*)[TOTAL_SCRIPTED_BRAIN_TASK_ENTRIES])0xC188F0;

void CScriptedBrainTaskEntry::InjectHooks() { HookInstall(0x62EC40, &CScriptedBrainTaskEntry::Constructor); }

void CScriptedBrainTaskStore::InjectHooks() {
    CScriptedBrainTaskEntry::InjectHooks();

    ReversibleHooks::Install("CScriptedBrainTaskStore", "SetTask", 0x635720, &CScriptedBrainTaskStore::SetTask);
    ReversibleHooks::Install("CScriptedBrainTaskStore", "GetTask", 0x6357C0, &CScriptedBrainTaskStore::GetTask);
    ReversibleHooks::Install("CScriptedBrainTaskStore", "Clear_ped", 0x635850, (void(*)(CPed*)) & CScriptedBrainTaskStore::Clear);
    ReversibleHooks::Install("CScriptedBrainTaskStore", "Clear_task", 0x6357F0, (void(*)(CTask*)) & CScriptedBrainTaskStore::Clear);
}

CScriptedBrainTaskEntry::CScriptedBrainTaskEntry() {
    m_ped = nullptr;
    m_task = nullptr;
}

// 0x62EC40
CScriptedBrainTaskEntry* CScriptedBrainTaskEntry::Constructor() {
    this->CScriptedBrainTaskEntry::CScriptedBrainTaskEntry();
    return this;
}

// 0x635720
CTask* CScriptedBrainTaskStore::SetTask(CPed* ped, CTask* task) {
    int32_t freeEntryIndex = -1;
    for (int32_t i = 0; i < TOTAL_SCRIPTED_BRAIN_TASK_ENTRIES; i++) {
        CScriptedBrainTaskEntry& entry = ms_entries[i];
        if (!entry.m_ped && freeEntryIndex == -1)
            freeEntryIndex = i;
        if (entry.m_ped == ped) {
            delete entry.m_task;
            entry.m_task = task;
            return task;
        }
    }
    if (freeEntryIndex == -1) {
        delete task;
        return nullptr;
    }
    CScriptedBrainTaskEntry& entry = ms_entries[freeEntryIndex];
    entry.m_ped = ped;
    ped->RegisterReference(reinterpret_cast<CEntity**>(&entry.m_ped));
    delete entry.m_task;
    entry.m_task = task;
    return task;
}

// 0x6357C0
CTask* CScriptedBrainTaskStore::GetTask(CPed* ped) {
    for (int32_t i = 0; i < TOTAL_SCRIPTED_BRAIN_TASK_ENTRIES; i++) {
        CScriptedBrainTaskEntry& entry = ms_entries[i];
        if (entry.m_ped == ped)
            return entry.m_task;
    }
    return nullptr;
}

// 0x635850
void CScriptedBrainTaskStore::Clear(CPed* ped) {
    for (int32_t i = 0; i < TOTAL_SCRIPTED_BRAIN_TASK_ENTRIES; i++) {
        CScriptedBrainTaskEntry& entry = ms_entries[i];
        if (entry.m_ped == ped) {
            delete entry.m_task;
            entry.m_task = nullptr;
            if (entry.m_ped)
                entry.m_ped->CleanUpOldReference(reinterpret_cast<CEntity**>(&entry.m_ped));
            entry.m_ped = nullptr;
            return;
        }
    }
}

// 0x6357F0
void CScriptedBrainTaskStore::Clear(CTask* task) {
    for (int32_t i = 0; i < TOTAL_SCRIPTED_BRAIN_TASK_ENTRIES; i++) {
        CScriptedBrainTaskEntry& entry = ms_entries[i];
        if (entry.m_task == task) {
            delete entry.m_task;
            entry.m_task = nullptr;
            if (entry.m_ped)
                entry.m_ped->CleanUpOldReference(reinterpret_cast<CEntity**>(&entry.m_ped));
            entry.m_ped = nullptr;
            return;
        }
    }
}
