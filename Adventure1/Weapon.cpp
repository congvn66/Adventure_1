#include "stdafx.h"
#include "Weapon.h"

void Weapon::InitVal()
{
	this->range = 80;
	this->damageMin = 1;
	this->damageMax = 2;

	this->atkTimer.restart();
	this->atkTimerMax = 500;
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

const bool Weapon::GetAtkTimer()
{
	//cout << this->atkTimer.getElapsedTime().asMilliseconds() << endl;
	if (this->atkTimer.getElapsedTime().asMilliseconds()>=this->atkTimerMax)
	{
		this->atkTimer.restart();
		return true;
	}
	return false;
}
