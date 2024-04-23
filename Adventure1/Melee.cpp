#include "stdafx.h"
#include "Melee.h"

Melee::Melee(unsigned value)
	:Item(value)
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
