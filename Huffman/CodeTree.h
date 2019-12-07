#pragma once
#include <iostream>
#include <vector>
#include "Node.h"
#include <memory>

#define NUMBER_CHARACTER 257

class CodeTree
{
private:
	//giữ nút gốc của cây
	 std::unique_ptr<Node> _root;

	//lưu mã code của các ký tự sau khi xây dựng xong
	//là 1 mảng 2 chiều, với 1 dòng là một mã code ex. {0, 1, 1}
	std::vector<std::vector<char>> _codes;

public:
	CodeTree(std::unique_ptr<Node>&& root);
	~CodeTree();

	//tạo 1 list mã code của ký tự
	//hàm hỗ trợ lưu cho đệ quy
	//tạo 1 list mã code của ký tự
	void buildListCode(const Node* node, std::vector<char> codePrefix);

	//trả về mã code của 1 kí tự
	std::vector<char> getCode(uint32_t symbol);

	//trả về độ dài mã của 1 ký tự
	uint32_t getCodeLenght(uint32_t symbol);

	//trả về độ dài code tương ứng với 256 kí tự trong bảng mã ASCII
	std::vector<std::uint32_t> getCodeLens();
};

