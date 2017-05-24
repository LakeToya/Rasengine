#include "stdafx.h"
#include "Sprite.h"
#include "ImageLoader.h"
#include "ResourceManager.h"
#include <cstddef>
#include "Vertex.h"


Sprite::Sprite()
{
	_vboID = 0;
}


Sprite::~Sprite()
{
	if (_vboID != 0)
	{
		glDeleteBuffers(1, &_vboID);
	}

}

void Sprite::Init(float x, float y, float w, float h)
{
	_x = x;
	_y = y;
	_width = w;
	_height = h;

	if (_vboID == 0)
	{
		glGenBuffers(1, &_vboID);
	}

	Vertex vertexData[6];

	vertexData[0].SetPosition(x + _width,y + _height);
	vertexData[0].SetUV(1.0f,1.0f);

	vertexData[1].SetPosition(x, y + _height);
	vertexData[1].SetUV(0.0f,1.0f);


	vertexData[2].SetPosition(x, y);
	vertexData[2].SetUV(0.0f,0.0f);


	vertexData[3].SetPosition(x ,y);
	vertexData[3].SetUV(0.0f,0.0f);

	vertexData[4].SetPosition(x + _width,y);
	vertexData[4].SetUV(1.0f,0.0f);


	vertexData[5].SetPosition(x + _width, y + _height);
	vertexData[5].SetUV(1.0f,1.0f);

	for (int i = 0; i < 6;i++)
	{
		vertexData[i].SetColor(255, 255,255, 255);
	}

	glBindBuffer(GL_ARRAY_BUFFER,_vboID);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData),vertexData,GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::LoadTexture(std::string texturePath)
{
	_texture = ResourceManager::GetTexture(texturePath);
}

void Sprite::Draw()
{

	//TODO: Keep track of bind textures
	//So your not rebinding textures

	glBindTexture(GL_TEXTURE_2D, _texture.id);

	//Bind the buffer object
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);

	//Tell opengl that we want to use the first attribute array.
	//We only need one array right now since wea re only using position
	glEnableVertexAttribArray(0);

	//Position Attribute pointer
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE,sizeof(Vertex), (void*)offsetof(Vertex,position));

	//Color Attribute Pointer
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));

	//UV Attribute Pointer
	glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,sizeof(Vertex), (void*)offsetof(Vertex, uv));


	//Draw Vertices
	glDrawArrays(GL_TRIANGLES, 0, 6);

	//Disable the vertex attrib array
	glDisableVertexAttribArray(0);

	//unbind the VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
