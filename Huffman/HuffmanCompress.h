#pragma once
#include "HuffmanCoder.h"
#include "CodeTree.h"
#include "FrequencyTable.h"
#include "Directory.h"
#include <fstream>
#include <string>
#include "CanonicalCode.h"
#include "FastFstream.h"

class HuffmanCompress
{
private:
	std::string _dirIn; //file or folder
	f_ofstream _fileCompress; //file compressed

public:
	HuffmanCompress(std::string dirIn, std::string linkFileCompress);
	~HuffmanCompress();

	//1 th�nh c�ng, 0 kh�ng th�nh c�ng
	int compressFile(std::string shortLink);
	bool compress();
};

