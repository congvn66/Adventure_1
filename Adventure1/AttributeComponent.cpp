#include "stdafx.h"
#include "AttributeComponent.h"

AttributeComponent::AttributeComponent(unsigned level)
{
	this->level = level;
	this->exp = 0;
	this->expNext = 0;
	this->attributePoint = 3;

	this->vitality = 1;
	this->strength = 1;
	this->dexterity = 1;
	this->intelligence = 1;
	this->constitution = 1;
	this->agility = 1;

	this->UpdateStats();
}
AttributeComponent::~AttributeComponent()
{
}

void AttributeComponent::CalulateExpNext()
{
}

void AttributeComponent::UpdateStats()
{

}

void AttributeComponent::LevelUp()
{
}

void AttributeComponent::Update()
{
}
