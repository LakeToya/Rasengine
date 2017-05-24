#include "stdafx.h"
#include "IOManager.h"
#include <fstream>

/*
bool IOManager::readFileToBuffer(std::string filepath,std::vector<unsigned char>& buffer)
{

	std::ifstream file(filepath, std::ios::binary);
	if (file.fail)
	{
		perror(filepath.c_str());
		return false;
	}
	//Seek to end
	file.seekg(0,std::ios::end);

	//get file size in bytes
	int fileSize = file.tellg;
	file.seekg(0, std::ios::beg);

	//Reduce file size by any header bytes that might be present
	fileSize -= file.tellg;

	buffer.resize(fileSize);
	file.read((char*)&buffer[0],fileSize);
	file.close();
	return true;
}
*/