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
	case EnemyType::SKELLY:
		this->activeEnemies.push_back(new Skelly(x, y, this->textures["SKELLY_SHEET"], es, this->player));
		es.IncreaseEnemyCounter();
		break;
	case EnemyType::WRAITH:
		this->activeEnemies.push_back(new Wraith(x, y, this->textures["WRAITH_SHEET"], es, this->player));
		es.IncreaseEnemyCounter();
		break;
	case EnemyType::ZOMBIE:
		this->activeEnemies.push_back(new Zombie(x, y, this->textures["ZOMBIE_SHEET"], es, this->player));
		es.IncreaseEnemyCounter();
		break;
	case EnemyType::BOSS:
		this->activeEnemies.push_back(new Boss(x, y, this->textures["BOSS_SHEET"], es, this->player));
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
