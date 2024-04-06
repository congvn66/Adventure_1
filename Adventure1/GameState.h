#pragma once
#include "Player.h"
#include "State.h"
#include "PauseMenu.h"

//state of the window when we in the game
class GameState :
    public State
{
private:
    Player* player;

    Font font;
    PauseMenu* pauseMenu;

    void InitKeybinds();
    void InitTexture();
    void InitPlayer();
    void InitFont();
    void InitPauseMenu();
public:
    GameState(RenderWindow* window, map <string, int>* supportedKeys, stack <State*>* states);
    ~GameState();
    
    void UpdateInput(const float& dt);
    void Update(const float& deltaTime);
    void UpdatePauseMenuButton();
    void Render(RenderTarget* target = nullptr);
    void UpdatePlayerInput(const float& deltaTime);
};

