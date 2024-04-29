#pragma once
#include "Tile.h"
class RegularTile :
    public Tile
{
private:
protected:
public:
    RegularTile(short type, int grid_x, int grid_y, float gridSizeF, Texture& tileSheet, const IntRect& texRect,
        bool collision = false);
    ~RegularTile();

	
	virtual const string GetAsString() const;
	virtual void Update();
	virtual void Render(RenderTarget& target, const Vector2f playerPos = Vector2f(), Shader* shader = nullptr);
};

