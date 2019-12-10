#pragma once
#include "HuffmanCoder.h"
#include "CodeTree.h"
#include "FrequencyTable.h"
#include "Directory.h"
#include <fstream>
#include <string>
#include "CanonicalCode.h"

class HuffmanCompress
{
private:
	std::string _dirIn; //file or folder
	std::ofstream _outFile; //file compressed

public:
	HuffmanCompress(std::string dirIn, std::string linkOutFile);
	~HuffmanCompress();

	//1 th�nh c�ng, 0 kh�ng th�nh c�ng
	int compressFile(std::string shortLink);
	bool compress();
};

