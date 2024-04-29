#include "stdafx.h"
#include "AIFollow.h"

AIFollow::AIFollow(Entity& self, Entity& entity, const float maxDis)
	:AIOption(self, entity)
{
	this->maxDis = maxDis;
}

AIFollow::~AIFollow()
{
}

void AIFollow::Update(const float& dt)
{
	sf::Vector2f moveVec;
	moveVec.x = entity.GetPos().x - self.GetPos().x;
	moveVec.y = entity.GetPos().y - self.GetPos().y;

	float vecLength = sqrt(pow(moveVec.x, 2) + pow(moveVec.y, 2));

	moveVec /= vecLength;

	if ((self.GetPos().x != entity.GetPos().x) && std::abs(vecLength) < maxDis)
	{
		/*cout << this->entity.GetPos().x << " " << this->entity.GetPos().y << endl;
		cout << this->self.GetPos().x << " " << this->self.GetPos().y << endl;
		cout << vecLength << endl;
		cout << moveVec.x << " " << moveVec.y << endl;*/
		self.Move(dt,moveVec.x, moveVec.y);
	}
		
}
