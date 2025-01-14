#pragma once
#include "Entity.h"


template<typename T>
class StateMachine;

class Player : public Entity
{
	StateMachine<Player>* mpStateMachine;
	
	enum State
	{
	// a faire plus tard
	};

	int mSpeed;
	int mMaxSpeed = 6;

	bool mGetBall;
	int mAreaIndex;

public:
	void SetAreaIndex(int index) { mAreaIndex = index; }
	const char* GetStateName(State state) const;
	int GetAreaIndex() const;

	void MakePass();
	void Move();

protected:
	void OnInitialize() override;
	void OnUpdate() override;



	// -> follow proces below  
	

	//friend class PlantAction_Idle;
	//friend class PlantAction_Reloading;
	//friend class PlantAction_Shooting;

	//friend class PlantCondition_FullAmmo;
	//friend class PlantCondition_NoAmmo;
	//friend class PlantCondition_ZombieOnLane;





};

