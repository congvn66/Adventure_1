#include "Player.h"

void Player::InitVal()
{
}

void Player::InitComponents()
{
}

Player::Player(float x, float y, Texture& textureSheet)
{
	this->InitVal();
	//create abilities????
	this->CreateMovementComponent(350.f,15.f,5.f);
	this->CreateAnimationComponent(textureSheet);
	this->InitComponents();

	this->SetPos(x, y);

	//add animation
	this->animationComponent->AddAnimation("IDLE_LEFT", 100.f, 0, 2, 3, 2, 42, 42);
	this->animationComponent->AddAnimation("WALK_LEFT", 100.f, 0, 1, 7, 1, 42, 42);
	this->animationComponent->AddAnimation("WALK_RIGHT", 100.f, 0, 0, 7, 0, 42, 42);
}

Player::~Player()
{
}

void Player::Update(const float& dt)
{
	//update pos with movement input
	this->movementComponent->Update(dt);

	//play animation with each state of the player
	if (this->movementComponent->GetState(IDLE)) {
		this->animationComponent->Play("IDLE_LEFT", dt);
	}
	else if (this->movementComponent->GetState(M_LEFT))
	{
		this->animationComponent->Play("WALK_LEFT", dt);
	}
	else if (this->movementComponent->GetState(M_RIGHT)) {
		this->animationComponent->Play("WALK_RIGHT", dt);
	}
	
}
