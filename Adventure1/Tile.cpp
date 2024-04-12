#include "stdafx.h"
#include "Tile.h"
Tile::Tile(unsigned grid_x, unsigned grid_y, float gridSizeF, Texture& tileSheet, const IntRect& texRect, bool collision, short type)
{
	this->collision = collision;
	this->type = type;
	this->shape.setSize(Vector2f(gridSizeF, gridSizeF));
	/*this->shape.setFillColor(Color(31, 75, 110,100));*/
	//this->shape.setOutlineThickness(1.0f);
	//this->shape.setOutlineColor(Color::Black);
	this->shape.setPosition(grid_x*gridSizeF, grid_y*gridSizeF);
	this->shape.setTexture(&tileSheet);
	this->shape.setTextureRect(texRect);
}
Tile::~Tile()
{
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


