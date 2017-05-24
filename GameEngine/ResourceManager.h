#pragma once

#include <map>
#include "GLTexture.h"
#include "Sprite.h"
/*
@brief Texture Cache
*/

class TextureCache
{
public:
	GLTexture GetTexture(std::string texturePath);


private:
	std::map<std::string, GLTexture> _textureMap;
};

class SpriteCache
{
public:
	Sprite GetSprite(std::string spritePath);

private:
	std::map<std::string, Sprite> _spriteMap;
};


class ResourceManager
{
public:
	static GLTexture GetTexture(std::string texturePath);
private:
	static TextureCache _textureCache;
};


