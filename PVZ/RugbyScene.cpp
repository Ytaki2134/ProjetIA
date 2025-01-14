#include "RugbyScene.h"
#include "Player.h"

#include "Debug.h"


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

	float playerRadius = height * 0.025f;

	float playerStartY = height / (PLAYER_COUNT * 2.f);
	float playerGapY = height / (float)PLAYER_COUNT;




	for (int i = 0; i < PLAYER_COUNT * 2; i++)
	{
		if (i < PLAYER_COUNT) {
			float plantStartX = width * 0.05f;

			pPlayer[i] = CreateEntity<Player>(playerRadius, sf::Color::Green);
			pPlayer[i]->SetPosition(plantStartX, playerStartY, 0.f, 0.5f);
			pPlayer[i]->SetAreaIndex((i ==2)?1:(i<3)?0:2);
			playerStartY += playerGapY;
		}
		else
		{
			if(i==PLAYER_COUNT)
				playerStartY = height / (PLAYER_COUNT * 2.f);
			float playerStartX =  width * 0.95f;

			pPlayer[i] = CreateEntity<Player>(playerRadius, sf::Color::Red);
			pPlayer[i]->SetPosition(playerStartX, playerStartY, 0.f, 0.5f);
			pPlayer[i]->SetAreaIndex((i == 7) ?1 : (i < 7) ? 0 : 2);
			playerStartY += playerGapY;
		}

	}
	int xMin = 1;
	int yMin =1;
	int xMax = width-1;
	int yMax =height/2-1;
	for (int i = 0; i < 3; i++) {
		mAreas[i] = { xMin, yMin, xMax, yMax  };
		yMin += height / 4;
		yMax += height / 4;
	}
	

}

void RugbyScene::OnEvent(const sf::Event& event)
{
	if (event.type != sf::Event::EventType::MouseButtonPressed)
		return;

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
			int minY = mAreas[pEntitySelected->GetAreaIndex()].yMin ;
			int maxY = mAreas[pEntitySelected->GetAreaIndex()].yMax ;
			int pos_y = event.mouseButton.y;
			pEntitySelected->GoToPosition(event.mouseButton.x,(pos_y<minY)?minY:(pos_y>maxY)?maxY:pos_y, 100.f);
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
}



