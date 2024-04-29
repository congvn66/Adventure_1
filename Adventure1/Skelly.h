#pragma once
#include "Enemy.h"
#include "AIFollow.h"
class Skelly :
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
    Skelly(float x, float y, Texture& textureSheet, EnemySpawner& enemySpawner, Entity& player);
    ~Skelly();

    void UpdateAnimation(const float& dt);
    void Update(const float& deltaTime, Vector2f& mousePosView, const View& view);
    void Render(RenderTarget& target, Shader* shader = nullptr, const bool showHitBox = false);
};

