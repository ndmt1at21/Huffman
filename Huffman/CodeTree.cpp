#include "CodeTree.h"
#include <exception>

CodeTree::CodeTree(Internal&& root) :_root(std::move(root))//?? tai sao de vao scope ko dc
{	
	//tạo ra 1 mảng 2 chiều gồm 257 dòng, mỗi dòng trống
	//chứa code của 1 ký tự từ 0-255 (256 quy định EOF)
	_codes = std::vector<std::vector<char>>(NUMBER_CHARACTER, std::vector<char>());
	std::vector<char> codePrefix;
	buildListCode(&_root, codePrefix);
}

void CodeTree::buildListCode(const Node* node, std::vector<char>& codePrefix)
{
	//node internal (node cha) có 2 con
	//sử dụng quay lui duyệt đến cuối gặp nút là thì đưa code vào codes
	//và quét hết các lá khác
	//phương thức get() dùng để trả về 1 pointer quản lý vùng nhớ từ smart pointer
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
		if (leaf->_symbol >= _codes.size())
			throw std::logic_error("Ky tu khong duoc ho tro");

		//symbol đã có mã code điền vào rồi, điền lại ko hợp lại
		if (!_codes[leaf->_symbol].empty())
			throw std::logic_error("Ma code ky tu da ton tai");

		//nếu đúng tất cả thì điền mà code vào vị trí symbol 
		_codes[leaf->_symbol] = codePrefix;
	}
}

//get Root
Internal* CodeTree::getRoot()
{
	return &_root;
}

const std::vector<char>& CodeTree::getCode(uint32_t symbol)
{
	if (_codes[symbol].empty())
		throw std::logic_error("Ky tu khong co ma code");

	return _codes[symbol];
}

std::vector<uint32_t> CodeTree::getCodeLens()
{
	std::vector<uint32_t> lens;
	for (uint32_t i = 0; i < _codes.size(); i++)
		lens.push_back(_codes[i].size());
	return lens;
}
