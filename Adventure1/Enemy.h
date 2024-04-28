#pragma once

#include "Entity.h"
#include "EnemySpawner.h"

class EnemySpawner;

class Enemy :
    public Entity
{
protected:
    EnemySpawner& enemySpawner; // keep track of its spawner
    unsigned gainExp;
    virtual void InitVal()=0;
    virtual void InitAnimation()=0;
    void InitComponents();
    Clock dmgTimer;
    Int32 dmgTimerMax;

public:
    Enemy(EnemySpawner& enemySpawner);
    ~Enemy();
    const unsigned& GetGainExp() const;
    EnemySpawner& GetEnemySpawner();
    void ResetDmgTimer();
    const bool GetDmgTimerDone();
    virtual void GenerateAttributes(const unsigned level);
    virtual const bool IsDead() const;
    virtual void LoseHP(const int hp);
    virtual const AttributeComponent* GetAC() const;
    virtual void Update(const float& dt, Vector2f& mousePosView)=0;
    virtual void Render(RenderTarget& target, Shader* shader=nullptr, const bool showHitBox=false)=0;
    virtual void UpdateAnimation(const float& dt)=0;
};
