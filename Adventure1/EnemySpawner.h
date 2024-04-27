#pragma once

#include "Enemy.h"
#include "Tile.h"

class EnemySpawner
	:public Tile
{
private:
	int enemyType;
	int amount;
	int enemyCnt;
	Int32 timeToSpawn;
	Clock enemySpawnTimer;
	float maxDis;
	bool spawned;

	//Spawn timer
public:
	EnemySpawner(int grid_x, int grid_y, float gridSizeF, Texture& tileSheet, const IntRect& texRect,
		int eType, int amount, Int32 timeToSpawn, float maxDis);
	~EnemySpawner();
	void spawn();
	void clear();
	void Update();
	const bool CanSpawn() const;
	const bool& GetSpawned() const;
	void IncreaseEnemyCounter();
	void DecreaseEnemyCounter();
	const int& GetEnemyCounter() const;
	const int& GetEnemyAmount() const;
	void SetSpawned(const bool spawned);
	void Render(RenderTarget& target, const Vector2f playerPos = Vector2f(), Shader* shader = nullptr);
	const string GetAsString() const;
};

