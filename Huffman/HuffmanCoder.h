#pragma once
#include "BitIOStream.h"
#include "CodeTree.h"

class HuffEncoder
{
private:
	BitOutputStream& _out;
	CodeTree& _codeTree;

public:
	HuffEncoder(BitOutputStream& out, CodeTree& codeTree);
	~HuffEncoder();
	void symEnc(uint32_t symbol);
};

class HuffDecoder
{
private:
	BitInputStream& _in;
	CodeTree& _codeTree;

public:
	HuffDecoder(BitInputStream& in, CodeTree& codeTree);
	~HuffDecoder();
	uint32_t symDec();
};

