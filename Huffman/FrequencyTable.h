/********************************************************
* Author: Nguyễn Đức Minh Trí							*
* Function: tạo bảng thống kế tần suất xuất hiện các	* 
*			kí tự trong file và các thao tác với bảng	*
* Date: 22/11/2019										*
********************************************************/
#pragma once

#include <iostream>
#include "CodeTree.h"
#include <queue>
#include "Node.h"

class FrequencyTable
{
public:
	std::vector<uint32_t> _freqs;

public:
	FrequencyTable();
	FrequencyTable(std::vector<uint32_t> freqs);

	//tăng tần số xuất hiện của một kí tự symbol
	void increase(uint32_t symbol);

	//trả về một cây Huffman xây dựng từ bảng thống kê
	CodeTree buildHuffTree() const;
};

NodeWithFreq popQueue(std::priority_queue<NodeWithFreq>& q);