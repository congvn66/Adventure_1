#include "stdafx.h"
#include "Melee.h"

Melee::Melee(unsigned value, string texFile)
	:Weapon(value, texFile)
{
	this->type = ItemTypes::MELEE;
}

Melee::~Melee()
{
}

Melee* Melee::clone()
{
	return nullptr;
}
