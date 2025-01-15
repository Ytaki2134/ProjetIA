#include "Player.h"
#include "Ball.h"
#include "RugbyScene.h"

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
}

void Player::OnUpdate()
{
}

void Player::OnCollision(Entity* pCollidedWith)
{
    if (!pCollidedWith->IsTag(mTag) && !pCollidedWith->IsTag(RugbyScene::Tag::BALL)) {
        Player* advPlayer = dynamic_cast<Player*>(pCollidedWith);
        if (advPlayer!=nullptr && mGetBall) {
            SetGetBall(false);
//            GoToPosition(advPlayer->GetDirection().x , advPlayer->GetDirection().x, 10000.f);
            mBall->SetPlayer(advPlayer);
            advPlayer->SetGetBall(true);
        }
    }
}

