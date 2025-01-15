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
	bool mStun;
	float mTimeStun;
	float mBeginStun;
	bool mHasBall;
	int mAreaIndex;

public:
	void SetAreaIndex(int index) { mAreaIndex = index; }
	const char* GetStateName(State state) const;
	int GetAreaIndex() const;

	void MakePass();
	void Move();
	bool IsStun() { return mStun; }
	void SetBall(Ball* ball);
	void SetHasBall(bool HasBall);
	void MakeAPass();
	int GetTag() { return mTag; }

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

