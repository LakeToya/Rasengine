#include "stdafx.h"
#include "ImageLoader.h"
#include "ResourceManager.h"
#include <iostream>

TextureCache ResourceManager::_textureCache;

GLTexture TextureCache::GetTexture(std::string texturePath)
{
	auto it = _textureMap.find(texturePath);
	if (it == _textureMap.end())
	{
		//Load Texture
		GLTexture newTexture = ImageLoader::LoadImage(texturePath);
		
		//Insert into map
		_textureMap.insert(make_pair(texturePath, newTexture));
		newTexture.count = 1;
		std::cout << "Loaded Cache NewTexture\n"<< std::endl;
		return newTexture;
	}
	std::cout << "Loaded Cache UsedTexture\n" << std::endl;
	//Increase Count
	it->second.count++;
	return it->second;
}

GLTexture ResourceManager::GetTexture(std::string texturePath)
{
	return _textureCache.GetTexture(texturePath);
}
