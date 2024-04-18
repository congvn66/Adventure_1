#pragma once

#include "Enemy.h"
#include "Tile.h"

class EnemySpawner
	:public Tile
{
private:
	int enemyType;
	int amount;
	int timeToSpawn;
	float maxDis;

public:
	EnemySpawner(int grid_x, int grid_y, float gridSizeF, Texture& tileSheet, const IntRect& texRect,
		float gridsize, int eType, int amount, int timeToSpawn, float maxDis);
	~EnemySpawner();
	void spawn();
	void clear();
	void Update();
	void Render(RenderTarget& target, const Vector2f playerPos = Vector2f(), Shader* shader = nullptr);
};

