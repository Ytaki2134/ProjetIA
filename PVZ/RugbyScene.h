#pragma once

#include "GameManager.h"

#include <list>
#define PLAYER_COUNT 5
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
	int GetClickedArea(int x, int y) const;
	void TrySetSelectedEntity(Player* pEntity, int x, int y);


public:
	enum Tag
	{
		TEAM_A,
		TEAM_B,
		BALL,
	};

	Zone mAreas[3];

	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;

	//bool IsZombieInArea(int index) const;
	//void OnDestroyZombie(int lane);
};

