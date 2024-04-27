#include "stdafx.h"
#include "EnemyMode.h"

void EnemyMode::InitGui()
{
	//cursorText
	this->cursorText.setFont(*this->editorStateData->font);
	this->cursorText.setCharacterSize(20);
	this->cursorText.setFillColor(Color::White);
	this->cursorText.setPosition(this->editorStateData->mousePosView->x, this->editorStateData->mousePosView->y);

	//Selector
	this->sidebar.setSize(Vector2f(80, 1080));
	this->sidebar.setFillColor(Color(50, 50, 50, 100));
	this->sidebar.setOutlineColor(Color(200, 200, 200, 150));
	this->sidebar.setOutlineThickness(1.f);
	this->selectorRect.setSize(Vector2f(this->stateData->gridSize, this->stateData->gridSize));
	this->selectorRect.setFillColor(Color(209, 222, 209, 150));
	this->selectorRect.setOutlineThickness(1.0f);
	this->selectorRect.setOutlineColor(Color::Green);
}

void EnemyMode::InitVal()
{
	this->enemyType= 0;
	this->amount=1;
	this->timeToSpawn=60;
	this->maxDis=1000.f;
}

EnemyMode::EnemyMode(StateData* stateData, TileMap* tileMap, EditorStateData* editorStateData)
	:EditorMode(stateData, tileMap, editorStateData)
{
	this->InitVal();
	this->InitGui();
}

EnemyMode::~EnemyMode()
{
}

void EnemyMode::UpdateInput(const float& deltaTime)
{
	//add tiles
	if (Mouse::isButtonPressed(Mouse::Left) && this->GetKeyTime()) {
		if (!this->sidebar.getGlobalBounds().contains(Vector2f(*this->editorStateData->mousePosWindow))) 
		{
			this->tileMap->AddTile(this->editorStateData->mousePosGrid->x, this->editorStateData->mousePosGrid->y,0, this->texRect, 
				this->enemyType, this->amount, this->timeToSpawn, this->maxDis);
		}
	}
	//remove
	else if (Mouse::isButtonPressed(Mouse::Right) && this->GetKeyTime()) {
		if (!this->sidebar.getGlobalBounds().contains(Vector2f(*this->editorStateData->mousePosWindow))) {
			this->tileMap->RemoveTile(this->editorStateData->mousePosGrid->x, this->editorStateData->mousePosGrid->y,0, TileType::SPAWNER);
		}
	}

	//toggle collision
	if (Keyboard::isKeyPressed(Keyboard::Key(this->editorStateData->keybinds->at("TYPE_UP"))) && this->GetKeyTime()) {
		if (Keyboard::isKeyPressed(Keyboard::LShift))
		{
			if (this->enemyType > 0)
			{
				this->enemyType--;
			}
		}
		else if (this->enemyType < 1000)
		{
			this->enemyType++;
		}
		else
		{
			this->enemyType = 0;
		}
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key(this->editorStateData->keybinds->at("AMOUNT_UP"))) && this->GetKeyTime()) {
		if (Keyboard::isKeyPressed(Keyboard::LShift))
		{
			if (this->amount > 0)
			{
				this->amount--;
			}
		}
		else if (this->amount < 1000)
		{
			this->amount++;
		}
		else
		{
			this->amount = 0;
		}
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key(this->editorStateData->keybinds->at("TTS_UP"))) && this->GetKeyTime()) {
		if (Keyboard::isKeyPressed(Keyboard::LShift))
		{
			if (this->timeToSpawn > 0)
			{
				this->timeToSpawn--;
			}
		}
		else if (this->timeToSpawn < 1000)
		{
			this->timeToSpawn++;
		}
		else
		{
			this->timeToSpawn = 0;
		}
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key(this->editorStateData->keybinds->at("MD_UP"))) && this->GetKeyTime()) {
		if (Keyboard::isKeyPressed(Keyboard::LShift))
		{
			if (this->maxDis > 0)
			{
				this->maxDis--;
			}
		}
		else if (this->maxDis < 1000)
		{
			this->maxDis++;
		}
		else
		{
			this->maxDis = 0;
		}
	}
}

void EnemyMode::UpdateGui(const float& deltaTime)
{
	this->selectorRect.setPosition(this->editorStateData->mousePosGrid->x * this->stateData->gridSize,
		this->editorStateData->mousePosGrid->y * this->stateData->gridSize); //this for the actual pos
	this->cursorText.setPosition(this->editorStateData->mousePosView->x + 100.f, this->editorStateData->mousePosView->y + 50.f);

	//show coordinates & index of the tiles on the tilesheet
	stringstream ss;
	ss << 
		"enemy type: " <<this->enemyType<< endl <<
		"amount: " <<this->amount<<endl <<
		"time: " <<this->timeToSpawn<<  endl<< 
		"max dis: " <<this->maxDis<< endl;
	this->cursorText.setString(ss.str());
}

void EnemyMode::Update(const float& deltaTime)
{
	this->UpdateInput(deltaTime);
	this->UpdateGui(deltaTime);
}

void EnemyMode::Render(RenderTarget& target)
{

	this->RenderGui(target);
}

void EnemyMode::RenderGui(RenderTarget& target)
{
	target.setView(*this->editorStateData->view);
	target.draw(this->selectorRect);
	target.draw(this->cursorText);

	//sidebar
	target.setView(target.getDefaultView());
	target.draw(this->sidebar);
}
