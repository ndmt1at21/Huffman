#include "Directory.h"
#include <sys/types.h>


std::vector<std::string> getLinkFiles(std::string linkFolder)
{
	std::vector<std::string> files;

	std::string pattern(linkFolder);
	pattern.append("\\*");
	WIN32_FIND_DATA data;
	HANDLE hFind;
	if ((hFind = FindFirstFile(pattern.c_str(), &data)) != INVALID_HANDLE_VALUE) {
		do {
			files.push_back(data.cFileName);
		} while (FindNextFile(hFind, &data) != 0);
		FindClose(hFind);
	}
}

//std::string getFileName(std::string linkFile)
//	{
//
//	}
	
