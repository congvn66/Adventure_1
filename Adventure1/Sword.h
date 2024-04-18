#pragma once
#include "Melee.h"
class Sword :
    public Melee
{
private:
public:
    Sword();
    ~Sword();

    void Update(const Vector2f centerPos, const Vector2f& mousePosView);
    void Render(RenderTarget& target);
};

