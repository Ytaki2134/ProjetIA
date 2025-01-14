#pragma once
#include "Entity.h"
#include "Ball.h"


template<typename T>
class StateMachine;

class Player : public Entity
{
	StateMachine<Player>* mpStateMachine;
	
	enum State
	{
		Idle,
		Attack,
		Pass,
		Intercept,
		Follow,
		Retrieve,

		Count
	};

	int mSpeed;
	int mMaxSpeed = 6;

	Ball* mBall;
	Player* playerHit;
	bool mGetBall;
	bool mTeamGetBall;
	int mAreaIndex;

public:
	void SetAreaIndex(int index) { mAreaIndex = index; }
	const char* GetStateName(State state) const;
	int GetAreaIndex() const;

	void MakePass();
	void Move();
	void SetGetBall(bool getball);
	void SetTeamGetBall(bool getball);



protected:
	void OnInitialize() override;
	void OnUpdate() override;
	void OnCollision(Entity* pCollidedWith) override;



	// -> follow proces below  
	

	//friend class PlantAction_Idle;
	//friend class PlantAction_Reloading;
	//friend class PlantAction_Shooting;

	//friend class PlantCondition_FullAmmo;
	//friend class PlantCondition_NoAmmo;
	//friend class PlantCondition_ZombieOnLane;





};

