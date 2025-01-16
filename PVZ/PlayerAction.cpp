#include "PlayerAction.h"
#include "Globals.h"

#include <iostream>
#include "Utils.h"

void PlayerAction_Attack::OnStart(Player* pPlayer)
{

	float goalSize = GOALSIZE;
	float windowWidth = WINDOWWIDTH;

	//TEAM A - Goes to Right Side
	if (pPlayer->GetTag() == 0)
	{
		pPlayer->SetTarget(sf::Vector2f(windowWidth - goalSize, pPlayer->GetPosition().y));
	}

	//TEAM B - Goes to Left Side
	else if (pPlayer->GetTag() == 1)
	{
		pPlayer->SetTarget(sf::Vector2f(goalSize, pPlayer->GetPosition().y));
	}
}

void PlayerAction_Idle::OnStart(Player* pPlayer)
{
	pPlayer->SetTarget(pPlayer->GetPosition());
}

void PlayerAction_Pass::OnStart(Player* pPlayer)
{
}

void PlayerAction_Follow::OnUpdate(Player* pPlayer)
{
	sf::Vector2f playerPos = pPlayer->GetPosition();

	//TEAM A - Goes to LEFT/UP OR LEFT/DOWN
	if (pPlayer->GetTag() == 0)
	{
		//Check closest position
		sf::Vector2f leftUp(pPlayer->GetScene()->GetBall()->GetPosition().x - 50, pPlayer->GetScene()->GetBall()->GetPosition().y - 100);
		sf::Vector2f leftDown(pPlayer->GetScene()->GetBall()->GetPosition().x - 50, pPlayer->GetScene()->GetBall()->GetPosition().y + 100);

		if (Utils::GetDistance(playerPos.x, playerPos.y, leftUp.x, leftUp.y) < Utils::GetDistance(playerPos.x, playerPos.y, leftDown.x, leftDown.y))
			pPlayer->SetTarget(leftUp);
		else
			pPlayer->SetTarget(leftDown);
	}

	//TEAM B - Goes to RIGHT/UP OR RIGHT/DOWN
	if (pPlayer->GetTag() == 0)
	{
		//Check closest position
		sf::Vector2f rightUp(pPlayer->GetScene()->GetBall()->GetPosition().x + 50, pPlayer->GetScene()->GetBall()->GetPosition().y - 100);
		sf::Vector2f rightDown(pPlayer->GetScene()->GetBall()->GetPosition().x + 50, pPlayer->GetScene()->GetBall()->GetPosition().y + 100);

		if (Utils::GetDistance(playerPos.x, playerPos.y, rightUp.x, rightUp.y) < Utils::GetDistance(playerPos.x, playerPos.y, rightDown.x, rightDown.y))
			pPlayer->SetTarget(rightUp);
		else
			pPlayer->SetTarget(rightDown);
	}
}

void PlayerAction_Retrieve::OnUpdate(Player* pPlayer)
{
	pPlayer->SetTarget(pPlayer->GetScene()->GetBall()->GetPosition());
}

void PlayerAction_Intercept::OnUpdate(Player* pPlayer)
{
	pPlayer->SetTarget(pPlayer->GetScene()->GetBall()->GetPosition());
}
