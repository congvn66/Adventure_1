#pragma once
#include "Entity.h"
class Player :
    public Entity
{
private:
    //val

    //init
    void InitVal();
    void InitComponents();

public:
    //con & de
    Player(float x, float y, Texture& texture);
    ~Player();
};

