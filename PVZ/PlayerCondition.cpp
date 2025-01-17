#include "PlayerCondition.h"

bool PlayerCondition_NoBall::OnTest(Player* owner)
{
	return (owner->GetScene()->GetBall()->GetWhoHasBall() == 3);
}

bool PlayerCondition_HasBall::OnTest(Player* owner)
{
	if (owner->GetBall() == nullptr)
		return false;
	else
		return true;
}

bool PlayerCondition_FriendHasBall::OnTest(Player* owner)
{
	if (owner->GetScene()->GetBall()->GetWhoHasBall() == 0)
		return false;

	return (owner->GetTag() == owner->GetScene()->GetBall()->GetWhoHasBall());
}

bool PlayerCondition_FoeHasBall::OnTest(Player* owner)
{
	if (owner->GetScene()->GetBall()->GetWhoHasBall() == 0)
		return false;

	return (owner->GetTag() != owner->GetScene()->GetBall()->GetWhoHasBall());
}

bool PlayerCondition_IsStuck::OnTest(Player* owner)
{
	if (owner->GetBall()) {
		sf::Vector2f posAdv = owner->GetNearestPlayer()->GetPosition();
		sf::Vector2f posAdv = owner->GetPosition();
		if (owner->GetDistanceNearestAdvPlayer() != -1 && owner->GetDistanceNearestAdvPlayer() < owner->GetRadius() * 2)
			return true;
	}
	return false;
}