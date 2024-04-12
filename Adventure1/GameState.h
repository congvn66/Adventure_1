#pragma once
#include "Player.h"
#include "State.h"
#include "PauseMenu.h"
#include "TileMap.h"

//state of the window when we in the game
class GameState :
    public State
{
private:
    View view;
    RenderTexture renderTexture; //actual canvas avoiding screen tearing
    Sprite renderSprite;

    Player* player;

    Font font;
    PauseMenu* pauseMenu;

    TileMap* tileMap;

    //init
    void InitDeferredRender();
    void InitView();
    void InitKeybinds();
    void InitTexture();
    void InitPlayer();
    void InitFont();
    void InitPauseMenu();
    void InitTileMap();
public:
    GameState(StateData* stateData);
    ~GameState();
    
    void UpdateView(const float& deltaTime);
    void UpdateInput(const float& dt);
    void Update(const float& deltaTime);
    void UpdatePauseMenuButton();
    void UpdateTileMap(const float& dt);
    void Render(RenderTarget* target = nullptr);
    void UpdatePlayerInput(const float& deltaTime);
};

