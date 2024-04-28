#include "stdafx.h"
#include "EnemySystem.h"

EnemySystem::EnemySystem(vector <Enemy*>& activeEnemies, std::map <string, Texture>& textures, Entity& player)
	:activeEnemies(activeEnemies), textures(textures), player(player)
{
}

EnemySystem::~EnemySystem()
{
}

void EnemySystem::CreateEnemy(const short type, const float x, const float y, EnemySpawner& es)
{
	switch(type)
	{
	case EnemyType::ORC:
		this->activeEnemies.push_back(new Orc(x, y, this->textures["ORC_SHEET"],es , this->player));
		es.IncreaseEnemyCounter();
		break;
	default:
		cout << "Enemy System: cant load enemies!";
		break;
	}
}

void EnemySystem::removeEnemy(const int index)
{
	this->activeEnemies[index]->GetEnemySpawner().DecreaseEnemyCounter();
	delete this->activeEnemies[index];
	this->activeEnemies.erase(this->activeEnemies.begin() + index);
}

void EnemySystem::Update(const float& deltaTime)
{
}

void EnemySystem::Render(RenderTarget* target)
{
}
