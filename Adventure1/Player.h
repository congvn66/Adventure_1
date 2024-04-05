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
    virtual void Update(const float& dt);
};

