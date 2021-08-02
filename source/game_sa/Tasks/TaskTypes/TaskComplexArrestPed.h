#include "TaskComplex.h"

class CVehicle;

class CTaskComplexArrestPed : public CTaskComplex {
public:
    bool      m_subTaskNeedsToBeCreated;
    CPed*     m_pedToArrest;
    int32_t   field_14;
    int32_t   field_18;
    int32_t   field_1C;
    CVehicle* m_vehicle;

public:
    static void InjectHooks();

    CTaskComplexArrestPed(CPed* ped);
    ~CTaskComplexArrestPed();

    CTask* Clone() override { return new CTaskComplexArrestPed(m_pedToArrest); }
    eTaskType GetId() override { return TASK_COMPLEX_ARREST_PED; }
    bool MakeAbortable(CPed* ped, eAbortPriority priority, CEvent* event) override;
    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed* ped) override;
    CTask* CreateSubTask(int32_t taskId, CPed* ped);

private:
    CTaskComplexArrestPed* Constructor(CPed* ped);

};

VALIDATE_SIZE(CTaskComplexArrestPed, 0x24);
