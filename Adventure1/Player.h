#pragma once
#include "Entity.h"
class Player :
    public Entity
{
private:
    //val
    bool attacking;

    //init
    void InitVal();
    void InitComponents(); // init its own abilities

public:
    //con & de
    Player(float x, float y, Texture& textureSheet);
    ~Player();

    AttributeComponent* GetAttributeComponent();
    void LoseHP(const unsigned hp);
    void LoseEXP(const unsigned exp);
    void GainHP(const unsigned hp);
    void GainEXP(const unsigned exp);
    void UpdateAttack();
    void UpdateAnimation(const float& dt);
    virtual void Update(const float& dt);
    virtual void Render(RenderTarget& target);
};

