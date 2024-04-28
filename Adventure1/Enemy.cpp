#include "stdafx.h"
#include "Enemy.h"

void Enemy::InitVal()
{
	this->gainExp = 10;
	this->dmgTimerMax = 1000;
}

void Enemy::InitComponents()
{
}
void Enemy::InitAnimation()
{
	
}
Enemy::Enemy(EnemySpawner& enemySpawner)
	:enemySpawner(enemySpawner)
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

EnemySpawner& Enemy::GetEnemySpawner()
{
	// TODO: insert return statement here
	return this->enemySpawner;
}

void Enemy::ResetDmgTimer()
{
	this->dmgTimer.restart();
}

const bool Enemy::GetDmgTimerDone()
{
	return this->dmgTimer.getElapsedTime().asMilliseconds()>=this->dmgTimerMax;
}

void Enemy::GenerateAttributes(const unsigned level)
{
	this->gainExp = level * (rand() % 5 + 1)+10 ;
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