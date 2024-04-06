#include "stdafx.h"
#include "Game.h"

using namespace sf;

int main()
{
    Game game;
    game.Run();
    return 0;
}
//what is happening right here:
// "Game game" : game constructor it create: a window (by InitWindow()), a game's states stack (only 1 element is added bcs i think game state just have in or out).
//"game.Run()": contain game loop (while window is open)
//            ---> update deltaTime;
//            ---> event loop
//                ---> check things in event loop
//            ---> game's states stack
//                ----> check top thing in stack (will the state take any input? what next?), update it (by Update(deltaTime) in GameState.h)
//            ---> draw things like the old project.

