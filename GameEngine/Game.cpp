#include "stdafx.h"
#include "Game.h"
#include "ImageLoader.h"
#include <iostream>
#include <GL/glew.h>

Game::Game() :
	_currentState(GameState::PLAYING),
	_window(nullptr),
	_screenWidth(800),
	_screenHeight(600),
	_time(0.0f),
	_desiredFPS(60.0f)
{

}


Game::~Game()
{
}

void Game::Run()
{
	Init();

	_sprites.push_back(new Sprite());
	_sprites.back()->Init(-1.0f, -0.0f, 1.0f, 1.0f);
	_sprites.back()->LoadTexture("Sprites/underworld.jpg");

	_sprites.push_back(new Sprite());
	_sprites.back()->Init(-1.0f, -1.0f, 1.0f, 1.0f);
	_sprites.back()->LoadTexture("Sprites/underworld.jpg");

	_sprites.push_back(new Sprite());
	_sprites.back()->Init(-0.0f, -1.0f, 1.0f, 1.0f);
	_sprites.back()->LoadTexture("Sprites/underworld.jpg");

	_sprite.Init(-0.9f, -0.5f,1.0f,1.0f);
	_sprite.LoadTexture("Sprites/underworld.jpg");
	Loop();
}

void Game::GetFPS()
{
	static const int NUM_SAMPLES = 10;
	static float frametimes[NUM_SAMPLES];
	static int index = 0;
	static int printCount = 0;

	static float prevTicks = SDL_GetTicks();
	float currentTicks;
	currentTicks = SDL_GetTicks();

	_frameTime = currentTicks - prevTicks;
	frametimes[index % NUM_SAMPLES] = _frameTime;

	prevTicks = currentTicks;

	int count;
	index++;

	if (index < NUM_SAMPLES)
	{
		count = index;
	}
	else
	{
		count = NUM_SAMPLES;
	}
	float frameTimeAverage = 0;
	for (int i = 0; i < count; i++)
	{
		frameTimeAverage += frametimes[i];
	}
	frameTimeAverage /= count;
	if (frameTimeAverage > 0)
	{
		_fps = 1000.0f/frameTimeAverage;
	}
	else
	{
		_fps = 0;
	}
	
	//Print out FPS
	if (printCount > 30)
	{
		std::cout << _fps << std::endl;
		printCount = 0;
	}
	printCount+=1;

}

void Game::Init()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	//Tell SDL to use double buffer window
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	_window = SDL_CreateWindow("GameEngine",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		_screenWidth,_screenHeight,SDL_WINDOW_OPENGL);


	SDL_GLContext glContex = SDL_GL_CreateContext(_window);
	if (glContex == nullptr)
	{
		printf("SDL_GL context could not be created");
	}

	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		printf("Could not initialize GLEW");
	}

	//Set Background Color
	glClearColor(0.0f,0.0f,0.0f,1.0f);

	//Check OpenGL Version
	std::printf("***	OpenGL Version: %s	***", glGetString(GL_VERSION));

	//Enable/Disable VSYNC
	SDL_GL_SetSwapInterval(0);

	InitShaders();
}

void Game::InitShaders()
{
	_colorProgram.CompileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");
	_colorProgram.AddAttribute("vertexPosition");
	_colorProgram.AddAttribute("vertexColor");
	_colorProgram.AddAttribute("vertexUV");
	_colorProgram.LinkShaders();
}

void Game::ProcessInput()
{
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			_currentState = GameState::EXIT;
			break;
		}
	}

}

void Game::Loop()
{
	while (_currentState != GameState::EXIT)
	{
		float startTicks = SDL_GetTicks();


		ProcessInput();
		_time += 0.03f;
		GetFPS();
		Draw();

		float frameTicks = SDL_GetTicks() - startTicks;
		//LimitFPS
		if ((1000.0f / _desiredFPS) > frameTicks)
		{
			SDL_Delay(1000.0f / _desiredFPS - frameTicks);
		}

	}
}

void Game::Draw()
{
	
	//set base depth to zero
	glClearDepth(1.0);

	//clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	_colorProgram.Use();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _sprite.GetTexture().id);
	
	GLuint timeLocation = _colorProgram.GetUnifromLocation("time");
	glUniform1f(timeLocation, _time);

	GLint textureLocation = _colorProgram.GetUnifromLocation("mySampler");	
	glUniform1f(textureLocation, 0);
	
	for (int i = 0; i < _sprites.size();i++)
	{
		_sprites[i]->Draw();
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	_colorProgram.Unuse();

	//swap our buffer and draw everything to screen
	SDL_GL_SwapWindow(_window);
}
