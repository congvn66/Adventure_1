#include "stdafx.h"
#include "DefaultMode.h"

void DefaultMode::InitVal()
{
	this->layer = 0;
	this->texRect = IntRect(0, 0, static_cast<int>(this->stateData->gridSize),
		static_cast<int>(this->stateData->gridSize));
	this->collision = false;
	this->type = TileType::DEFAULT;
	this->tileAddLock = false;
}

void DefaultMode::InitGui()
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

	//preview
	this->selectorRect.setTexture(this->tileMap->GetTileSheet());
	this->selectorRect.setTextureRect(this->texRect);

	//texture selector
	this->texSelector = new gui::TextureSelector(20.f, 20.f, 1600.f, 800.f, this->stateData->gridSize,
		this->tileMap->GetTileSheet(), *this->editorStateData->font, "Hide");
}

DefaultMode::DefaultMode(StateData* stateData, TileMap* tileMap, EditorStateData* editorStateData)
	:EditorMode(stateData,tileMap,editorStateData)
{
	this->InitVal();
	this->InitGui();	
}

DefaultMode::~DefaultMode()
{
	delete this->texSelector;
}

void DefaultMode::UpdateInput(const float& deltaTime)
{
	//add tiles
	if (Mouse::isButtonPressed(Mouse::Left) && this->GetKeyTime()) {
		if (!this->sidebar.getGlobalBounds().contains(Vector2f(*this->editorStateData->mousePosWindow))) {
			if (!this->texSelector->GetActive()) {
				//add
				if (this->tileAddLock) // this dont let user put a tile on a tile.
				{
					if (this->tileMap->TileEmpty(this->editorStateData->mousePosGrid->x, this->editorStateData->mousePosGrid->y, 0))
					{
						this->tileMap->AddTile(this->editorStateData->mousePosGrid->x, this->editorStateData->mousePosGrid->y, 0, this->texRect, this->collision, this->type);
					}
				}
				else
				{
					this->tileMap->AddTile(this->editorStateData->mousePosGrid->x, this->editorStateData->mousePosGrid->y, 0, this->texRect, this->collision, this->type);
				}
			}
			else {
				this->texRect = this->texSelector->GetTexRect();
			}
		}
	}
	//remove
	else if (Mouse::isButtonPressed(Mouse::Right) && this->GetKeyTime()) {
		if (!this->sidebar.getGlobalBounds().contains(Vector2f(*this->editorStateData->mousePosWindow))) {
			if (!this->texSelector->GetActive()) {
				//remove
				this->tileMap->RemoveTile(this->editorStateData->mousePosGrid->x, this->editorStateData->mousePosGrid->y, 0);
			}
		}
	}

	//toggle collision
	if (Keyboard::isKeyPressed(Keyboard::Key(this->editorStateData->keybinds->at("COLLISION"))) && this->GetKeyTime()) {
		if (this->collision == false) {
			this->collision = true;
		}
		else {
			this->collision = false;
		}

	}
	else if (Keyboard::isKeyPressed(Keyboard::Key(this->editorStateData->keybinds->at("TYPE+"))) && this->GetKeyTime()) {
		this->type++;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key(this->editorStateData->keybinds->at("TYPE-"))) && this->GetKeyTime()) {
		if (this->type > 0) {
			this->type--;
		}
	}

	//set tile add lock
	if (Keyboard::isKeyPressed(Keyboard::Key(this->editorStateData->keybinds->at("TILE_LOCK"))) && this->GetKeyTime())
	{
		if (this->tileAddLock)
		{
			this->tileAddLock = false;
		}
		else {
			this->tileAddLock = true;
		}
	}
}

void DefaultMode::UpdateGui(const float& deltaTime)
{
	//texture selector
	this->texSelector->Update(*this->editorStateData->mousePosWindow, deltaTime);
	if (!this->texSelector->GetActive()) {
		//update for the preview tile
		this->selectorRect.setTextureRect(this->texRect);
		this->selectorRect.setPosition(this->editorStateData->mousePosGrid->x * this->stateData->gridSize,
			this->editorStateData->mousePosGrid->y * this->stateData->gridSize); //this for the actual pos
	}

	//set pos 4 the below
	this->cursorText.setPosition(this->editorStateData->mousePosView->x + 100.f, this->editorStateData->mousePosView->y + 50.f);

	//show coordinates & index of the tiles on the tilesheet
	stringstream ss;
	ss << this->editorStateData->mousePosView->x << "/" << this->editorStateData->mousePosView->y << endl << //mouse pos with respect to camera
		this->editorStateData->mousePosGrid->x << "/" << this->editorStateData->mousePosGrid->y << endl <<	//mouse pos with respect to grid
		this->texRect.left << "/" << this->texRect.top << endl <<
		"col: " << this->collision << endl <<
		"type: " << this->type << endl <<
		"tiles: " << this->tileMap->GetLayerSize(this->editorStateData->mousePosGrid->x, this->editorStateData->mousePosGrid->y, this->layer) << endl <<
		"tile lock: " << this->tileAddLock;
	this->cursorText.setString(ss.str());

}

void DefaultMode::Update(const float& deltaTime)
{
	this->UpdateInput(deltaTime);
	this->UpdateGui(deltaTime);
}

void DefaultMode::Render(RenderTarget& target)
{
	this->RenderGui(target);
}

void DefaultMode::RenderGui(RenderTarget& target)
{
	if (!this->texSelector->GetActive()) {
		//texture selector
		target.setView(*this->editorStateData->view);
		target.draw(this->selectorRect);
	}
	target.setView(this->stateData->window->getDefaultView());
	this->texSelector->Render(target);
	//sidebar
	target.draw(this->sidebar);

	//cursor text
	target.setView(*this->editorStateData->view);
	target.draw(this->cursorText);
}
