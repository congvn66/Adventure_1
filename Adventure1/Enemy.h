#pragma once

#include "Entity.h"
#include "EnemySpawner.h"

class EnemySpawner;

class Enemy :
    public Entity
{
private:
    //EnemySpawner& enemySpawner; // keep track of its spawner

    virtual void InitVal()=0;
    virtual void InitAnimation()=0;
    void InitComponents();

public:
    Enemy();
    ~Enemy();
    virtual void Update(const float& dt, Vector2f& mousePosView)=0;
    virtual void Render(RenderTarget& target, Shader* shader=nullptr, const bool showHitBox=false)=0;
    virtual void UpdateAnimation(const float& dt)=0;
};
