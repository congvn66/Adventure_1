#include "stdafx.h"
#include "Tile.h"
Tile::Tile()
{
	this->collision = false;
	this->type = 0;
}
Tile::Tile(short type,int grid_x, int grid_y, float gridSizeF, Texture& tileSheet, const IntRect& texRect, const bool collision)
{
	this->collision = collision;
	this->type = type;
	/*this->shape.setFillColor(Color(31, 75, 110,100));*/
	//this->shape.setOutlineThickness(1.0f);
	//this->shape.setOutlineColor(Color::Black);
	this->shape.setPosition(static_cast<float>(grid_x)*gridSizeF, static_cast<float>(grid_y)*gridSizeF);
	this->shape.setTexture(tileSheet);
	this->shape.setTextureRect(texRect);
}
Tile::~Tile()
{
}

const short& Tile::GetType() const
{
	return this->type;
}

const bool& Tile::GetCollision() const
{
	return this->collision;
}

const Vector2f& Tile::GetPos() const
{
	return this->shape.getPosition();
}

const bool Tile::Intersects(FloatRect bounds) const
{
	return this->shape.getGlobalBounds().intersects(bounds);
}

const FloatRect Tile::GetGlobalBounds() const
{
	return this->shape.getGlobalBounds();
}



