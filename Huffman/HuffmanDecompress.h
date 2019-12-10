#pragma once
#include <string>
#include "CodeTree.h"
#include "HuffmanCoder.h"
#include <fstream>
#include "Directory.h"
#include "CanonicalCode.h"

class HuffmanDecompress
{
private:
	std::ifstream _inFile; //file compressed
	std::string _dirOut; //link folder where file be decompress

public:
	HuffmanDecompress();
	HuffmanDecompress(std::string linkInFile, std::string dirOut);

	int decompressFile();
	bool decompress();
};

