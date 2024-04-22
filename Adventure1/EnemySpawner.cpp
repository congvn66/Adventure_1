#include "stdafx.h"
#include "EnemySpawner.h"

EnemySpawner::EnemySpawner(int grid_x, int grid_y, float gridSizeF, Texture& tileSheet, const IntRect& texRect,
	 int eType, int amount, int timeToSpawn, float maxDis)
	:Tile (TileType::SPAWNER,grid_x,grid_y,gridSizeF,tileSheet,texRect,false)
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
