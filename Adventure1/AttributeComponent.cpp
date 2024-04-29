#include "stdafx.h"
#include "AttributeComponent.h"

AttributeComponent::AttributeComponent(int level)
{
	this->level = level;
	this->exp = 0;
	this->expNext = static_cast<int>((50/3)*(pow(this->level+1,3)-6*pow(this->level+1,2)+((this->level+1)*17)-12));//equation to calculate next exp
	this->attributePoint = 2;
	this->movementSpeed = 140.f;

	this->vitality = 1;
	this->strength = 1;
	this->dexterity = 1;
	this->intelligence = 1;
	this->agility = 1;

	this->UpdateLevel();
	this->UpdateStats(true);
}
AttributeComponent::~AttributeComponent()
{
}

const bool AttributeComponent::isDead() const
{
	return this->hp <=0;
}

void AttributeComponent::LoseHP(const int hp)
{
	this->hp -= hp;

	if (this->hp < 0)
	{
		this->hp = 0;
	}
}
void AttributeComponent::LoseEXP(const int exp)
{
	this->exp -= exp;

	if (this->exp < 0)
	{
		this->exp = 0;
	}
}
void AttributeComponent::GainHP(const int hp)
{
	this->hp += hp;

	if (this->hp > this->hpMax)
	{
		this->hp = this->hpMax;
	}
}

void AttributeComponent::GainExp(const int exp)
{
	this->exp += exp;

	this->UpdateLevel();
}

void AttributeComponent::UpdateStats(const bool reset)
{
	this->movementSpeed = 5 * this->agility + 140;
	this->hpMax     = (this->vitality * 9 + this->vitality + this->strength/2 + this->intelligence / 5);
	this->damageMin = (this->strength * 2 + this->strength / 4 + this->intelligence / 5);
	this->damageMax = (this->strength * 2 + this->strength / 2 + this->intelligence / 5);
	this->accuracy  = (this->dexterity * 5 + this->dexterity / 3 + this->intelligence / 5);
	this->dodge     = (this->agility * 2 + this->agility / 4 + this->intelligence / 5);
	this->luck      = (this->intelligence * 2 + this->intelligence / 5);

	if (reset)
	{
		this->hp = this->hpMax;
	}
}

void AttributeComponent::UpdateLevel()
{
	while (this->exp >= this->expNext) //surpass a level
	{
		this->level++;
		this->exp -= this->expNext;
		this->expNext = static_cast<int>((50 / 3) * (pow(this->level, 3) - 6 * pow(this->level, 2) + (this->level * 17) - 12));
		this->attributePoint++;
		this->UpdateStats(true);
	}
}
void AttributeComponent::Update()
{
	this->UpdateLevel();
}


