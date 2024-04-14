#include "stdafx.h"
#include "Tile.h"
Tile::Tile(int grid_x, int grid_y, float gridSizeF, Texture& tileSheet, const IntRect& texRect, bool collision, short type)
{
	this->collision = collision;
	this->type = type;
	this->shape.setSize(Vector2f(gridSizeF, gridSizeF));
	/*this->shape.setFillColor(Color(31, 75, 110,100));*/
	//this->shape.setOutlineThickness(1.0f);
	//this->shape.setOutlineColor(Color::Black);
	this->shape.setPosition(static_cast<float>(grid_x)*gridSizeF, static_cast<float>(grid_y)*gridSizeF);
	this->shape.setTexture(&tileSheet);
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
	// TODO: insert return statement here
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

const string Tile::GetAsString() const
{
	stringstream ss;
	//x y collision type
	ss << this->shape.getTextureRect().left << " " << this->shape.getTextureRect().top << " " << this->collision << " " << this->type;
	return ss.str();
}
void Tile::Update()
{
}
void Tile::Render(RenderTarget& target)
{
	target.draw(this->shape);
}


