#include "PlayerAction.h"
#include "Globals.h"

#include <iostream>

void PlayerAction_Attack::OnStart(Player* pPlayer)
{
	std::cout << "ATTACK START" << std::endl;

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

void PlayerAction_Retrieve::OnStart(Player* pPlayer)
{
	std::cout << "RETRIEVE START" << std::endl;

	pPlayer->SetTarget(pPlayer->GetScene()->GetBall()->GetPosition());
}

void PlayerAction_Idle::OnStart(Player* pPlayer)
{
	std::cout << "IDLE START" << std::endl;
}
