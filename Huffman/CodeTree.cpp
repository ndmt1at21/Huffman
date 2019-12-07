#include "CodeTree.h"
#include <exception>

CodeTree::CodeTree(std::unique_ptr<Node>&& root)
{
	_root = std::move(root);
	
	//tạo ra 1 mảng 2 chiều gồm 257 dòng, mỗi dòng trống
	_codes = std::vector<std::vector<char>>(NUMBER_CHARACTER, std::vector<char>());
}

CodeTree::~CodeTree()
{
}

void CodeTree::buildListCode(const Node* node, std::vector<char> codePrefix)
{
	//node internal (node cha) có 2 con
	//sử dụng quay lui duyệt đến cuối gặp nút là thì đưa code vào codes
	//và quét hết các lá khác
	//phương thức get dùng để trả về 1 con trỏ quản lý vùng nhớ từ smart pointer
	if (dynamic_cast<const Internal*>(node) != NULL)
	{
		const Internal* interNode = dynamic_cast<const Internal*>(node);
		codePrefix.push_back(0);
		buildListCode(interNode->_lchild.get(), codePrefix);
		codePrefix.pop_back();

		codePrefix.push_back(1);
		buildListCode(interNode->_rchild.get(), codePrefix);
		codePrefix.pop_back();
	}
	else if (dynamic_cast<const Leaf*>(node) != NULL)
	{
		const Leaf* leaf = dynamic_cast<const Leaf*>(node);

		//kí tự truyền vào không hợp lệ
		if (leaf->_symbol < 0 || leaf->_symbol > 255)
			throw std::logic_error("Ky tu khong duoc ho tro");

		//symbol đã có mã code điền vào rồi, điền lại ko hợp lại
		if (!_codes[leaf->_symbol].empty())
			throw std::logic_error("Ma code ky tu da ton tai");

		//nếu đúng tất cả thì điền mà code vào vị trí symbol 
		_codes[leaf->_symbol] = codePrefix;
	}
}

std::vector<char> CodeTree::getCode(uint32_t symbol)
{
	std::vector<char> code;

	if (!_codes[symbol].empty())
		code = _codes[symbol];

	return code;
}

uint32_t CodeTree::getCodeLenght(uint32_t symbol)
{
	return (getCode(symbol).size());
}

std::vector<uint32_t> CodeTree::getCodeLens()
{
	//0 -> kí tự không xuất hiện
	std::vector<uint32_t> codeLens(NUMBER_CHARACTER, 0);

	for (int sym = 0; sym < NUMBER_CHARACTER; sym++)
		codeLens[sym] = _codes[sym].size();

	return codeLens;
}