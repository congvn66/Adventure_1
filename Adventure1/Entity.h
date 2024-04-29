#pragma once
//now i know its not enemy :D

#include "MovementComponent.h"
#include "AnimationComponent.h"
#include "HitboxComponent.h"
#include "AttributeComponent.h"
#include "SkillComponent.h"

using namespace std;
using namespace sf;


using namespace sf;

class Entity
{
private:
	void InitVal();

protected:
	Sprite sprite;//now every entity has a sprite

	//component
	AttributeComponent* attributeComponent; // stats
	HitboxComponent* hitboxComponent;	//hitbox	
	MovementComponent* movementComponent;// move 
	AnimationComponent* animationComponent;//animate
	SkillComponent* skillComponent;
public:
	//con & de
	Entity();
	~Entity();

	//it is w it is
	//component stuffs
	void CreateSkillComponent();
	void CreateHitboxComponent(Sprite& sprite, float offsetX, float offsetY, float width, float height);
	void CreateMovementComponent(const float maxSpeed, const float acceleration, 
		const float deceleration);
	void CreateAnimationComponent(Texture& textureSheet);
	void CreateAttributeComponent(const unsigned level);

	virtual MovementComponent* GetMC();
	virtual HitboxComponent* GetHC();
	virtual SkillComponent* GetSC();
	virtual AnimationComponent* GetAniC();
	virtual AttributeComponent* GetAC();

	virtual const float GetDistance(const Entity& entity) const;
	virtual const FloatRect GetNextPosBounds(const float& deltaTime) const;
	virtual const Vector2i getGridPos(const int gridSizeI) const;
	virtual const FloatRect GetGlobalBounds() const;
	virtual const Vector2f& GetPos() const;
	virtual const Vector2f& GetSpritePos() const;
	virtual const Vector2f GetCenterPos() const;
	virtual const Vector2f GetSpriteCenterPos() const;
	virtual void SetPos(const float x, const float y);
	virtual void Move(const float& deltaTime, const float dirX, const float dirY);
	virtual void Update(const float& deltaTime, Vector2f& mousePosView, const View& view)=0;
	virtual void Render(RenderTarget& target,Shader* shader, const bool showHitbox= false)=0;
	virtual void Stop();
	virtual void StopX();
	virtual void StopY();
	//texture 4 each entity
	void SetTexture(Texture& texture);
};

