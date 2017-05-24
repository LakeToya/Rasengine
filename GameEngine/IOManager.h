#pragma once

#include <vector>
class IOManager
{
public:
	static bool readFileToBuffer(std::string filepath,std::vector<unsigned char>& buffer);

};

