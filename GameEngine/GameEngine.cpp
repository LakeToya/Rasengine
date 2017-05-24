// GameEngine.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <SDL/SDL.h>
#include <GL/glew.h>
#include "Game.h"

int main(int argc ,char ** argv)
{
	Game game;
	game.Run();


    return 0;
}

