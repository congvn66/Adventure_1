#include "stdafx.h"
#include "EnemySystem.h"

EnemySystem::EnemySystem(vector <Enemy*>& activeEnemies, std::map <string, Texture>& textures)
	:activeEnemies(activeEnemies), textures(textures)
{
}

EnemySystem::~EnemySystem()
{
}

void EnemySystem::CreateEnemy(const short type,const float x, const float y)
{
	switch(type)
	{
	case EnemyType::ORC:
		this->activeEnemies.push_back(new Orc(x, y, this->textures["ORC_SHEET"]));
		break;
	default:
		cout << "Enemy System: cant load enemies!";
		break;
	}
}

void EnemySystem::Update(const float& deltaTime)
{
}

void EnemySystem::Render(RenderTarget* target)
{
}
