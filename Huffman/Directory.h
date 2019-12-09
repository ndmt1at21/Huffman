#pragma once
#include <cstring>
#include <io.h>
#include <iostream>
#include <vector>
#include <direct.h>
#include <string>
#include <fstream>
#include <direct.h>

class Directory
{
public:
	//trả về đường dẫn rút gọn
	//VD: linkDir: D:/C++/Huffman (trong thu muc co file abc.txt)
	//-> result: /Huffman/abc.txt (ko cần có ổ đĩa)
	static std::vector<std::string> getLinkFiles(std::string linkDir); //folder or file
	static std::string getFileName(std::string linkFile);
	
	//tạo đường dẫn tới địa chỉ của file
	//chức năng: tạo folder chứa file
	static void makeDir(std::string linkFile);

private:
	static void list(const char* dir, std::string currentLink, std::vector<std::string>& linkFiles);
};

