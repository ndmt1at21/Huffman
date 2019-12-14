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

	//1 thành công, 0 không thành công
	int compressFile(std::string shortLink);
	bool compress();
};

