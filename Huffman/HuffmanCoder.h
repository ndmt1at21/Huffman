/************************************************************
* Author: Nguyễn Đức Minh Trí							    *
* Function: Các thao tác Enc và Dec ký tự, hỗ trợ cho nén   *
* Date: 08/12/2019										    *
************************************************************/

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

	//encode tree huffman ghi vào file
	void treeEnc();

private:
	//hàm đệ quy hỗ trợ encode tree
	void treeEncRecur(const Node* node);
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

	//xây dựng lại cây huffman từ file đã được encode
	CodeTree toCodeTree();

private:
	//hàm đệ quy, hỗ trợ xây dựng lại huff tree
	Node* treeDec();
};

