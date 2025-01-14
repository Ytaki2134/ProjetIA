#include "RugbyScene.h"
#include "Player.h"
#include "Debug.h"

#define PLAYER_COUNT 5
int RugbyScene::GetClickedArea(int x, int y) const
{
	return 0;
}

void RugbyScene::OnInitialize()
{

	int width = GetWindowWidth();
	int height = GetWindowHeight();

	float playerRadius = height * 0.025f;

	float playerStartY = height / (PLAYER_COUNT * 2.f);
	float playerGapY = height / (float)PLAYER_COUNT;


	Player* pPlayer[PLAYER_COUNT * 2];

	for (int i = 0; i < PLAYER_COUNT * 2; i++)
	{
		if (i < PLAYER_COUNT) {
			float plantStartX = width * 0.05f;

			pPlayer[i] = CreateEntity<Player>(playerRadius, sf::Color::Green);
			pPlayer[i]->SetPosition(plantStartX, playerStartY, 0.f, 0.5f);
			pPlayer[i]->SetAreaIndex((i ==3)?2:(i<3)?1:3);
			playerStartY += playerGapY;
		}
		else
		{
			if(i==5)
				playerStartY = height / (PLAYER_COUNT * 2.f);
			float plantStartX =  width * 0.95f;

			pPlayer[i] = CreateEntity<Player>(playerRadius, sf::Color::Red);
			pPlayer[i]->SetPosition(plantStartX, playerStartY, 0.f, 0.5f);
			pPlayer[i]->SetAreaIndex((i == 7) ? 2 : (i < 7) ? 1 : 3);
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
}

void RugbyScene::OnUpdate()
{
	for (int i = 0; i < 3; i++)
	{
		const Zone& aabb = mAreas[i];

		Debug::DrawRectangle(aabb.xMin, aabb.yMin, aabb.xMax - aabb.xMin, aabb.yMax - aabb.yMin, sf::Color::Red);
	}
}



