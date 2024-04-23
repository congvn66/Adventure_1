#pragma once
#include "Item.h"
class Ranged :
    public Item
{
public:
    Ranged(unsigned value);
    ~Ranged();
    virtual Ranged* clone()= 0;
};

