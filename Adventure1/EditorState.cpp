#include "EditorState.h"

EditorState::EditorState(RenderWindow* window, map <string, int>* supportedKeys, stack <State*>* states)
	:State(window, supportedKeys, states)
{
	this->InitVal();
	this->InitFont();
	this->InitKeybinds();
	this->InitBackground();
	this->InitButton();
}

void EditorState::InitVal()
{
}



void EditorState::InitKeybinds()
{
	this->keybinds["CLOSE"] = this->supportedKeys->at("ESC");
}

void EditorState::InitFont()
{
	//load font
	if (font.loadFromFile("Assets/Font/ARCADECLASSIC.TTF")) {
		cout << "Editor: Font loaded!" << endl;
	}
	else {
		cout << "Editor: Font failed to load!" << endl;
	}
}

void EditorState::InitButton()
{
	//setting up buttons
	
}

void EditorState::InitBackground()
{

}

EditorState::~EditorState()
{

	//just delete buttons
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

void EditorState::Update(const float& deltaTime)
{
	//it is w it is
	this->UpdateMousePos();

	//handle input by keyboard
	this->UpdateInput(deltaTime);

	//update states of buttons
	this->UpdateButton();
}

void EditorState::Render(RenderTarget* target)
{
	//render editor
	if (target == nullptr) {
		target = this->window;
	}
	//render buttons
	this->RenderButtons(*target);
}

void EditorState::UpdateInput(const float& deltaTime)
{
	if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("CLOSE")))) {
		this->EndState();
	}
}

void EditorState::UpdateButton()
{
	//this how to loop thru all elements in a map?
	//Update mouse
	for (auto& it : this->buttons) {
		it.second->Update(this->mousePosView);
	}
}

void EditorState::RenderButtons(RenderTarget& target)
{
	//this how to loop thru all elements in a map?
	for (auto& it : this->buttons) {
		it.second->Render(target);
	}
}
