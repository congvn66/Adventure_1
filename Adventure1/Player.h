#pragma once
#include "Entity.h"
#include "ItemInclude.h"
#include "Inventory.h"
class Player :
    public Entity
{
private:
    Inventory* inventory;
    //val
    bool attacking;
    Sword* sword;

    //init
    void InitVal();
    void InitComponents(); // init its own abilities

public:
    //con & de
    Player(float x, float y, Texture& textureSheet);
    ~Player();

    const Weapon* GetWeapon() const;
    void InitInventory();
    void InitAnimation();
    void InitWeapon();
    AttributeComponent* GetAttributeComponent();
    void LoseHP(const int hp);
    void LoseEXP(const int exp);
    void GainHP(const int hp);
    void GainEXP(const int exp);
    void UpdateAttack();
    void UpdateAnimation(const float& dt);
    virtual void Update(const float& dt,Vector2f& mousePosView);
    virtual void Render(RenderTarget& target, Shader* shader=nullptr,const bool showHitBox=false);
};

