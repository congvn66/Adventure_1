#include "stdafx.h"
#include "Enemy.h"

void Enemy::InitVal()
{
	this->gainExp = 10;
	this->dmgTimerMax = 1000;
	this->despawnTimerMax = 1000;
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

const bool Enemy::GetDespawnTimerDone() const
{
	return this->despawnTimer.getElapsedTime().asMilliseconds() >= this->despawnTimerMax;
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

const unsigned Enemy::GetDmg() const
{
	return rand() % ((this->attributeComponent->damageMax) - (this->attributeComponent->damageMin) + 1) + (this->attributeComponent->damageMin);
}

void Enemy::GenerateAttributes(const unsigned level, const int type)
{
	this->gainExp = level * (rand() % 10 + 5) + 10 ;
	if (type == 3) //zombie
	{
		this->attributeComponent->hpMax = 35;
		this->attributeComponent->hp = this->attributeComponent->hpMax;
		this->attributeComponent->damageMax = 2;
		this->attributeComponent->damageMin = 1;
	}
	else if (type == 0) //orc
	{
		this->attributeComponent->hpMax = 25;
		this->attributeComponent->hp = this->attributeComponent->hpMax;
		this->attributeComponent->damageMax = 3;
		this->attributeComponent->damageMin = 1;
	}
	else if (type == 1) //skelly
	{
		this->attributeComponent->hpMax = 20;
		this->attributeComponent->hp = this->attributeComponent->hpMax;
		this->attributeComponent->damageMax = 5;
		this->attributeComponent->damageMin = 2;
	}
	else if (type == 2) //wraith
	{
		this->attributeComponent->hpMax = 1;
		this->attributeComponent->hp = this->attributeComponent->hpMax;
		this->attributeComponent->damageMax = 6;
		this->attributeComponent->damageMin = 3;
	}
	else if (type == 4) //boss
	{
		this->attributeComponent->hpMax = 9999;
		this->attributeComponent->hp = this->attributeComponent->hpMax;
		this->attributeComponent->damageMax = 1000000;
		this->attributeComponent->damageMin = 1000000-1;
	}
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
void Enemy::Update(const float& deltaTime, Vector2f& mousePosView, const View& view)
{
	Vector2f tmp; 
	tmp.x = view.getCenter().x - this->GetPos().x;
	tmp.y = view.getCenter().y - this->GetPos().y;
	float len = sqrt(pow(tmp.x, 2) + pow(tmp.y, 2));
	if (len < 1500.f)
	{
		this->despawnTimer.restart();
	}
}