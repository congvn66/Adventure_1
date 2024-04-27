#pragma once
#include "Weapon.h"
class Melee :
    public Weapon
{
protected:
    
public:
    Melee(unsigned dmgMin, unsigned dmgMax, unsigned range, unsigned level, unsigned value, string texFile);
    ~Melee();

    virtual void Generate(const unsigned lvMax, const unsigned lvMin);
    virtual void Update(const Vector2f centerPos, const Vector2f& mousePosView) = 0;
    virtual void Render(RenderTarget& target) = 0;
    virtual Melee* clone()=0;
};

