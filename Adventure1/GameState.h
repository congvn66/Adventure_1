#pragma once

#include "State.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "PlayerGUI.h"

//state of the window when we in the game
class GameState :
    public State
{
private:
    View view;
    RenderTexture renderTexture; //actual canvas avoiding screen tearing
    Sprite renderSprite;
    Vector2i viewGridPos;

    Player* player;
    PlayerGUI* playerGUI;

    Shader coreShader;

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
    void InitShader();
    void InitPlayerGUI();
    void InitTileMap();
public:
    GameState(StateData* stateData);
    ~GameState();
    
    void Update(const float& deltaTime);
    void UpdateView(const float& deltaTime);
    void UpdateInput(const float& dt);
    void UpdatePlayerGUI(const float& deltaTime);
    void UpdatePauseMenuButton();
    void UpdateTileMap(const float& dt);
    void UpdatePlayerInput(const float& deltaTime);
    void Render(RenderTarget* target = nullptr);
};

