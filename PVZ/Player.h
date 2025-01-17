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
	Player* mNearestPlayer = nullptr;
	Player* mNearestAdvPlayer = nullptr;
	bool mStun;
	float mTimeStun;
	float mBeginStun;

	bool mHasBall;
	int mAreaIndex;

public:
	void SetAreaIndex(int index) { mAreaIndex = index; }
	const char* GetStateName(State state) const;
	int GetAreaIndex() const;

	Player* GetNearestPlayer() { return mNearestPlayer; };
	float GetDistanceNearestAdvPlayer();
	void TryNearestPlayer(Player* player);
	void TryNearestAdvPlayer(Player* player);

	void Move();
	bool IsStun() { return mStun; };
	bool IsBoost() { return mBoost; }
	void SetBoost(bool boost) { mBoost = boost; };
	void SetBall(Ball* ball);
	void SetHasBall(bool HasBall);
	bool GetHasBall() { return mHasBall; };
	void SetScene(RugbyScene* scene);

	void SetTarget(sf::Vector2f target);
	sf::Vector2f GetTargetPosition() {return mTarget.position;};
	float GetDistanceTarget() {return mTarget.distance;};
	bool TargetIsSet() { return mTarget.isSet; };
	void DeleteTarget();

	void MakeAPassTo(Player* );
	void MakeAPass();

	int GetTag() { return mTag; }
	float GetSpeed();
	Ball* GetBall();
	RugbyScene* GetScene();

	void ReStart();
	
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

