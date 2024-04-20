#pragma once
#include "State.h"
#include "Gui.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "EditorMode.h"

class EditorMode;
class StateData;

enum EditorModes {DEFAULT_MODE=0, ENEMY_MODE};

using namespace gui;

class EditorState :
    public State
{
private:
    //tile shit
    View view;//cam
    TileMap* tileMap;
    
    //pmenu
    PauseMenu* pauseMenu;
    Font font;

    //button elements
    std::map<string, Button*> buttons;

    vector <EditorMode*> modes; 
    float camSpeed;

    //init
    void InitView();
    void InitVal();
    void InitKeybinds();
    void InitFont();
    void InitButton();
    void InitPauseMenu();
    void InitGui();
    void InitTileMap();

    void InitMode();
public:
    //constructor, deconstructor
    EditorState(StateData* stateData);
    ~EditorState();

    //just look in cpp file.
    void UpdateGui(const float& deltaTime);
    void UpdateEditorInput(const float deltaTime);
    void Update(const float& deltaTime);
    void UpdateInput(const float& deltaTime);
    void UpdateButton();
    void Render(RenderTarget* target = nullptr);
    void RenderGui(RenderTarget& target);
    void RenderButtons(RenderTarget& target);
    void UpdatePauseMenuButton();
};

