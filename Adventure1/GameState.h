#pragma once
#include "Player.h"
#include "State.h"

class GameState :
    public State
{
private:
    Player* player;

    void InitKeybinds();
    void InitTexture();
    void InitPlayer();
public:
    //ok, basic things that a state must have:
    GameState(RenderWindow* window, map <string, int>* supportedKeys, stack <State*>* states);
    ~GameState();

    void Update(const float& deltaTime);
    void Render(RenderTarget* target = nullptr);
    void UpdateInput(const float& deltaTime);
};

