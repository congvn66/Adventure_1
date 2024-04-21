#pragma once
#include "State.h"
#include "Gui.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "EditorMode.h"
#include "DefaultMode.h"
#include "EnemyMode.h"

class EnemyMode;
class EditorMode;
class StateData;
class EditorStateData;
class DefaultMode;

enum EditorModes {DEFAULT_MODE=0, ENEMY_MODE};

using namespace gui;

class EditorState :
    public State
{
private:
    EditorStateData editorStateData;
    //tile shit
    View view;//cam
    TileMap* tileMap;
    
    //pmenu
    PauseMenu* pauseMenu;
    Font font;

    //button elements
    std::map<string, Button*> buttons;

    vector <EditorMode*> modes; 
    unsigned activeMode;

    float camSpeed;

    //init
    void InitView();
    void InitEditorStateData();
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
    void UpdateModes(const float& deltaTime);
    void RenderModes(RenderTarget& target);
    void Render(RenderTarget* target = nullptr);
    void RenderGui(RenderTarget& target);
    void RenderButtons(RenderTarget& target);
    void UpdatePauseMenuButton();
};

