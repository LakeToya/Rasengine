#pragma once
#include "GLTexture.h"
#include <string>
class ImageLoader
{
public:
	static GLTexture LoadImage(std::string filePath);

};

