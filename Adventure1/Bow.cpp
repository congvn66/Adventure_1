#include "stdafx.h"
#include "Bow.h"

Bow::Bow(unsigned value)
	:Ranged(value)
{
}

Bow::~Bow()
{
}

Bow* Bow::clone()
{
	return new Bow(*this); // copy of it
}
