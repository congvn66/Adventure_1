#pragma once
#include "Enemy.h"

class Enemy;

class Orc :
    public Enemy
{
private:
    void InitVal();
    void InitComponents();
    void InitAnimation();
public:
    Orc(float x, float y, Texture& textureSheet);
    ~Orc();

    void UpdateAnimation(const float& dt);
    void Update(const float& dt, Vector2f& mousePosView);
    void Render(RenderTarget& target, Shader* shader = nullptr, const bool showHitBox = false);
};

