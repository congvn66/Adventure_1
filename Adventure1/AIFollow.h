#pragma once
#include "AIOption.h"
class AIFollow :
    public AIOption
{
private:
    float maxDis;
public:
    AIFollow(Entity& self, Entity& entity, const float maxDis);
    ~AIFollow();

    void Update(const float& dt);
};

