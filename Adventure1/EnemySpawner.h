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
	bool firstSpawn;

	//Spawn timer
public:
	EnemySpawner(int grid_x, int grid_y, float gridSizeF, Texture& tileSheet, const IntRect& texRect,
		int eType, int amount, Int32 timeToSpawn, float maxDis);
	~EnemySpawner();
	void spawn();
	void clear();
	void Update();
	void IncreaseEnemyCounter();
	void DecreaseEnemyCounter();
	const bool GetSpawnTimer() ;
	const int& GetEnemyCounter() const;
	const int& GetEnemyAmount() const;
	const int& GetEnemyType() const;
	const float& GetEnemyMaxDis() const;
	void Render(RenderTarget& target, const Vector2f playerPos = Vector2f(), Shader* shader = nullptr);
	const string GetAsString() const;
};

