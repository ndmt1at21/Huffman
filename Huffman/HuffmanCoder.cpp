#include "HuffmanCoder.h"
#include <memory>

HuffEncoder::HuffEncoder(BitOutputStream& out, CodeTree& codeTree) 
	: _out(out), _codeTree(codeTree) {}

HuffEncoder::~HuffEncoder() {}

void HuffEncoder::symEnc(uint32_t symbol)
{
	for (char bit : _codeTree.getCode(symbol))
		_out.setBit(int(bit));
}

void HuffEncoder::treeEnc()
{
	treeEncRecur(_codeTree.getRoot());
}

void HuffEncoder::treeEncRecur(const Node* node)
{
	if (dynamic_cast<const Leaf*>(node) != NULL)
	{
		_out.setBit(1);
		_out.setByte(dynamic_cast<const Leaf*>(node)->_symbol);
	}
	else if (dynamic_cast<const Internal*>(node) != NULL)
	{
		const Internal* currentNode = dynamic_cast<const Internal*>(node);
		
		_out.setBit(0);
		treeEncRecur(currentNode->_lchild.get());
		treeEncRecur(currentNode->_rchild.get());
	}
}

HuffDecoder::HuffDecoder(BitInputStream& in)
	:_in(in) {}

HuffDecoder::~HuffDecoder() {}

int HuffDecoder::symDec(CodeTree& codeTree)
{
	const Internal* currentNode = codeTree.getRoot();

	while (true)
	{
		int tmp = _in.getBit();

		if (tmp == EOF)
			return EOF;

		if (tmp == DEF_EOF)
			break;

		const Node* nextNode;

		//đi qua bên phải
		if (tmp == 0)
			nextNode = currentNode->_lchild.get();
		//đi qua bên trái
		else if (tmp == 1)
			nextNode = currentNode->_rchild.get();
		else
			throw std::logic_error("bit chi co 2 gia tri 0 va 1");

		//nếu chạm đến là thì trả về ký tự 
		if (dynamic_cast<const Leaf*>(nextNode) != NULL)
			return (dynamic_cast<const Leaf*>(nextNode)->_symbol);
		//nếu là node lá thì gán node hiện tại bằng node tìm đc bên trên
		else if (dynamic_cast<const Internal*>(nextNode) != NULL)
			currentNode = dynamic_cast<const Internal*>(nextNode);
	}
}

CodeTree HuffDecoder::toCodeTree()
{
	Internal* root = dynamic_cast<Internal*>(treeDec());
	CodeTree codeTree(std::move(*root));
	delete root;

	return codeTree;
}

Node* HuffDecoder::treeDec()
{
	int bit = _in.getBit();

	if (bit == 0)
	{
		Node* lchild = treeDec();
		Node* rchild = treeDec();
		return (new Internal(lchild, rchild));
	}
	else if (bit == 1)
	{
		return (new Leaf(_in.getByte()));
	}

	return NULL;
}

