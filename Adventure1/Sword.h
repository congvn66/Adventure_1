#pragma once
#include "Melee.h"
class Sword :
    public Melee
{
private:
public:
    Sword(unsigned dmgMin, unsigned dmgMax, unsigned range, unsigned level,unsigned value, string texFile);
    ~Sword();

    void Update(const Vector2f centerPos, const Vector2f& mousePosView);
    void Render(RenderTarget& target);
    Sword* clone();
};

