#pragma once

#include "Entity.h"
#include "EnemySpawner.h"

class EnemySpawner;

class Enemy :
    public Entity
{
private:
    EnemySpawner& enemySpawner; // keep track of its spawner

    void InitVal();
    void InitComponents();
    void InitAnimation();

public:
    Enemy(EnemySpawner& enemy_spawner,float x, float y, Texture& textureSheet);
    ~Enemy();
    void Update(const float& dt, Vector2f& mousePosView);
    void Render(RenderTarget& target, Shader* shader=nullptr, const bool showHitBox=false);
    void UpdateAnimation(const float& dt);
};
