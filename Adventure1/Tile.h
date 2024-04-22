#pragma once

enum TileType {DEFAULT = 0, DAMAGING, ABOVE, SPAWNER};

class Tile
{
private:

protected:
	Sprite shape;
	short type;
	bool collision;
public:
	Tile();
	Tile(short type,int grid_x, int grid_y, float gridSizeF,Texture& tileSheet,const IntRect& texRect,const bool collision);
	~Tile();

	virtual const bool& GetCollision() const;
	virtual const short& GetType() const;
	virtual const Vector2f& GetPos() const;
	virtual const bool Intersects(FloatRect bounds) const;
	virtual const FloatRect GetGlobalBounds() const;
	virtual const string GetAsString() const=0;
	virtual void Update()=0;
	virtual void Render(RenderTarget& target,const Vector2f playerPos=Vector2f(), Shader* shader = nullptr)=0;
};

