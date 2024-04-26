#pragma once
#include "Weapon.h"
class Ranged :
    public Weapon
{
private:

protected:
public:
    Ranged(unsigned value, string texFile);
    ~Ranged();
    virtual void Update(const Vector2f centerPos, const Vector2f& mousePosView) = 0;
    virtual void Render(RenderTarget& target) = 0;
    virtual Ranged* clone()= 0;
};

