#include "Node.h"

Node::~Node() {}


Leaf::Leaf(uint32_t symbol) :_symbol(symbol) {}


Internal::Internal(std::unique_ptr<Node>&& lchild, std::unique_ptr<Node>&& rchild)
	: _lchild(std::move(lchild)), _rchild(std::move(rchild)) {}

Internal::Internal(Node* lchild, Node* rchild)
	: _lchild(std::unique_ptr<Node>(lchild)), _rchild(std::unique_ptr<Node>(rchild)) {}

NodeWithFreq::NodeWithFreq()
	: _symbol(0), _freq(0) {}


NodeWithFreq::NodeWithFreq(Node* node, uint32_t sym, uint64_t freq)
	: _node(std::unique_ptr<Node>(node)), _symbol(sym), _freq(freq) {}


bool NodeWithFreq::operator<(const NodeWithFreq& other) const
{
	if (_freq > other._freq)
		return true;
	else if (_freq < other._freq)
		return false;
	else
	{
		if (_symbol > other._symbol)
			return true;
		else if (_symbol < other._symbol)
			return false;
	}

	return false;
}