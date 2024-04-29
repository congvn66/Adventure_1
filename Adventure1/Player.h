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
    bool initAttack;
    bool attacking;
    Weapon* weapon;

    //init
    void InitVal();
    void InitComponents(); // init its own abilities

    //timer to take dmg from enemies
    Clock dmgTimer;
    Int32 dmgTimerMax;


public:
    //con & de
    Player(float x, float y, Texture& textureSheet);
    ~Player();
     Weapon* GetWeapon() const;
    void InitInventory();
    void InitAnimation();
    void InitWeapon();
    AttributeComponent* GetAttributeComponent();
    void LoseHP(const int hp);
    void LoseEXP(const int exp);
    void GainHP(const int hp);
    void GainEXP(const int exp);
    const bool& GetInitAttack() const;
    const bool GetDmgTimer();
    const unsigned GetDmg() const;
    void SetInitAttack(const bool initAttack);
    const string ToStringCharTab() const;
    void UpdateAnimation(const float& dt);
    virtual void Update(const float& deltaTime, Vector2f& mousePosView, const View& view);
    virtual void Render(RenderTarget& target, Shader* shader=nullptr,const bool showHitBox=false);
};

