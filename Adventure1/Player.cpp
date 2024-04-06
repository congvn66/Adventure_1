#include "stdafx.h"
#include "Player.h"

void Player::InitVal()
{
	this->attacking = false;
}

void Player::InitComponents()
{
}

Player::Player(float x, float y, Texture& textureSheet)
{
	this->InitVal();
	//create abilities????
	this->CreateHitboxComponent(this->sprite,42.f*1.5,10.f, 42.f ,42.f*4-20);
	this->CreateMovementComponent(350.f,15.f,5.f);
	this->CreateAnimationComponent(textureSheet);
	this->InitComponents();

	this->SetPos(x, y);

	//add animation
	this->animationComponent->AddAnimation("IDLE", 80.f, 0, 0, 3, 0, 42, 42);
	this->animationComponent->AddAnimation("WALK", 80.f, 0, 1, 7, 1, 42, 42);
	this->animationComponent->AddAnimation("ATTACK", 50.f, 0, 3, 9, 3, 80,42);
}

Player::~Player()
{
}

void Player::UpdateAttack()
{
	
}

void Player::UpdateAnimation(const float& dt)
{
	if (Mouse::isButtonPressed(Mouse::Left)) {
		this->attacking = true;
	}
	if (this->attacking) {
		this->animationComponent->Play("ATTACK", dt, true);
		if (this->animationComponent->IsDone("ATTACK")) {
			this->attacking = false;
		}
	}
	//play animation with each state of the player
	if (this->movementComponent->GetState(IDLE)) {
		this->animationComponent->Play("IDLE", dt);
	}
	else if (this->movementComponent->GetState(M_RIGHT))
	{
		this->sprite.setOrigin(0.f, 0.f);
		this->sprite.setScale(4.f, 4.f);
		this->animationComponent->Play("WALK", dt, this->movementComponent->GetVelocity().x, this->movementComponent->GetMaxSpeed());
	}
	else if (this->movementComponent->GetState(M_LEFT)) {
		this->sprite.setOrigin(42.f, 0.f);
		this->sprite.setScale(-4.f, 4.f);
		this->animationComponent->Play("WALK", dt, this->movementComponent->GetVelocity().x, this->movementComponent->GetMaxSpeed());
	}
	else if (this->movementComponent->GetState(M_UP)) {
		this->animationComponent->Play("WALK", dt, this->movementComponent->GetVelocity().x, this->movementComponent->GetMaxSpeed());
	}
	else if (this->movementComponent->GetState(M_DOWN)) {
		this->animationComponent->Play("WALK", dt, this->movementComponent->GetVelocity().x, this->movementComponent->GetMaxSpeed());
	}
}

void Player::Update(const float& dt)
{
	//update pos with movement input
	this->movementComponent->Update(dt);

	this->UpdateAttack();
	
	this->UpdateAnimation(dt);
	
	this->hitboxComponent->Update();

}
