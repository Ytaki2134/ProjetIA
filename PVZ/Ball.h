#pragma once
#include "Entity.h"
#include "Header.h"

class Player;

class Ball: public Entity 
{
private:
	Player* mPlayer = nullptr;
	Team mWhoHasBall = NOBODY;
protected:
	void OnInitialize() override;
	void OnUpdate() override;
	void OnCollision(Entity* pCollidedWith) override;
public:
	void SetPlayer(Player* player);
	Team GetWhoHasBall() {return mWhoHasBall;};
};

