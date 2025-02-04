#include "PlayerCondition.h"

bool PlayerCondition_NoBall::OnTest(Player* owner)
{
	return (owner->GetScene()->GetBall()->GetWhoHasBall() == 3);
}

bool PlayerCondition_HasBall::OnTest(Player* owner)
{
	return owner->GetHasBall();
}

bool PlayerCondition_FriendHasBall::OnTest(Player* owner)
{
	if (owner->GetScene()->GetBall()->GetWhoHasBall() == 2)
		return false;

	return (owner->GetTag() == owner->GetScene()->GetBall()->GetWhoHasBall());
}

bool PlayerCondition_FoeHasBall::OnTest(Player* owner)
{
	if (owner->GetScene()->GetBall()->GetWhoHasBall() == 2)
		return false;

	return (owner->GetTag() != owner->GetScene()->GetBall()->GetWhoHasBall());
}

bool PlayerCondition_IsStuck::OnTest(Player* owner)
{
	if (owner->GetBall()) {
		if (owner->GetDistanceNearestAdvPlayer() != -1 && owner->GetDistanceNearestAdvPlayer() < owner->GetRadius() * 3)
			return true;
	}
	return false;
}