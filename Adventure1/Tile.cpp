#include "stdafx.h"
#include "Tile.h"

Tile::Tile(float x, float y, float gridSizeF)
{
	this->shape.setSize(Vector2f(gridSizeF, gridSizeF));
	this->shape.setFillColor(Color(31, 75, 110,100));
	this->shape.setPosition(x, y);
}

Tile::~Tile()
{
}

void Tile::Update()
{
}

void Tile::Render(RenderTarget& target)
{
	target.draw(this->shape);
}


