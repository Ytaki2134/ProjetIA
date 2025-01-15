#pragma once
#include "Entity.h"
#include "Ball.h"
#include "RugbyScene.h"

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
	
	bool mBoost;
	float mBoostSpeed;
	float mTimeBoost;
	float mBeginBoost;

	Ball* mBall;
	RugbyScene* mScene;
	bool mStun;
	float mTimeStun;
	float mBeginStun;

	bool mHasBall;
	int mAreaIndex;

public:
	void SetAreaIndex(int index) { mAreaIndex = index; }
	const char* GetStateName(State state) const;
	int GetAreaIndex() const;

	bool IsStun() { return mStun; };
	void SetBoost(bool boost) { mBoost = boost; };
	void SetBall(Ball* ball);
	void SetHasBall(bool HasBall);
	void SetScene(RugbyScene* scene);

	sf::Vector2f GetTargetPosition() {return mTarget.position;};
	float GetDistanceTarget() {return mTarget.distance;};
	bool TargetIsSet() { return mTarget.isSet; };
	void DeleteTarget();

	void MakeAPassTo(Player* );

	int GetTag() { return mTag; }
	float GetSpeed();
	Ball* GetBall();
	RugbyScene* GetScene();

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

