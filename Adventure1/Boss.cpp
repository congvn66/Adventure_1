#include "stdafx.h"
#include "Boss.h"

//192x128

Boss::Boss(float x, float y, Texture& textureSheet, EnemySpawner& enemySpawner, Entity& player)
	:Enemy(enemySpawner)
{
	this->InitVal();
	this->InitGui();
	//create abilities????
	this->InitComponents();
	this->CreateHitboxComponent(this->sprite, 250.f, 100.f, 192.f*4-450, 168.f*4-350); //hitbox
	this->CreateMovementComponent(5000.f, 2600.f, 1000.f); //move
	this->CreateAnimationComponent(textureSheet);     //animation
	this->CreateAttributeComponent(1);
	this->GenerateAttributes(this->attributeComponent->level,4);

	this->SetPos(x, y);
	this->InitAnimation();

	this->follow = new AIFollow(*this, player, 150.f*sqrt(2));
}

Boss::~Boss()
{
	delete this->follow;
}

void Boss::InitVal()
{
}

void Boss::InitComponents()
{
}
void Boss::InitAnimation()
{
	//add animation
	this->animationComponent->AddAnimation("IDLE", 80.f, 0, 0, 5, 0, 192, 128);
	this->animationComponent->AddAnimation("WALK_LEFT", 80.f, 1, 1, 9, 1, 192, 128);
	this->animationComponent->AddAnimation("WALK_RIGHT", 80.f, 0, 4, 3, 4, 192, 128);
	this->animationComponent->AddAnimation("WALK_UP", 80.f, 0, 0, 5, 0, 192, 128);
	this->animationComponent->AddAnimation("WALK_DOWN", 80.f, 0, 0, 5, 0, 192, 128);
	this->animationComponent->AddAnimation("ATTACK", 50.f, 0, 4, 4, 4, 192, 128);
}

void Boss::InitGui()
{
	this->hpBar.setFillColor(Color::Red);
	this->hpBar.setSize(Vector2f(400.f, 10.f));
	this->hpBar.setPosition(this->sprite.getPosition());
}

void Boss::InitAI()
{
}

void Boss::UpdateAnimation(const float& dt)
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

	if (this->dmgTimer.getElapsedTime().asMilliseconds() <= this->dmgTimerMax)
	{
		this->sprite.setColor(Color::Red);
	}
	else
	{
		this->sprite.setColor(Color::White);
	}
}

void Boss::Update(const float& deltaTime, Vector2f& mousePosView, const View& view)
{
	Enemy::Update(deltaTime, mousePosView, view);
	//update pos with movement input
	this->movementComponent->Update(deltaTime);

	//update gui
	this->hpBar.setSize(Vector2f(400.f * (static_cast<float>(this->attributeComponent->hp) / static_cast<float>(this->attributeComponent->hpMax)), 10.f));
	this->hpBar.setPosition(Vector2f(this->sprite.getPosition().x +200.f, this->sprite.getPosition().y + 80.f));

	//animation update
	this->UpdateAnimation(deltaTime);

	//hitbox update
	this->hitboxComponent->Update();

	//AI
	this->follow->Update(deltaTime);
}
void Boss::Render(RenderTarget& target, Shader* shader, const bool showHitBox)
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