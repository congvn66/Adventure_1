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
	this->InitComponents();
	this->CreateHitboxComponent(this->sprite,40,10, 12*4,26*4); //hitbox
	this->CreateMovementComponent(350.f,1500.f,900.f); //move
	this->CreateAnimationComponent(textureSheet);     //animation
	this->CreateAttributeComponent(1);				//stats

	this->SetPos(x, y);

	//add animation
	this->animationComponent->AddAnimation("IDLE", 80.f, 0, 8, 4, 8, 32, 32);
	this->animationComponent->AddAnimation("WALK_LEFT", 80.f, 0, 2, 4, 2, 32, 32);
	this->animationComponent->AddAnimation("WALK_RIGHT", 80.f, 0, 3, 4, 3, 32, 32);
	this->animationComponent->AddAnimation("WALK_UP", 80.f, 0, 1, 4, 1, 32, 32);
	this->animationComponent->AddAnimation("WALK_DOWN", 80.f, 0, 0, 4, 0, 32, 32);
	this->animationComponent->AddAnimation("ATTACK", 50.f, 0, 4, 4, 4, 32,32);
}

Player::~Player()
{
}



void Player::UpdateAttack()
{
	if (Mouse::isButtonPressed(Mouse::Left))
	{
		//this->attacking = true;
	}
}
void Player::UpdateAnimation(const float& dt)
{
	this->UpdateAttack();
	if (this->attacking) {
		this->animationComponent->Play("ATTACK", dt, true);
		if (this->animationComponent->IsDone("ATTACK")) {
			this->attacking = false;
		}
	}
	//play animation with each state of the player
	if (this->movementComponent->GetState(IDLE)) {
		this->sprite.setScale(4.f, 4.f);
		this->animationComponent->Play("IDLE", dt);
	}
	else if (this->movementComponent->GetState(M_RIGHT))
	{
		this->sprite.setScale(4.f, 4.f);
		this->animationComponent->Play("WALK_RIGHT", dt, this->movementComponent->GetVelocity().x, this->movementComponent->GetMaxSpeed());
	}
	else if (this->movementComponent->GetState(M_LEFT)) {
		this->sprite.setScale(4.f, 4.f);
		this->animationComponent->Play("WALK_LEFT", dt, this->movementComponent->GetVelocity().x, this->movementComponent->GetMaxSpeed());
	}
	else if (this->movementComponent->GetState(M_UP)) {
		this->sprite.setScale(4.f, 4.f);
		this->animationComponent->Play("WALK_UP", dt, this->movementComponent->GetVelocity().x, this->movementComponent->GetMaxSpeed());
	}
	else if (this->movementComponent->GetState(M_DOWN)) {
		this->sprite.setScale(4.f, 4.f);
		this->animationComponent->Play("WALK_DOWN", dt, this->movementComponent->GetVelocity().x, this->movementComponent->GetMaxSpeed());
	}
}
AttributeComponent* Player::GetAttributeComponent()
{
	return this->attributeComponent;
}
void Player::LoseHP(const int hp)
{
	this->attributeComponent->hp -= hp;

	if (this->attributeComponent->hp < 0)
	{
		this->attributeComponent->hp = 0;
	}
}
void Player::LoseEXP(const int exp)
{
	this->attributeComponent->exp -= exp;

	if (this->attributeComponent->exp < 0)
	{
		this->attributeComponent->exp = 0;
	}
}
void Player::GainHP(const int hp)
{
	this->attributeComponent->hp += hp;

	if (this->attributeComponent->hp > this->attributeComponent->hpMax)
	{
		this->attributeComponent->hp = this->attributeComponent->hpMax;
	}
}
void Player::GainEXP(const int exp)
{
	this->attributeComponent->GainExp(exp);
}

void Player::Update(const float& dt)
{

	//update pos with movement input
	this->movementComponent->Update(dt);

	this->UpdateAttack();
	
	this->UpdateAnimation(dt);
	
	this->hitboxComponent->Update();

}

void Player::Render(RenderTarget& target, const bool showHitBox)
{
	target.draw(this->sprite);
	if (showHitBox)
	{
		this->hitboxComponent->Render(target);
	}
}
