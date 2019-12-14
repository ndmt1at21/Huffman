/**************************************************************
* Author: Nguyễn Đức Minh Trí							      *
* Function: Chuyển từ bảng codelen về cây (dạng canonical)    *
* Canonical code len giúp chuyển từ code len về cây huffman   *
* mà không cần lưu cả cây                                     *
* Date: 05/12/2019									      	  *
**************************************************************/

#pragma once
#include <iostream>
#include <vector>
#include "CodeTree.h"

class CanonicalCode
{
private:
	std::vector<uint32_t> _codeLens;
	
public:
	CanonicalCode(std::vector<uint32_t>& codeLens);
	
	//đọc code length và xây dựng lại cây
	CodeTree toCodeTree();

	//get code length
	uint32_t getCodeLength(uint32_t symbol);
};

