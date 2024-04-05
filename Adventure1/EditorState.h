#pragma once
#include "State.h"
#include "Button.h"

class EditorState :
    public State
{
private:
   
    //button elements
    Font font;
    map<string, Button*> buttons;

    //init
    void InitVal();
    void InitKeybinds();
    void InitFont();
    void InitButton();
    void InitBackground();
public:
    //constructor, deconstructor
    EditorState(RenderWindow* window, map <string, int>* supportedKeys, stack <State*>* states);
    ~EditorState();

    //just look in cpp file.
    void Update(const float& deltaTime);
    void UpdateInput(const float& deltaTime);
    void UpdateButton();
    void Render(RenderTarget* target = nullptr);
    void RenderButtons(RenderTarget* target = nullptr);

};

