#include "stdafx.h"
#include "Ranged.h"

Ranged::Ranged(unsigned value, string texFile)
    :Weapon(value, texFile)
{
    this->type = ItemTypes::RANGED;
}

Ranged::~Ranged()
{
}

Ranged* Ranged::clone()
{
    return nullptr;
}
