#include "stdafx.h"
#include "RegularTile.h"

RegularTile::RegularTile(short type, int grid_x, int grid_y, float gridSizeF, Texture& tileSheet, 
	const IntRect& texRect, bool collision)
	:Tile(type,grid_x,grid_y,gridSizeF,tileSheet,texRect,collision)
{
}

RegularTile::~RegularTile()
{
}



const string RegularTile::GetAsString() const
{
	stringstream ss;
	//type x y collision
	ss << this->type << " " << this->shape.getTextureRect().left << " " << this->shape.getTextureRect().top << " " << this->collision;
	//cout << ss.str() << endl;
	return ss.str();
}

void RegularTile::Update()
{
}

void RegularTile::Render(RenderTarget& target, const Vector2f playerPos, Shader* shader)
{
	if (shader)
	{
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", playerPos);
		target.draw(this->shape, shader);
	}
	else
	{
		target.draw(this->shape);
	}
}
