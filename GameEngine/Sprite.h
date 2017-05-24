#pragma once

#include <GL/glew.h>
#include "GLTexture.h"
#include <string>
class Sprite
{
public:
	Sprite();
	~Sprite();

	void Init(float x, float y, float w, float h);
	void LoadTexture(std::string texturePath);
	GLTexture GetTexture() { return _texture; };
	void Draw();

private:
	int _x;
	int _y;
	int _width;
	int _height;

	GLuint _vboID;
	GLTexture _texture;

};

