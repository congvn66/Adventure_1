#pragma once

#include "GameState.h"
#include "MainMenuState.h"

using namespace sf;
using namespace std;

class Game
{
private:
	//variables
	RenderWindow* window;
	Event event;
	float deltaTime;
	Clock clock;
	ContextSettings settings;
	bool fullscreen;
	unsigned AALevel;

	vector <VideoMode> videoModes;

	// just like powerpoint presentation, 
	// for ex: if u click "Exit" the GameState 
	// will be pop out and reveal other States
	stack <State*> states; 


	//supported keys in game
	map <string, int> supportedKeys;

	//init
	void InitVal();
	void InitWindow();
	void InitStates();
	void InitKeys();

public:
	//constructor & deconstructor
	Game();
	~Game();

	void UpdateDeltaTime();

	//right now this just the event loop.
	void Update();

	//tf this same with Draw;
	void Render();

	//contain game loop
	void Run();

	//contain event loop
	void UpdateSFMLEvent();
};

