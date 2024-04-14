#include "stdafx.h"
#include "AttributeComponent.h"

AttributeComponent::AttributeComponent(unsigned level)
{
	this->level = level;
	this->exp = 0;
	this->expNext = static_cast<unsigned>((50/3)*(pow(this->level+1,3)-6*pow(this->level+1,2)+((this->level+1)*17)-12));//equation to calculate next exp
	this->attributePoint = 2;

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


void AttributeComponent::GainExp(const unsigned exp)
{
	this->exp += exp;

	this->UpdateLevel();
}

void AttributeComponent::UpdateStats(const bool reset)
{
	this->hpMax     = this->vitality * 5 + this->vitality + this->strength/2 + this->intelligence / 5;
	this->damageMin = this->strength * 2 + this->strength / 4 + this->intelligence / 5;
	this->damageMax = this->strength * 2 + this->strength / 2 + this->intelligence / 5;
	this->accuracy  = this->dexterity * 5 + this->dexterity / 3 + this->intelligence / 5;
	this->dodge     = this->agility * 2 + this->agility / 4 + this->intelligence / 5;
	this->luck      = this->intelligence * 2 + this->intelligence / 5;

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
		this->expNext = static_cast<unsigned>((50 / 3) * (pow(this->level, 3) - 6 * pow(this->level, 2) + (this->level * 17) - 12));
		this->attributePoint++;
	}
}
void AttributeComponent::Update()
{
	this->UpdateLevel();
}


