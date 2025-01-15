#pragma once

#include "GameManager.h"
#include "Header.h"

#include <list>

class Player;
class Ball;

namespace sf
{
	class Event;
}


struct Zone
{
	int xMin;
	int yMin;
	int xMax;
	int yMax;
};
class RugbyScene: public Scene
{
private:
	Player* pPlayer[PLAYER_COUNT * 2];
	Player* pEntitySelected;
	Ball* mBall;

	int GetClickedArea(int x, int y) const;
	void TrySetSelectedEntity(Player* pEntity, int x, int y);


public:
	enum Tag
	{
		TEAM_A,
		TEAM_B,
		BALL,
		NOBALL
	};

	float lineX[5] = {0.5f,2,3,2,0.5f};
	float lineY[5] = {1,0.5f,1,1.25f,1};

	Zone mAreas[3];
	
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
	Ball* GetBall();

	//bool IsZombieInArea(int index) const;
	//void OnDestroyZombie(int lane);
};

