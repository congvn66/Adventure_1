#include "stdafx.h"
#include "EnemySpawner.h"

EnemySpawner::EnemySpawner(int grid_x, int grid_y, float gridSizeF, Texture& tileSheet, const IntRect& texRect,
	float gridsize, int eType, int amount, int timeToSpawn, float maxDis)
	:Tile (grid_x,grid_y,gridSizeF,tileSheet,texRect,false,TileType::SPAWNER)
{
	this->enemyType = eType;
	this->amount = amount;
	this->timeToSpawn = timeToSpawn;
	this->maxDis = maxDis;
}

EnemySpawner::~EnemySpawner()
{
}

void EnemySpawner::spawn()
{
}

void EnemySpawner::clear()
{
}

void EnemySpawner::Update()
{

}

void EnemySpawner::Render(RenderTarget& target, const Vector2f playerPos, Shader* shader)
{
	if (shader)
	{
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", playerPos);
		target.draw(this->shape, shader);
	}
	else
	{
		target.draw(this->shape);
	}
}
