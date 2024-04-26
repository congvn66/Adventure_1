#pragma once
#include "Item.h"
class Weapon :
    public Item
{
private:
    void InitVal();

protected:
    unsigned range;
    Sprite weaponSprite;
    Texture weaponTexture;
    unsigned damageMin;
    unsigned damageMax;

    Clock atkTimer;
    Int32 atkTimerMax;
public:
    Weapon(unsigned value, string texFile);
    ~Weapon();

    const unsigned& GetDamageMin() const;
    const unsigned& GetDamageMax() const;
    const unsigned& GetRange() const;
    const bool GetAtkTimer();

    virtual Item* clone()=0;
    virtual void Update(const Vector2f centerPos, const Vector2f& mousePosView)=0;
    virtual void Render(RenderTarget& target)=0;
};

