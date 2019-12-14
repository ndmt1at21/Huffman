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

	int decompressFile();
	bool decompress();
};

