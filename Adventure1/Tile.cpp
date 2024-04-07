#include "stdafx.h"
#include "Tile.h"

Tile::Tile(float x, float y, float gridSizeF, Texture& tileSheet, const IntRect& texRect)
{
	this->shape.setSize(Vector2f(gridSizeF, gridSizeF));
	/*this->shape.setFillColor(Color(31, 75, 110,100));*/
	//this->shape.setOutlineThickness(1.0f);
	//this->shape.setOutlineColor(Color::Black);
	this->shape.setPosition(x, y);
	this->shape.setTexture(&tileSheet);
	this->shape.setTextureRect(texRect);
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


