#include "Player.h"

#include "RugbyScene.h"

#include "StateMachine.h"
#include "PlayerAction.h"
#include "PlayerCondition.h"

#include "Debug.h"

void Player::OnInitialize()
{
	mpStateMachine = new StateMachine<Player>(this, State::Count);

	mAreaIndex = -1;

	//SetTag(RugbyScene::Tag::PLAYER_A);

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

void Player::MakePass()
{
}

void Player::Move()
{
}

void Player::OnUpdate()
{
}

