/********************************************************
* Author: Nguyễn Đức Minh Trí							*
* Function: thao tác nén file chính                     *
* Date: 12/11/2019										*
********************************************************/

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

	//nén 1 file
	int compressFile(std::string shortLink);

	//nén folder
	//return: 1 thành công, 0 không thành công
	bool compress();
};

