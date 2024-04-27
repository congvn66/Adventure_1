#include "stdafx.h"
#include "EnemySpawner.h"

EnemySpawner::EnemySpawner(int grid_x, int grid_y, float gridSizeF, Texture& tileSheet, const IntRect& texRect,
	 int eType, int amount, Int32 timeToSpawn, float maxDis)
	:Tile (TileType::SPAWNER,grid_x,grid_y,gridSizeF,tileSheet,texRect,false)
{
	this->enemyType = eType;
	this->amount = amount;
	this->enemyCnt = 0;
	this->enemySpawnTimer.restart();
	this->timeToSpawn = timeToSpawn;
	this->maxDis = maxDis;
	this->spawned = false;
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
	if (this->CanSpawn())
	{
		this->spawned = false;
	}
}

const bool EnemySpawner::CanSpawn() const
{
	if (this->enemySpawnTimer.getElapsedTime().asMilliseconds() >= this->timeToSpawn)
	{
		return true;
	}
	return false;
}

const bool& EnemySpawner::GetSpawned() const
{
	return this->spawned;
}

void EnemySpawner::IncreaseEnemyCounter()
{
	if (this->enemyCnt > this->amount)
	{
		this->enemyCnt = this->amount;
	}
	else
	{
		this->enemyCnt++;
	}
}

void EnemySpawner::DecreaseEnemyCounter()
{
	if (this->enemyCnt < 0)
	{
		this->enemyCnt =0;
	}
	else
	{
		this->enemyCnt--;
	}
}

const int& EnemySpawner::GetEnemyCounter() const
{
	// TODO: insert return statement here
	return this->enemyCnt;
}

const int& EnemySpawner::GetEnemyAmount() const
{
	// TODO: insert return statement here
	return this->amount;
}

void EnemySpawner::SetSpawned(const bool spawned)
{
	this->spawned = spawned;
	this->enemySpawnTimer.restart();
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

const string EnemySpawner::GetAsString() const
{
	stringstream ss;
	//x y z(tilemap save) 
	//type 
	//rectx recty
	//enemy type
	//enemy am
	//enemy	tts
	//max dis
	ss << this->type << " " << this->shape.getTextureRect().left << " " << this->shape.getTextureRect().top<<" "<< 
		this->enemyType <<" "<< this->amount<< " "<< this->timeToSpawn << " "<< this->maxDis;
	//cout << ss.str() << endl;
	return ss.str();
}
