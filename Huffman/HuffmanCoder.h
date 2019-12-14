/************************************************************
* Author: Nguyễn Đức Minh Trí							    *
* Function: Các thao tác Enc và Dec ký tự, hỗ trợ cho nén   *
* Date: 08/12/2019										    *
************************************************************/

#pragma once
#include "BitIOStream.h"
#include "CodeTree.h"

//đánh dấu là file nén .ttZip
#define MAGIC_NUMBER 0xC77680 

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

public:
	HuffDecoder(BitInputStream& in);
	~HuffDecoder();
	
	//decode 1 ký tự
	int symDec(CodeTree& codeTree);
};

