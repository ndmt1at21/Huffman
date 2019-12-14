/********************************************************
* Author: Nguyễn Đức Minh Trí							*
* Function: thao tác giải nén file                      *
* Date: 12/11/2019										*
********************************************************/

#pragma once
#include <string>
#include "CodeTree.h"
#include "HuffmanCoder.h"
#include <fstream>
#include "Directory.h"
#include "CanonicalCode.h"
#include "FastFstream.h"

class HuffmanDecompress
{
private:
	f_ifstream _fileCompressed; //file compressed
	std::string _dirOut; //link folder where file be decompress

public:
	HuffmanDecompress(std::string linkFileDecompress, std::string dirOut);
	~HuffmanDecompress();

	//giải nén 1 file
	int decompressFile();

	//giải nén folder lẫn file
	//return 1: thành công, 0: thất bại
	bool decompress();
};

