#include "stdafx.h"
#include "AIComponent.h"



AIComponent::AIComponent(Entity& self, Entity& entity)
	:entity(entity), self(self)
{

}

AIComponent::~AIComponent()
{
	//delete this->follow;
}

void AIComponent::Update(const float& dt)
{
	//this->follow->Update(dt);
}
