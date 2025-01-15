#pragma once

#include "Condition.h"
#include "Player.h"

class PlayerCondition_NoBall : public Condition<Player>
{
public:
	bool OnTest(Player* owner) override;
};

class PlayerCondition_HasBall : public Condition<Player>
{
public:
	bool OnTest(Player* owner) override;
};

class PlayerCondition_FriendHasBall : public Condition<Player>
{
public:
	bool OnTest(Player* owner) override;
};

class PlayerCondition_FoeHasBall : public Condition<Player>
{
public:
	bool OnTest(Player* owner) override;
};

class PlayerCondition_IsStuck : public Condition<Player>
{
public:
	bool OnTest(Player* owner) override;
};

