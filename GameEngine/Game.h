#pragma once

#include "Sprite.h"
#include <SDL/SDL.h>
#include "GLSLProgram.h"
#include "GLTexture.h"
#include <vector>



enum class GameState {
	PLAYING,
	EXIT
};

class Game
{
public:
	Game();
	~Game();


	void Run();
	void GetFPS();
	

private:
	SDL_Event		event;
	GameState		_currentState;
	SDL_Window*		_window;
	int				_screenWidth;
	int				_screenHeight;

	std::vector <Sprite*> _sprites;
	Sprite			_sprite;

	void			Init();
	void			InitShaders();
	void			ProcessInput();
	void			Loop();
	void			Draw();

	GLSLProgram		_colorProgram;

	int				 _desiredFPS;
	float			_time;
	float			_fps;
	float			_frameTime;
};

