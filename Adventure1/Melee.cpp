#include "stdafx.h"
#include "Melee.h"

Melee::Melee(unsigned dmgMin, unsigned dmgMax, unsigned range, unsigned level, unsigned value, string texFile)
	:Weapon(dmgMin, dmgMax, range,level,value, texFile)
{
	this->type = ItemTypes::MELEE;
}

Melee::~Melee()
{
}

void Melee::Generate(const unsigned lvMax, const unsigned lvMin)
{
	this->level = rand() % (lvMax - lvMin + 1) + lvMin;
	this->damageMin = this->level * (rand() % 2 + 1);
	this->damageMax = this->level * (rand() % 2 + 1) + this->damageMin;
	this->range = this->level + rand() % 10 + 80;
	this->value = this->level + this->damageMin + this->damageMax + this->range + (rand() % this->level * 10);
}

Melee* Melee::clone()
{
	return nullptr;
}
