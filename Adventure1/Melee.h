#pragma once
#include "Weapon.h"
class Melee :
    public Weapon
{
protected:
    
public:
    Melee(unsigned value, string texFile);
    ~Melee();

    virtual void Update(const Vector2f centerPos, const Vector2f& mousePosView) = 0;
    virtual void Render(RenderTarget& target) = 0;
    virtual Melee* clone()=0;
};

