#pragma once

#include "Tile.h"
#include "Entity.h"

using namespace std;
using namespace sf;
class TileMap
{
private:
	void Clear();
	string texFile;
	RectangleShape collisionBox; //walls, borders, etc,...
	float gridSizeF; // grid size
	unsigned gridSizeU; // for wut :DDDD

	unsigned layers; // for 2.5D

	vector<vector<vector<Tile*>>> map; //2d vector, each factor has a vector in it

	Vector2u maxSizeGrid; // size of the grid
	Vector2f maxSizeWorldF;

	Texture tileSheet;

	unsigned fromX;
	unsigned fromY;
	unsigned toX;
	unsigned toY;
	unsigned layer;
public:
	TileMap(float gridSize, unsigned width, unsigned height, string texFile);
	~TileMap();

	//for the editor, i mean this class =)
	void Update();
	void Render(RenderTarget& target, Entity* entity = nullptr);
	const Texture* GetTileSheet() const;
	void UpdateCollision(Entity* entity);
	void AddTile(const unsigned x, const unsigned y, const unsigned z, const IntRect texRect,const bool& collision, const short& type);
	void RemoveTile(const unsigned x, const unsigned y, const unsigned z);
	void SaveToFile(const string fileName);
	void LoadFromFile(const string fileName);
};

