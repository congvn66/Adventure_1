#include "Player.h"

void Player::InitVal()
{
}

void Player::InitComponents()
{
	this->CreateMovementComponent(350.f,15.f,5.f);
}

Player::Player(float x, float y, Texture& texture)
{
	this->InitVal();
	this->InitComponents();
	this->SetTexture(texture);
	this->SetPos(x, y);
}

Player::~Player()
{
}
