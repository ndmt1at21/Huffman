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
			return EOF;//?

		const Node* nextNode;

		//đi qua bên phải
		if (tmp == 0)
			nextNode = currentNode->_lchild.get();
		//đi qua bên trái
		else 
			nextNode = currentNode->_rchild.get();

		//nếu chạm đến là thì trả về ký tự 
		const Leaf* leaf = dynamic_cast<const Leaf*>(nextNode);
		if ( leaf != NULL)
			return (leaf->_symbol);

		//nếu là node lá thì gán node hiện tại bằng node tìm đc bên trên
		currentNode = dynamic_cast<const Internal*>(nextNode);
	}
}
