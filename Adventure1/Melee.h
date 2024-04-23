#pragma once
#include "Item.h"
class Melee :
    public Item
{
protected:
    Sprite weaponSprite;
    Texture weaponTexture;
    int damageMin;
    int damageMax;
public:
    Melee(unsigned value);
    ~Melee();

    virtual void Update(const Vector2f centerPos, const Vector2f& mousePosView) = 0;
    virtual void Render(RenderTarget& target) = 0;
    virtual Melee* clone()=0;
};

