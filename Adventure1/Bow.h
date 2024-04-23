#pragma once
#include "Ranged.h"
class Bow :
    public Ranged
{
public:
    Bow(unsigned value);
    ~Bow();

    Bow* clone();
};

