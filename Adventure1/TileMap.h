#pragma once

#include "Tile.h"

using namespace std;
using namespace sf;
class TileMap
{
private:
	void Clear();
	string texFile;
	float gridSizeF; // grid size
	unsigned gridSizeU; // for wut :DDDD

	unsigned layers; // for 2.5D

	Vector2u maxSize; // size of the grid

	vector<vector<vector<Tile*>>> map; //2d vector, each factor has a vector in it

	Texture tileSheet;
public:
	TileMap(float gridSize, unsigned width, unsigned height, string texFile);
	~TileMap();

	void Update();
	void Render(RenderTarget& target);

	const Texture* GetTileSheet() const;

	//for the editor, i mean this class =)
	void AddTile(const unsigned x, const unsigned y, const unsigned z, const IntRect texRect,const bool& collision, const short& type);
	void RemoveTile(const unsigned x, const unsigned y, const unsigned z);
	void SaveToFile(const string fileName);
	void LoadFromFile(const string fileName);
};

