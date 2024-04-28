#pragma once
#include "AIFollow.h"
class AIComponent
{
private:
	Entity& self;
	Entity& entity;

public:
	AIComponent(Entity& self, Entity& entity);
	~AIComponent();

	void Update(const float& dt);
};

