#pragma once
#include "Ranged.h"
class Bow :
    public Ranged
{
public:
    Bow(unsigned value, string texFile);
    ~Bow();

    Bow* clone();
    virtual void Update(const Vector2f centerPos, const Vector2f& mousePosView);
    virtual void Render(RenderTarget& target);
};

