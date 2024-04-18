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
	Tile(int grid_x, int grid_y, float gridSizeF,Texture& tileSheet,const IntRect& texRect, 
		bool collision=false, short type=TileType::DEFAULT);
	~Tile();

	const short& GetType() const;
	const bool& GetCollision() const;
	const Vector2f& GetPos() const;
	const bool Intersects(FloatRect bounds) const;
	const FloatRect GetGlobalBounds() const;
	const string GetAsString() const;
	virtual void Update();
	virtual void Render(RenderTarget& target,const Vector2f playerPos=Vector2f(), Shader* shader = nullptr);
};

