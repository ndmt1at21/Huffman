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
	//trả về đường dẫn của tất cả các file trong folder
	//nếu là file thì trả về đường dẫn file đó
	//trả về link rút gọn
	static std::vector<std::string> getLinkFiles(std::string linkDir); //folder or file
	static std::string getFileName(std::string linkFile);
	
	//tạo đường dẫn tới địa chỉ của file
	//chức năng: tạo folder chứa file
	static void makeDir(std::string linkFile);

private:
	static void list(const char* dir, std::string currentLink, std::vector<std::string>& linkFiles);
};

