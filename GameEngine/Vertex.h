#pragma once

#include <GL/glew.h>
struct Position
{
	float x;
	float y;
};

struct UV
{
	float u;
	float v;
};

struct Color
{
	GLubyte r;
	GLubyte g;
	GLubyte b;
	GLubyte a;
};

struct Vertex
{
	Position position;
	Color color;
	UV uv;

	void SetColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a)
	{
		color.r = r;
		color.b = b;
		color.g = g;
		color.a = a;
	}
	void SetUV(float u, float v)
	{
		uv.u = u;
		uv.v = v;
	}
	void SetPosition(float x, float y)
	{
		position.x = x;
		position.y = y;
	}

};
