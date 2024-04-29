#include "stdafx.h"
#include "Ranged.h"

Ranged::Ranged(unsigned level,unsigned value, string texFile)
    :Weapon(level, value, texFile)
{
    this->type = ItemTypes::RANGED;
}

Ranged::~Ranged()
{
}

void Ranged::Generate(const unsigned lvMax, const unsigned lvMin)
{
}

Ranged* Ranged::clone()
{
    return nullptr;
}
