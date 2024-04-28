#pragma once

#include "Orc.h"
#include "EnemySpawner.h"

enum EnemyType {ORC = 0, SKELLY, WRAITH, ZOMBIE};

class EnemySystem
{
private:
	std::map <string, Texture>& textures; // point to gamestate's one
	vector <Enemy*>& activeEnemies;
	Entity& player;
public:
	EnemySystem(vector <Enemy*>& activeEnemies, std::map <string, Texture>& textures, Entity& player);
	~EnemySystem();

	void CreateEnemy(const short type, const float x, const float y, EnemySpawner& es);
	void removeEnemy(const int index);
	void Update(const float& deltaTime);
	void Render(RenderTarget* target);
};

