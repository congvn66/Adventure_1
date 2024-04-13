#pragma once

enum TileType {DEFAULT = 0, DAMAGING};

class Tile
{
private:

protected:
	RectangleShape shape;
	short type;
	bool collision;
public:
	Tile(int grid_x, int grid_y, float gridSizeF,Texture& tileSheet,const IntRect& texRect, bool collision=false, short type=TileType::DEFAULT);
	~Tile();

	const bool& GetCollision() const;
	const Vector2f& GetPos() const;
	const bool Intersects(FloatRect bounds) const;
	const FloatRect GetGlobalBounds() const;
	const string GetAsString() const;
	void Update();
	void Render(RenderTarget& target);
};

