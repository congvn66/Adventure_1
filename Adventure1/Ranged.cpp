#include "stdafx.h"
#include "Ranged.h"

Ranged::Ranged(unsigned value)
    :Item(value)
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
