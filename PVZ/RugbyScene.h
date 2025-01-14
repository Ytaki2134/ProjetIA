#pragma once

#include "GameManager.h"

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

	int GetClickedArea(int x, int y) const;
public:
	enum Tag
	{
		PLAYER_A,
		PLAYER_B,
		BALL,
	};

	int mLaneCount[3] = { 0,0,0 };
	Zone mAreas[3];

	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;

	//bool IsZombieInArea(int index) const;
	//void OnDestroyZombie(int lane);
};

