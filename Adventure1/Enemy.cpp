#include "stdafx.h"
#include "Enemy.h"

void Enemy::InitVal()
{
	this->gainExp = 10;
}

void Enemy::InitComponents()
{
}
void Enemy::InitAnimation()
{
	
}
Enemy::Enemy()
{
	this->InitVal();
	this->InitAnimation();
}

Enemy::~Enemy()
{
}

const unsigned& Enemy::GetGainExp() const
{
	return this->gainExp;
}

const bool Enemy::IsDead() const
{
	if (this->animationComponent)
	{
		return this->attributeComponent->isDead();
	}
}

void Enemy::LoseHP(const int hp)
{
	if (this->attributeComponent)
	{
		this->attributeComponent->LoseHP(hp);
	}
}

const AttributeComponent* Enemy::GetAC() const
{
	if (this->attributeComponent)
	{
		return this->attributeComponent;
	}
	return nullptr;
}