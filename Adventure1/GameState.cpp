#include "GameState.h"

GameState::GameState(RenderWindow* window)
	:State(window)
{
}

GameState::~GameState()
{
}

void GameState::EndState()
{
	cout << "end.";
}

void GameState::Update(const float& deltaTime)
{
	this->UpdateKeybinds(deltaTime);
	
	this->player.Update(deltaTime);
}

void GameState::Render(RenderTarget* target)
{
	this->player.Render(target);
}

void GameState::UpdateKeybinds(const float& deltaTime)
{
	this->CheckQuit();
}
