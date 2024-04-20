#pragma once

#include "State.h"
#include "TileMap.h"
#include "Gui.h"

class TileMap;
class Tile;
class State;
class StateData;

class EditorMode
{
private:
protected:
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
	EditorMode(StateData* stateData, TileMap* tileMap, Font* font);
	~EditorMode();

    virtual void UpdateInput(const float& deltaTime)=0;
    virtual void UpdateGui(const float& deltaTime)=0;
    virtual void Update(const float& deltaTime)=0;

    virtual void Render(RenderTarget* target = nullptr)=0;
    virtual void RenderGui(RenderTarget& target)=0;

};

