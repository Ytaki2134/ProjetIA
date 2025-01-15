#pragma once
#include "Entity.h"

class Player;

class Ball: public Entity 
{
private:
	Player* mPlayer = nullptr;

protected:
	void OnInitialize() override;
	void OnUpdate() override;
	void OnCollision(Entity* pCollidedWith) override;
public:
	void SetPlayer(Entity* player);

};

