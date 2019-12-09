#pragma once
#include <string>
#include <vector>
#include <Windows.h>

class Directory
{
public:
	static std::vector<std::string> getLinkFiles(std::string linkFolder);
	static std::string getFileName(std::string linkFile);
};

