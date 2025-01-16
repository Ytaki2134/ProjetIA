#include "Player.h"
#include "Ball.h"
#include "RugbyScene.h"
#include <iostream>

#include "StateMachine.h"
#include "PlayerAction.h"
#include "PlayerCondition.h"

#include "Debug.h"
#include "Utils.h"
#include <iostream>

void Player::OnInitialize()
{
	mSpeed = 100;
	mBoostSpeed = 100;
	mTimeBoost = 1;
	mAreaIndex = -1;
	mTimeStun = 1;
	SetRigidBody(true);


	mpStateMachine = new StateMachine<Player>(this, State::Count);
	//IDLE
	{
		Action<Player>* pIdle = mpStateMachine->CreateAction<PlayerAction_Idle>(State::Idle);

		//-> ATTACK
		{
			auto transition = pIdle->CreateTransition(State::Attack);

			auto condition = transition->AddCondition<PlayerCondition_HasBall>();
		}

		//-> INTERCEPT
		{
			auto transition = pIdle->CreateTransition(State::Intercept);

			transition->AddCondition<PlayerCondition_FoeHasBall>();
		}

		//-> FOLLOW
		{
			auto transition = pIdle->CreateTransition(State::Follow);

			transition->AddCondition<PlayerCondition_FriendHasBall>();
		}

		//-> RETRIEVE
		{
			auto transition = pIdle->CreateTransition(State::Retrieve);

			transition->AddCondition<PlayerCondition_NoBall>(false);
			transition->AddCondition<PlayerCondition_FriendHasBall>(false);
			transition->AddCondition<PlayerCondition_FoeHasBall>(false);
		}
	}

	//ATTACK
	{
		Action<Player>* pAttack = mpStateMachine->CreateAction<PlayerAction_Attack>(State::Attack);

		//-> IDLE
		{
			auto transition = pAttack->CreateTransition(State::Idle);

			transition->AddCondition<PlayerCondition_NoBall>();
		}

		//-> PASS
		{
			auto transition = pAttack->CreateTransition(State::Pass);

			transition->AddCondition<PlayerCondition_IsStuck>();
		}
	}

	//PASS
	{
		Action<Player>* pPass = mpStateMachine->CreateAction<PlayerAction_Pass>(State::Pass);

		//-> FOLLOW
		{
			auto transition = pPass->CreateTransition(State::Follow);

			transition->AddCondition<PlayerCondition_FriendHasBall>();
		}

		//-> INTERCEPT
		{
			auto transition = pPass->CreateTransition(State::Intercept);

			transition->AddCondition<PlayerCondition_FoeHasBall>();
		}

		//-> RETRIEVE
		{
			auto transition = pPass->CreateTransition(State::Retrieve);

			transition->AddCondition <PlayerCondition_FriendHasBall>(false);
			transition->AddCondition <PlayerCondition_FoeHasBall>(false);
		}
	}

	//INTERCEPT
	{
		Action<Player>* pIntercept = mpStateMachine->CreateAction<PlayerAction_Pass>(State::Intercept);

		//->IDLE
		{
			auto transition = pIntercept->CreateTransition(State::Idle);

			transition->AddCondition<PlayerCondition_NoBall>();
		}

		//->ATTACK
		{
			auto transition = pIntercept->CreateTransition(State::Attack);

			transition->AddCondition<PlayerCondition_HasBall>();
		}

		//->FOLLOW
		{
			auto transition = pIntercept->CreateTransition(State::Follow);

			transition->AddCondition<PlayerCondition_FriendHasBall>();
		}

		//->RETRIEVE
		{
			auto transition = pIntercept->CreateTransition(State::Retrieve);

			transition->AddCondition<PlayerCondition_FriendHasBall>(false);
			transition->AddCondition<PlayerCondition_FoeHasBall>(false);
		}
	}

	//FOLLOW
	{
		Action<Player>* pFollow = mpStateMachine->CreateAction<PlayerAction_Pass>(State::Follow);

		//->IDLE
		{
			auto transition = pFollow->CreateTransition(State::Idle);

			transition->AddCondition<PlayerCondition_NoBall>();
		}

		//->ATTACK
		{
			auto transition = pFollow->CreateTransition(State::Attack);

			transition->AddCondition<PlayerCondition_HasBall>();
		}

		//->INTERCEPT
		{
			auto transition = pFollow->CreateTransition(State::Intercept);

			transition->AddCondition<PlayerCondition_FoeHasBall>();
		}

		//->RETRIEVE
		{
			auto transition = pFollow->CreateTransition(State::Retrieve);

			transition->AddCondition<PlayerCondition_FriendHasBall>(false);
			transition->AddCondition<PlayerCondition_FoeHasBall>(false);
		}
	}

	//RETRIEVE
	{
		Action<Player>* pRetrieve = mpStateMachine->CreateAction<PlayerAction_Pass>(State::Retrieve);

		//->IDLE
		{
			auto transition = pRetrieve->CreateTransition(State::Idle);

			transition->AddCondition<PlayerCondition_NoBall>();
		}

		//->ATTACK
		{
			auto transition = pRetrieve->CreateTransition(State::Attack);

			transition->AddCondition<PlayerCondition_HasBall>();
		}

		//->INTERCEPT
		{
			auto transition = pRetrieve->CreateTransition(State::Intercept);

			transition->AddCondition<PlayerCondition_FoeHasBall>();
		}

		//->FOLLOW
		{
			auto transition = pRetrieve->CreateTransition(State::Follow);

			transition->AddCondition<PlayerCondition_FriendHasBall>();
		}
	}

	mpStateMachine->SetState(State::Idle);
}

