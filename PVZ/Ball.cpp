#include "Ball.h"
#include "RugbyScene.h"
#include <iostream>

void Ball::OnInitialize()
{
	SetTag(RugbyScene::Tag::BALL);
}

void Ball::OnUpdate()
{
	sf::Vector2f position = GetPosition(0.f, 0.f);

	int width = GetScene()->GetWindowWidth();
	int height = GetScene()->GetWindowHeight();

	if (position.x > width || position.x < 0)
		Destroy();
	if (position.y > height || position.y < 0)
		Destroy();
}

void Ball::OnCollision(Entity* pCollidedWith)
{
	if (pCollidedWith->IsTag(RugbyScene::Tag::TEAM_A))
	{
		std::cout << "hit" << std::endl;
		//Destroy();
	}
	else if (pCollidedWith->IsTag(RugbyScene::Tag::TEAM_B))
	{
		std::cout << "hit" << std::endl;
		//Destroy();
	}
}
