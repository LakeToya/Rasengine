#include "stdafx.h"
#include "ImageLoader.h"
#include <SOIL/SOIL.h>
/*
@brief Load Texture
*/


GLTexture ImageLoader::LoadImage(std::string filePath)
{
	GLTexture texture = {};
	unsigned char* image = SOIL_load_image(filePath.c_str(), &texture.width, &texture.height, 0, SOIL_LOAD_RGB);
	if (image == 0)
	{
		printf("Failed to Load image: %s\n" , filePath);
		return texture;
	}
//	texture.id = SOIL_load_OGL_texture(filePath.c_str(),
//		SOIL_LOAD_AUTO,
//		SOIL_CREATE_NEW_ID,
//		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
//	if (texture.id == 0)
//	{
//		printf("Failed to Create Texture: %s\n", filePath);
//	}
//
	glGenTextures(1, &texture.id);
	glBindTexture(GL_TEXTURE_2D, texture.id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture.width, texture.height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//MipMaps
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);

	// Free Up Stuff
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	return texture;
}
