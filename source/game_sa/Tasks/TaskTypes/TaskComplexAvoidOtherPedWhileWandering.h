#include "TaskComplex.h"
#include "TaskTimer.h"
#include "Vector.h"

class CColSphere;

class CTaskComplexAvoidOtherPedWhileWandering : public CTaskComplex {
public:
    CPed* m_ped;
    CVector field_10;
    CVector field_1C;
    CVector field_28;
    int32_t field_34;
    int32_t field_38;
    int32_t field_3C;
    CTaskTimer field_40;
    CTaskTimer field_4C;
    int32_t m_moveState; // see eMoveState
    int8_t m_flag1 : 1;
    int8_t m_flag2 : 1;
    int8_t m_flag3 : 1;
    int8_t m_flag4 : 1;
    char field_5D[3];

    static void InjectHooks();

    CTaskComplexAvoidOtherPedWhileWandering(CPed* ped, CVector* targetPoint, int32_t moveState);
    ~CTaskComplexAvoidOtherPedWhileWandering();
private:
    CTaskComplexAvoidOtherPedWhileWandering* Constructor(CPed* ped, CVector* targetPoint, int32_t moveState);
public:
    CTask* Clone() override;
    CTask* ControlSubTask(CPed* ped) override;
    eTaskType GetId() override { return TASK_COMPLEX_AVOID_OTHER_PED_WHILE_WANDERING; }
    bool MakeAbortable(CPed* ped, eAbortPriority priority, CEvent* event) override;
    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override;

    void QuitIK(CPed* ped);
    uint8_t NearbyPedsInSphere(CColSphere* colsphere, CPed* ped);
    void SetUpIK(CPed* ped);
    bool ComputeSphere(CPed* ped, CColSphere* colsphere, CPed** pedsToCheck, CPed** pedsInSphere);
    void ComputeAvoidSphere(CPed* ped, CColSphere* colsphere);
    bool ComputeDetourTarget(CPed* ped, CColSphere* colsphere);
    bool ComputeDetourTarget(CPed* ped);
};

VALIDATE_SIZE(CTaskComplexAvoidOtherPedWhileWandering, 0x60);
