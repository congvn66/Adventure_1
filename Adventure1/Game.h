#pragma once

#include "GameState.h"
#include "MainMenuState.h"

using namespace sf;
using namespace std;

class Game
{
private:
	//variables
	StateData stateData;
	RenderWindow* window;
	Event event;
	float deltaTime;
	Clock clock;
	ContextSettings settings;
	bool fullscreen;
	unsigned AALevel;
	float gridSize;

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
	void InitKeys();
	void InitStateData();
	void InitStates();

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

