#include "stdafx.h"
#include "Bow.h"

Bow::Bow(unsigned level,unsigned value, string texFile)
	:Ranged(level, value,texFile)
{
}

Bow::~Bow()
{
}

Bow* Bow::clone()
{
	return new Bow(*this); // copy of it
}

void Bow::Update(const Vector2f centerPos, const Vector2f& mousePosView)
{
}

void Bow::Render(RenderTarget& target)
{
}
