#include "TaskComplex.h"
#include "Vector.h"

class CPointRoute;
class CTaskComplexWalkRoundObject : public CTaskComplex {
public:
    int32_t m_moveState;
    CVector m_targetPoint;
    CEntity* m_object;
    CPointRoute* m_pointRoute;
    int32_t field_24;
    int32_t field_28;
    int8_t field_2C;
    int8_t field_2D;
    int32_t field_30;

    static void InjectHooks();

    CTaskComplexWalkRoundObject(int32_t moveState, CVector* targetPoint, CEntity* object);
    ~CTaskComplexWalkRoundObject();
private:
    CTaskComplexWalkRoundObject* Constructor(int32_t moveState, CVector* targetPoint, CEntity* object);
public:
    CTask* Clone() override { return new CTaskComplexWalkRoundObject(m_moveState,&m_targetPoint, m_object); }
    eTaskType  GetId() override { return TASK_COMPLEX_WALK_ROUND_OBJECT; }
    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed* ped) override;
public:
    CTask* CreateRouteTask(CPed* ped);

};

VALIDATE_SIZE(CTaskComplexWalkRoundObject, 0x34);
