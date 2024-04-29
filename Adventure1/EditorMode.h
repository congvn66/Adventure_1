#pragma once

#include "State.h"
#include "TileMap.h"
#include "Gui.h"

class TileMap;
class Tile;
class State;
class StateData;

class EditorStateData
{
public:
    EditorStateData() {

    }
    View* view;
    Font* font;

    float* keyTime;
    float* keyTimeMax;

    map <string, int>* keybinds;

    //mouse pos
    Vector2i* mousePosScreen;
    Vector2i* mousePosWindow;
    Vector2f* mousePosView;
    Vector2i* mousePosGrid; // which grid are u on?
};

class EditorMode
{
private:
protected:
    EditorStateData* editorStateData;
	StateData* stateData;
    TileMap* tileMap;
    Font* font;

    void InitView();
    void InitText();
    void InitVal();
    void InitKeybinds();
    void InitFont();
    void InitButton();
    void InitPauseMenu();
    void InitGui();
    void InitTileMap();
public:
	EditorMode(StateData* stateData, TileMap* tileMap, EditorStateData* editorStateData);
	~EditorMode();

    const bool GetKeyTime();
    virtual void UpdateInput(const float& deltaTime)=0;
    virtual void UpdateGui(const float& deltaTime)=0;
    virtual void Update(const float& deltaTime)=0;

    virtual void Render(RenderTarget& target)=0;
    virtual void RenderGui(RenderTarget& target)=0;
};

