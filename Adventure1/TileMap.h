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
	int gridSizeI; // for wut :DDDD
	int layers; // for 2.5D

	vector<vector<vector<vector<Tile*>>>> map; //4d vector (now the fourth dimension access each tile that appear in 1 layer)
	stack<Tile*> deferedRenderStack;

	Vector2i maxSizeGrid; // size of the grid
	Vector2f maxSizeWorldF;

	Texture tileSheet;

	int fromX;
	int fromY;
	int toX;
	int toY;
	int layer;
public:
	TileMap(float gridSize, int width, int height, string texFile);
	TileMap(const string fileName);
	~TileMap();

	//for the editor, i mean this class =)
	const bool TileEmpty(const int x, const int y, const int z) const;
	const Vector2i& GetMaxSizeGrid() const;
	const Vector2f& GetMaxSizeF() const;
	const int GetLayerSize(const int x, const int y, const int z);
	void Render(RenderTarget& target, const Vector2i& gridPos,const bool show_collision = false, const Vector2f playerPos = Vector2f(), Shader* shader = nullptr);
	const Texture* GetTileSheet() const;
	void Update(Entity* entity, const float& deltaTime);
	void AddTile(const int x, const int y, const int z, const IntRect texRect,const bool& collision, const short& type);
	void RemoveTile(const int x, const int y, const int z);
	void SaveToFile(const string fileName);
	void LoadFromFile(const string fileName);
	void RenderDefered(RenderTarget& target, const Vector2f playerPos = Vector2f(), Shader* shader = nullptr);
};