const char* Player::GetStateName(State state) const
{
	return nullptr;
}

int Player::GetAreaIndex() const
{
	return mAreaIndex;
}



void Player::TryNearestPlayer(Player* player)
{
	if (mNearestPlayer != nullptr) {
		float distactual = Utils::GetDistance(GetPosition().x, GetPosition().y, mNearestPlayer->GetPosition().x, mNearestPlayer->GetPosition().y);
		float distTest = Utils::GetDistance(GetPosition().x, GetPosition().y, player->GetPosition().x, player->GetPosition().y);
		if (distTest < distactual)
			mNearestPlayer = player;
	}
	else {
		mNearestPlayer = player;
	}
}

void Player::Move()
{
}

void Player::SetBall(Ball* ball)
{
	mBall = ball;

	if (ball != nullptr)
		SetHasBall(true);
	else
		SetHasBall(false);
}

void Player::SetHasBall(bool getball)
{
	mHasBall = getball;
}

void Player::SetScene(RugbyScene* scene)
{
	mScene = scene;
}

void Player::SetTarget(sf::Vector2i target)
{
	mTarget.position = target;
	float dist = Utils::GetDistance(target.x, GetPosition().x, target.y, GetPosition().y);
	mTarget.distance = dist;
	mTarget.isSet = true;
}


void Player::DeleteTarget()
{
	mTarget.position = sf::Vector2f(-1, -1);
	mTarget.distance = -1;
	mTarget.isSet = false;
}

void Player::MakeAPassTo(Player* advPlayer)
{
	mBall->SetPlayer(advPlayer);
	advPlayer->SetBall(mBall);
	SetBall(nullptr);
}

void Player::MakeAPass()
{
	bool passCorect = false;
	switch (mNearestPlayer->GetTag())
	{
	case 0:
		(mNearestPlayer->GetPosition().x < GetPosition().x) ? passCorect = true : passCorect = false;
		break;
	case 1:
		(mNearestPlayer->GetPosition().x > GetPosition().x) ? passCorect = true : passCorect = false;
		break;
	default:
		break;
	}
	if (passCorect) {
		mBall->SetPlayer(mNearestPlayer);
		mNearestPlayer->SetBall(mBall);
		SetBall(nullptr);
	}
}

float Player::GetSpeed()
{
	if (mBoost) {
		return mSpeed + mBoostSpeed;
	}
	else {

		return mSpeed;
	}
}

Ball* Player::GetBall()
{
	return mBall;
}

RugbyScene* Player::GetScene()
{
	return mScene;
}

void Player::OnUpdate()
{
	if (mBoost) {
		mBeginBoost += GetDeltaTime();
		if (mBeginBoost > mTimeBoost) {
			mBoost = false;
			mBeginBoost = 0;
		}
	}

	if (mStun) {
		mBeginStun += GetDeltaTime();
		if (mBeginStun > mTimeStun) {
			mStun = false;
			mBeginStun = 0;
		}
	}
	if (GetPosition().x != mTarget.position.x && GetPosition().y != mTarget.position.y && mTarget.isSet)
		GoToPosition(mTarget.position.x, mTarget.position.y, GetSpeed());
	else
		DeleteTarget();
	if (mHasBall) {
		Debug::DrawLine(GetPosition().x, GetPosition().y, mNearestPlayer->GetPosition().x, mNearestPlayer->GetPosition().y, sf::Color::Cyan);
	}

	mpStateMachine->Update();
}

void Player::OnCollision(Entity* pCollidedWith)
{
	if (!mStun) {

		if (!pCollidedWith->IsTag(mTag) && !pCollidedWith->IsTag(RugbyScene::Tag::BALL)) {
			Player* advPlayer = dynamic_cast<Player*>(pCollidedWith);
			if (advPlayer != nullptr && mHasBall && !advPlayer->IsStun())
			{

				mBall->SetPlayer(advPlayer);
				advPlayer->SetBall(mBall);
				advPlayer->SetBoost(true);
				SetBall(nullptr);
				mStun = true;
				mBeginStun = GetDeltaTime();

			}
		}
		else if (pCollidedWith->IsTag(RugbyScene::Tag::BALL) && !mHasBall) {
			mBall = dynamic_cast<Ball*>(pCollidedWith);
		}

	}

}

