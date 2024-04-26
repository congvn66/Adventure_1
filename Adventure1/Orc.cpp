#include "stdafx.h"
#include "Orc.h"

Orc::Orc(float x, float y, Texture& textureSheet)
	:Enemy()
{
	this->InitVal();
	//create abilities????
	this->InitComponents();
	this->CreateHitboxComponent(this->sprite, 5.f, 0.f, 16.f * 4 - 15, 16.f * 4); //hitbox
	this->CreateMovementComponent(50.f, 1600.f, 1000.f); //move
	this->CreateAnimationComponent(textureSheet);     //animation
	this->CreateAttributeComponent(1);

	this->SetPos(x, y);
	this->InitAnimation();
	this->InitGui();
}

Orc::~Orc()
{
}

void Orc::InitVal()
{
}

void Orc::InitComponents()
{
}
void Orc::InitAnimation()
{
	//add animation
	this->animationComponent->AddAnimation("IDLE", 80.f, 0, 2, 3, 2, 16, 16);
	this->animationComponent->AddAnimation("WALK_LEFT", 80.f, 0, 5, 3, 5, 16, 16);
	this->animationComponent->AddAnimation("WALK_RIGHT", 80.f, 0, 4, 3, 4, 16, 16);
	this->animationComponent->AddAnimation("WALK_UP", 80.f, 0, 7, 3, 7, 16, 16);
	this->animationComponent->AddAnimation("WALK_DOWN", 80.f, 0, 6, 3, 6, 16, 16);
	this->animationComponent->AddAnimation("ATTACK", 50.f, 0, 4, 4, 4, 16, 16);
}

void Orc::InitGui()
{
	this->hpBar.setFillColor(Color::Red);
	this->hpBar.setSize(Vector2f(70.f, 20.f));
	this->hpBar.setPosition(this->sprite.getPosition());
}

void Orc::UpdateAnimation(const float& dt)
{
	/*this->UpdateAttack();
	if (this->attacking) {
		this->animationComponent->Play("ATTACK", dt, true);
		if (this->animationComponent->IsDone("ATTACK")) {
			this->attacking = false;
		}
	}*/
	//play animation with each state of the player
	if (this->movementComponent->GetState(IDLE)) {
		this->sprite.setScale(4.f, 4.f);
		this->animationComponent->Play("IDLE", dt);
	}
	else if (this->movementComponent->GetState(M_RIGHT))
	{
		this->sprite.setScale(4.f, 4.f);
		this->animationComponent->Play("WALK_RIGHT", dt, this->movementComponent->GetVelocity().x, this->movementComponent->GetMaxSpeed());
	}
	else if (this->movementComponent->GetState(M_LEFT)) {
		this->sprite.setScale(4.f, 4.f);
		this->animationComponent->Play("WALK_LEFT", dt, this->movementComponent->GetVelocity().x, this->movementComponent->GetMaxSpeed());
	}
	else if (this->movementComponent->GetState(M_UP)) {
		this->sprite.setScale(4.f, 4.f);
		this->animationComponent->Play("WALK_UP", dt, this->movementComponent->GetVelocity().x, this->movementComponent->GetMaxSpeed());
	}
	else if (this->movementComponent->GetState(M_DOWN)) {
		this->sprite.setScale(4.f, 4.f);
		this->animationComponent->Play("WALK_DOWN", dt, this->movementComponent->GetVelocity().x, this->movementComponent->GetMaxSpeed());
	}
}

void Orc::Update(const float& dt, Vector2f& mousePosView)
{

	//update pos with movement input
	this->movementComponent->Update(dt);

	//update gui
	this->hpBar.setSize(Vector2f(70.f * (static_cast<float>(this->attributeComponent->hp) / static_cast<float>(this->attributeComponent->hpMax)), 20.f));
	this->hpBar.setPosition(Vector2f(this->sprite.getPosition().x, this->sprite.getPosition().y-10.f));

	//animation update
	this->UpdateAnimation(dt);

	//hitbox update
	this->hitboxComponent->Update();
}
void Orc::Render(RenderTarget& target, Shader* shader, const bool showHitBox)
{

	if (shader)
	{
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", this->GetCenterPos());
		target.draw(this->sprite, shader);
	}
	else
	{
		target.draw(this->sprite);
	}

	target.draw(this->hpBar);

	if (showHitBox)
	{
		this->hitboxComponent->Render(target);
	}
}
