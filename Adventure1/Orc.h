#pragma once
#include "Enemy.h"
#include "AIFollow.h"

class Enemy;

class Orc :
    public Enemy
{
private:
    void InitVal();
    void InitComponents();
    void InitAnimation();
    void InitGui();
    void InitAI();

    AIFollow* follow;

    RectangleShape hpBar;
public:
    Orc(float x, float y, Texture& textureSheet, EnemySpawner& enemySpawner, Entity& player);
    ~Orc();

    void UpdateAnimation(const float& dt);
    void Update(const float& dt, Vector2f& mousePosView);
    void Render(RenderTarget& target, Shader* shader = nullptr, const bool showHitBox = false);
};

