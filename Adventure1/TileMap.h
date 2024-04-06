#pragma once

#include "Tile.h"

using namespace std;
using namespace sf;
class TileMap
{
private:
	float gridSizeF; // grid size
	unsigned gridSizeU; // for wut :DDDD

	unsigned layers; // for 2.5D

	Vector2u maxSize; // size of the grid

	vector<vector<vector<Tile>>> map; //2d vector, each factor has a vector in it
public:
	TileMap();
	~TileMap();
	void Update();
	void Render(RenderTarget& target);
};

