#pragma once
#include "Player.h"
#include "State.h"

//state of the window when we in the game
class GameState :
    public State
{
private:
    Player* player;

    void InitKeybinds();
    void InitTexture();
    void InitPlayer();
public:
    GameState(RenderWindow* window, map <string, int>* supportedKeys, stack <State*>* states);
    ~GameState();

    void Update(const float& deltaTime);
    void Render(RenderTarget* target = nullptr);
    void UpdateInput(const float& deltaTime);
};

