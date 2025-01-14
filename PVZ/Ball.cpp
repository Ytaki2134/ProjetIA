#include "Ball.h"
#include "Player.h"
#include "RugbyScene.h"
#include <iostream>

void Ball::OnInitialize()
{
	mPlayer = nullptr;
	SetTag(RugbyScene::Tag::BALL);
	sf::Vector2f position = GetPosition(0.f, 0.f);

	int width = GetScene()->GetWindowWidth();
	int height = GetScene()->GetWindowHeight();

	if (position.x > width || position.x < 0)
		Destroy();
	if (position.y > height || position.y < 0)
		Destroy();
}

void Ball::OnUpdate()
{
	if (mPlayer != nullptr) {
		SetPosition(mPlayer->GetPosition().x, mPlayer->GetPosition().y);
	}
}

void Ball::OnCollision(Entity* pCollidedWith)
{
	if ((pCollidedWith->IsTag(RugbyScene::Tag::TEAM_A) || pCollidedWith->IsTag(RugbyScene::Tag::TEAM_B))&& pCollidedWith!=mPlayer)
	{
		Player* player = dynamic_cast<Player*>(pCollidedWith);
		if (player != nullptr)
		{
			mPlayer=player; // Utilise SetPlayer pour g�rer le pointeur
			mPlayer->SetGetBall(true);
		}
	}
}

void Ball::SetPlayer(Player* player)
{
	//mPlayer = player;
	std::cout << "change" << std::endl;
}
