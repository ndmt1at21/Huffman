#pragma once
#include "HuffmanCoder.h"
#include "CodeTree.h"
#include "FrequencyTable.h"
#include <fstream>
#include <string>

class HuffmanCompress
{
private:
	std::string _dirIn; //file or folder
	std::ofstream _outFile; //file compressed

public:
	HuffmanCompress(std::string dirIn, std::string linkOutFile);
	~HuffmanCompress();

	//1 thành công, 0 không thành công
	int compressFile(std::string infile);
	int compressFiles();
};

