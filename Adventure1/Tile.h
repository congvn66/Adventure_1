#pragma once


class Tile
{
private:

protected:
	RectangleShape shape;
public:
	Tile(float x, float y, float gridSizeF);
	~Tile();

	void Update();
	void Render(RenderTarget& target);
};

