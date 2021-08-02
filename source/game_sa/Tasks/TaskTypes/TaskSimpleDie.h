#include "TaskSimple.h"

class CAnimBlendHierarchy;
class CAnimBlendAssociation;

class CTaskSimpleDie : public CTaskSimple
{
    int32_t m_animGroupId;
    int32_t m_animId;
    CAnimBlendHierarchy* m_animHierarchy;
    uint32_t m_animFlags;
    float m_blendDelta;
    float m_animSpeed;
    uint8_t m_flags;
private:
    uint8_t padding[3];
public:
    CAnimBlendAssociation* m_animAssociation;
};

VALIDATE_SIZE(CTaskSimpleDie, 0x28);
