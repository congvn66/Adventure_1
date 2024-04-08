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
	Tile(unsigned grid_x, unsigned grid_y, float gridSizeF,Texture& tileSheet,const IntRect& texRect, bool collision=false, short type=TileType::DEFAULT);
	~Tile();

	const string GetAsString() const;
	void Update();
	void Render(RenderTarget& target);
};

