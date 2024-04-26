#include "stdafx.h"
#include "Weapon.h"

void Weapon::InitVal()
{
	this->range = 20;
	this->damageMin = 1;
	this->damageMax = 2;
}

void Weapon::InitCooldown()
{
	this->cooldown = 0.f;
	this->cooldownMax = 10.f;
	this->cooldownAddition = 1.f;
}

Weapon::Weapon(unsigned value, string texFile)
	:Item(value)
{
	this->InitVal();
	if (this->weaponTexture.loadFromFile(texFile))
	{
		cout << "GameState: sword is ready!" << endl;
	}
	this->weaponSprite.setTexture(weaponTexture);
}

Weapon::~Weapon()
{
}

const unsigned& Weapon::GetDamageMin() const
{
	return this->damageMin;
}

const unsigned& Weapon::GetDamageMax() const
{
	return this->damageMax;
}

const unsigned& Weapon::GetRange() const
{
	return this->range;
}
