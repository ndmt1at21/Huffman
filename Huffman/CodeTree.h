#pragma once
#include <iostream>
#include <vector>
#include "Node.h"
#include <memory>
#include <utility>

#define NUMBER_CHARACTER 257

class CodeTree
{
public:
	//giữ nút gốc của cây
	 Internal _root;

	//lưu mã code của các ký tự sau khi xây dựng xong
	//là 1 mảng 2 chiều, với 1 dòng là một mã code ex. {0, 1, 1}
	std::vector<std::vector<char>> _codes;

public:
	CodeTree(Internal&& root);
	//tai sao bo ham huy vao loi bi loi trturn o frequency table

	//tạo 1 list mã code của ký tự
	//hàm hỗ trợ lưu cho đệ quy
	//tạo 1 list mã code của ký tự
	void buildListCode(const Node* node, std::vector<char>& codePrefix);

	//get Root
	Internal* getRoot();

	//trả về mã code của 1 kí tự
	const std::vector<char>& getCode(uint32_t symbol);
};

