#include "PlayerCondition.h"

bool PlayerCondition_NoBall::OnTest(Player* owner)
{
    return false;
}

bool PlayerCondition_HasBall::OnTest(Player* owner)
{
    return false;
}

bool PlayerCondition_FriendHasBall::OnTest(Player* owner)
{
    return false;
}

bool PlayerCondition_FoeHasBall::OnTest(Player* owner)
{
    return false;
}

bool PlayerCondition_IsStuck::OnTest(Player* owner)
{
    return false;
}