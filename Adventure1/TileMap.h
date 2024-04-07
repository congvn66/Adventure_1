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

	vector<vector<vector<Tile*>>> map; //2d vector, each factor has a vector in it

	Texture tileSheet;
public:
	TileMap(float gridSize, unsigned width, unsigned height);
	~TileMap();

	void Update();
	void Render(RenderTarget& target);

	const Texture* GetTileSheet() const;

	//for the editor, i mean this class =)
	void AddTile(const unsigned x, const unsigned y, const unsigned z, const IntRect texRect);
	void RemoveTile(const unsigned x, const unsigned y, const unsigned z);

};

