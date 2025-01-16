#include "RugbyScene.h"
#include "Player.h"
#include "Ball.h"

#include "Debug.h"
#include <iostream>

int RugbyScene::GetClickedArea(int x, int y) const
{
	return 0;
}

void RugbyScene::TrySetSelectedEntity(Player* pEntity, int x, int y)
{
	if (pEntity->IsInside(x, y) == false)
		return;

	pEntitySelected = pEntity;
}

void RugbyScene::OnInitialize()
{

	int width = GetWindowWidth();
	int height = GetWindowHeight();

	playerRadius = height * 0.025f;

	float playerStartX = width * 0.05f;
	float playerStartY = height / (PLAYER_COUNT * 2.f);
	float playerGapY = height / (float)PLAYER_COUNT;
	float multiplyx = 0;

	for (int i = 0; i < PLAYER_COUNT * 2; i++)
	{
		if (i < PLAYER_COUNT) {
			pPlayer[i] = CreateEntity<Player>(playerRadius, sf::Color::Green);
			pPlayer[i]->SetTag(Tag::TEAM_A);
			pPlayer[i]->SetPosition(playerStartX * lineX[i], playerStartY * lineY[i], 0.f, 0.5f);

			pPlayer[i]->SetAreaIndex((i == 2) ? 1 : (i < 3) ? 0 : 2);
			playerStartY += playerGapY;
		}
		else
		{
			pPlayer[i] = CreateEntity<Player>(playerRadius, sf::Color::Red);
			pPlayer[i]->SetTag(Tag::TEAM_B);
			pPlayer[i]->SetPosition(width - pPlayer[i - PLAYER_COUNT]->GetPosition().x, pPlayer[i - PLAYER_COUNT]->GetPosition().y, 0.f, 0.5f);
			pPlayer[i]->SetAreaIndex((i == 7) ? 1 : (i < 7) ? 0 : 2);
		}
		pPlayer[i]->SetScene(this);
	}

	int xMin = 1;
	int yMin = 1;
	int xMax = width - 1;
	int yMax = height / 2 - 1;
	for (int i = 0; i < 3; i++) {
		mAreas[i] = { xMin, yMin, xMax, yMax };
		yMin += height / 4;
		yMax += height / 4;
	}

	mBall = CreateEntity<Ball>(height * 0.015f, sf::Color::Blue);
	mBall->SetPosition(width / 2, height / 2, 0.f, 0.5f);
}

void RugbyScene::OnEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed) {
		// Vérifier si la touche pressée est la barre d'espace
		if (event.key.code == sf::Keyboard::Space) {
			if (mBall->GetPlayerWhoHasBall() != nullptr) {
				mBall->GetPlayerWhoHasBall()->MakeAPass();
			}
		}
	}
	//if (event.type != sf::Event::EventType::MouseButtonPressed)
	//	return;

	if (event.mouseButton.button == sf::Mouse::Button::Right)
	{
		for (auto player : pPlayer) {
			TrySetSelectedEntity(player, event.mouseButton.x, event.mouseButton.y);
		}
	}

	if (event.mouseButton.button == sf::Mouse::Button::Left)
	{
		if (pEntitySelected != nullptr)
		{
			int minY = mAreas[pEntitySelected->GetAreaIndex()].yMin;
			int maxY = mAreas[pEntitySelected->GetAreaIndex()].yMax;
			int pos_y = event.mouseButton.y;
			Player* player = dynamic_cast<Player*>(pEntitySelected);
			//player->GoToPosition(event.mouseButton.x, (pos_y < minY) ? minY : (pos_y > maxY) ? maxY : pos_y, player->GetSpeed());
			player->SetTarget(sf::Vector2f(event.mouseButton.x, (pos_y < minY) ? minY : (pos_y > maxY) ? maxY : pos_y));
		}
	}
}

void RugbyScene::OnUpdate()
{
	for (int i = 0; i < 3; i++)
	{
		const Zone& aabb = mAreas[i];
		Debug::DrawRectangle(aabb.xMin, aabb.yMin, aabb.xMax - aabb.xMin, aabb.yMax - aabb.yMin, sf::Color::Red);
	}
	if (mBall->GetPlayerWhoHasBall() != nullptr) {
		for (auto player : pPlayer) {
			if (mBall->GetPlayerWhoHasBall() != player) {
				if(mBall->GetPlayerWhoHasBall()->GetTag() == player->GetTag())
					mBall->GetPlayerWhoHasBall()->TryNearestPlayer(player);
				else
					mBall->GetPlayerWhoHasBall()->TryNearestAdvPlayer(player);

			}
		}
	}

}

Ball* RugbyScene::GetBall()
{
	return mBall;
}

Player* RugbyScene::isPointTouchingPass(sf::Vector2f a, sf::Vector2f b, int tag) {
	Player* p = nullptr;
	sf::Vector2f posp;
	for (auto player : pPlayer) {
		if (tag != player->GetTag()) {

			sf::Vector2f ab = b - a;
			sf::Vector2f ap = player->GetPosition() - a;

			float abLengthSquared = ab.x * ab.x + ab.y * ab.y;
			float dotProduct = (ap.x * ab.x + ap.y * ab.y) / abLengthSquared;

			if (dotProduct < 0)continue;
			if (dotProduct > 1)continue;

			sf::Vector2f projection = a + dotProduct * ab;
			float dx = player->GetPosition().x - projection.x;
			float dy = player->GetPosition().y - projection.y;
			float distanceSquared = dx * dx + dy * dy;

			if (distanceSquared <= playerRadius * playerRadius) {
				p= player;
			}
		}
	}
	return p;
}
