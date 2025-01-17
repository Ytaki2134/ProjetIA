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
	pPlayer->MakeAPass();
}

void PlayerAction_Follow::OnUpdate(Player* pPlayer)
{
	sf::Vector2f playerPos = pPlayer->GetPosition();
	Zone playerZone = pPlayer->GetScene()->mAreas[pPlayer->GetAreaIndex()];


	//TEAM A - Goes to LEFT/UP OR LEFT/DOWN
	if (pPlayer->GetTag() == 0 && pPlayer->GetBall() == nullptr)
	{

		if (pPlayer->GetScene()->GetBall()->GetPlayerWhoHasBall()->GetPosition().x <= pPlayer->GetPosition().x)
		{
			
			sf::Vector2f leftUp(pPlayer->GetScene()->GetBall()->GetPlayerWhoHasBall()->GetPosition().x + 50, pPlayer->GetScene()->GetBall()->GetPlayerWhoHasBall()->GetPosition().y - 100);
			sf::Vector2f leftDown(pPlayer->GetScene()->GetBall()->GetPlayerWhoHasBall()->GetPosition().x + 50, pPlayer->GetScene()->GetBall()->GetPlayerWhoHasBall()->GetPosition().y + 100);
			sf::Vector2f Front(pPlayer->GetScene()->GetBall()->GetPlayerWhoHasBall()->GetPosition().x + 50, pPlayer->GetScene()->GetBall()->GetPlayerWhoHasBall()->GetPosition().y);

			if (Utils::GetDistance(playerPos.x, playerPos.y, leftUp.x, leftUp.y) < Utils::GetDistance(playerPos.x, playerPos.y, leftDown.x, leftDown.y) && leftUp.y < playerZone.yMin)
				pPlayer->SetTarget(leftUp);
			else if (leftDown.y > playerZone.yMax)
				pPlayer->SetTarget(leftDown);
			else
				pPlayer->SetTarget(Front);
		}	
		else {
			sf::Vector2f leftUp(pPlayer->GetScene()->GetBall()->GetPlayerWhoHasBall()->GetPosition().x - 50, pPlayer->GetScene()->GetBall()->GetPlayerWhoHasBall()->GetPosition().y - 100);
			sf::Vector2f leftDown(pPlayer->GetScene()->GetBall()->GetPlayerWhoHasBall()->GetPosition().x - 50, pPlayer->GetScene()->GetBall()->GetPlayerWhoHasBall()->GetPosition().y + 100);
			sf::Vector2f Back(pPlayer->GetScene()->GetBall()->GetPlayerWhoHasBall()->GetPosition().x - 50, pPlayer->GetScene()->GetBall()->GetPlayerWhoHasBall()->GetPosition().y );

			if (Utils::GetDistance(playerPos.x, playerPos.y, leftUp.x, leftUp.y) < Utils::GetDistance(playerPos.x, playerPos.y, leftDown.x, leftDown.y) && leftUp.y < playerZone.yMin)
				pPlayer->SetTarget(leftUp);
			else if(leftDown.y > playerZone.yMax)
				pPlayer->SetTarget(leftDown);
			else
				pPlayer->SetTarget(Back);
		}
		//Check closest position

	}

	//TEAM B - Goes to RIGHT/UP OR RIGHT/DOWN
	if (pPlayer->GetTag() == 1 && pPlayer->GetBall() == nullptr)
	{

		if (pPlayer->GetScene()->GetBall()->GetPlayerWhoHasBall()->GetPosition().x >= pPlayer->GetPosition().x)
		{
			sf::Vector2f rightUp(pPlayer->GetScene()->GetBall()->GetPlayerWhoHasBall()->GetPosition().x - 50, pPlayer->GetScene()->GetBall()->GetPlayerWhoHasBall()->GetPosition().y - 100);
			sf::Vector2f rightDown(pPlayer->GetScene()->GetBall()->GetPlayerWhoHasBall()->GetPosition().x - 50, pPlayer->GetScene()->GetBall()->GetPlayerWhoHasBall()->GetPosition().y + 100);
			sf::Vector2f Front(pPlayer->GetScene()->GetBall()->GetPlayerWhoHasBall()->GetPosition().x - 50, pPlayer->GetScene()->GetBall()->GetPlayerWhoHasBall()->GetPosition().y);

			if (Utils::GetDistance(playerPos.x, playerPos.y, rightUp.x, rightUp.y) < Utils::GetDistance(playerPos.x, playerPos.y, rightDown.x, rightDown.y) && rightUp.y < playerZone.yMin)
				pPlayer->SetTarget(rightUp);
			else if (rightDown.y> playerZone.yMax)
				pPlayer->SetTarget(rightDown);
			else
				pPlayer->SetTarget(Front);
		}
		else {
			sf::Vector2f rightUp(pPlayer->GetScene()->GetBall()->GetPlayerWhoHasBall()->GetPosition().x + 50, pPlayer->GetScene()->GetBall()->GetPlayerWhoHasBall()->GetPosition().y - 100);
			sf::Vector2f rightDown(pPlayer->GetScene()->GetBall()->GetPlayerWhoHasBall()->GetPosition().x + 50, pPlayer->GetScene()->GetBall()->GetPlayerWhoHasBall()->GetPosition().y + 100);
			sf::Vector2f Back(pPlayer->GetScene()->GetBall()->GetPlayerWhoHasBall()->GetPosition().x + 50, pPlayer->GetScene()->GetBall()->GetPlayerWhoHasBall()->GetPosition().y);

			if (Utils::GetDistance(playerPos.x, playerPos.y, rightUp.x, rightUp.y) < Utils::GetDistance(playerPos.x, playerPos.y, rightDown.x, rightDown.y) && rightUp.y < playerZone.yMin)
				pPlayer->SetTarget(rightUp);
			else if(rightDown.y > playerZone.yMax)
				pPlayer->SetTarget(rightDown);
			else
				pPlayer->SetTarget(Back);
		}
		
	}
	std::cout << pPlayer->GetTag() << ":  " << pPlayer->GetTarget()->position.x << " ,"<< pPlayer->GetTarget()->position.y << std::endl;
}

void PlayerAction_Retrieve::OnUpdate(Player* pPlayer)
{
	Zone playerZone = pPlayer->GetScene()->mAreas[pPlayer->GetAreaIndex()];
	sf::Vector2f target = sf::Vector2f(pPlayer->GetScene()->GetBall()->GetPosition().x, (playerZone.yMin > pPlayer->GetScene()->GetBall()->GetPosition().y) ? playerZone.yMin : (playerZone.yMax < pPlayer->GetScene()->GetBall()->GetPosition().y) ? playerZone.yMax : pPlayer->GetScene()->GetBall()->GetPosition().y);
	pPlayer->SetTarget(target);
}

void PlayerAction_Intercept::OnUpdate(Player* pPlayer)
{
	Zone playerZone = pPlayer->GetScene()->mAreas[pPlayer->GetAreaIndex()];
	sf::Vector2f target = sf::Vector2f(pPlayer->GetScene()->GetBall()->GetPosition().x, (playerZone.yMin > pPlayer->GetScene()->GetBall()->GetPosition().y) ? playerZone.yMin : (playerZone.yMax < pPlayer->GetScene()->GetBall()->GetPosition().y) ? playerZone.yMax : pPlayer->GetScene()->GetBall()->GetPosition().y);
	pPlayer->SetTarget(target);
}
