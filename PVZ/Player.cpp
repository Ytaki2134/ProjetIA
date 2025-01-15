#include "Player.h"
#include "Ball.h"
#include "RugbyScene.h"
#include <iostream>

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

void Player::SetGetBall(bool getball)
{
    mGetBall = getball;
}

void Player::SetTeamGetBall(bool getball)
{
    mTeamGetBall = getball;
}


void Player::OnInitialize()
{
    SetRigidBody(true);
    mTimeStun =5;
}

void Player::OnUpdate()
{
    if (mStun) {
        mBeginStun += GetDeltaTime();
    }
}

void Player::OnCollision(Entity* pCollidedWith)
{    
    
    if (!pCollidedWith->IsTag(mTag) && !pCollidedWith->IsTag(RugbyScene::Tag::BALL)) {
        Player* advPlayer = dynamic_cast<Player*>(pCollidedWith);
        if (advPlayer!=nullptr && mGetBall && !advPlayer->IsStun())
        {
//            GoToPosition(advPlayer->GetDirection().x , advPlayer->GetDirection().x, 10000.f);
            if(mBall !=nullptr)
                mBall->SetPlayer(pCollidedWith);
            if (mStun && (GetDeltaTime() - mBeginStun) > mTimeStun) {
                mStun = false;
            }
            else if (!mStun) {
                mStun = true;
                mBeginStun = GetDeltaTime();
            }

        }
    }
    else if (pCollidedWith->IsTag(RugbyScene::Tag::BALL) && !mGetBall) {
        mBall = dynamic_cast<Ball*>(pCollidedWith);
    }
}

