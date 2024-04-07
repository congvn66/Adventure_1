#pragma once


class Tile
{
private:

protected:
	RectangleShape shape;
public:
	Tile(float x, float y, float gridSizeF,Texture& tileSheet,const IntRect& texRect);
	~Tile();

	void Update();
	void Render(RenderTarget& target);
};

