#pragma once
#include "Item.h"
class Weapon :
    public Item
{
private:
    void InitVal();
    void InitCooldown();
protected:
    unsigned range;
    Sprite weaponSprite;
    Texture weaponTexture;
    unsigned damageMin;
    unsigned damageMax;

    float cooldown; // attacking timer
    float cooldownMax;
    float cooldownAddition;
public:
    Weapon(unsigned value, string texFile);
    ~Weapon();

    const unsigned& GetDamageMin() const;
    const unsigned& GetDamageMax() const;
    const unsigned& GetRange() const;

    virtual Item* clone()=0;
    virtual void Update(const Vector2f centerPos, const Vector2f& mousePosView)=0;
    virtual void Render(RenderTarget& target)=0;
};

