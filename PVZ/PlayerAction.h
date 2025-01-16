#pragma once

#include "Action.h"
#include "Player.h"

class PlayerAction_Idle : public Action<Player>
{
public:
	void OnStart(Player* pPlayer) override;
	void OnUpdate(Player* pPlayer) override {};
	void OnEnd(Player* pPlayer) override {};
};

class PlayerAction_Attack : public Action<Player>
{
public:
	void OnStart(Player* pPlayer) override;
	void OnUpdate(Player* pPlayer) override {};
	void OnEnd(Player* pPlayer) override {};
};

class PlayerAction_Pass : public Action<Player>
{
public:
	void OnStart(Player* pPlayer) override {};
	void OnUpdate(Player* pPlayer) override {};
	void OnEnd(Player* pPlayer) override {};
};

class PlayerAction_Intercept : public Action<Player>
{
public:
	void OnStart(Player* pPlayer) override {};
	void OnUpdate(Player* pPlayer) override {};
	void OnEnd(Player* pPlayer) override {};
};

class PlayerAction_Follow : public Action<Player>
{
public:
	void OnStart(Player* pPlayer) override {};
	void OnUpdate(Player* pPlayer) override {};
	void OnEnd(Player* pPlayer) override {};
};

class PlayerAction_Retrieve : public Action<Player>
{
public:
	void OnStart(Player* pPlayer) override;
	void OnUpdate(Player* pPlayer) override {};
	void OnEnd(Player* pPlayer) override {};
};

