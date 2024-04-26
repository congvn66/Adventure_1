#pragma once

#include "State.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "PlayerGUI.h"
#include "Sword.h"
#include "TextTagSystem.h"


class Player;
class Orc;

//state of the window when we in the game
class GameState :
    public State
{
private:
    //view things
    View view;
    RenderTexture renderTexture; //actual canvas avoiding screen tearing
    Sprite renderSprite;
    Vector2i viewGridPos;
    Shader coreShader;
    TileMap* tileMap;

    //player things
    Player* player;
    PlayerGUI* playerGUI;

    //pmenu
    Font font;
    PauseMenu* pauseMenu;

    EnemySystem *enemySystem;

    vector <Enemy*> activeEnemies;

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
    void InitEnemySystem();
public:
    GameState(StateData* stateData);
    ~GameState();
    
    void UpdatePlayer(const float& dt);
    void UpdateCombatAndEnemies(const float& dt);
    void UpdateView(const float& deltaTime);
    void UpdateInput(const float& dt);
    void UpdatePlayerGUI(const float& deltaTime);
    void UpdatePauseMenuButton();
    void UpdateTileMap(const float& dt);
    void UpdatePlayerInput(const float& deltaTime);
    void UpdateCombat(Enemy* enemy, const int index, const float dt);
    void Update(const float& deltaTime);
    void Render(RenderTarget* target = nullptr);
};

