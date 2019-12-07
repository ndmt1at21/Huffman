#pragma once
#include <iostream>
#include <memory>

//node goi chung
class Node
{
public:
	virtual ~Node() {}
};


//node la chi co du lieu la ky tu
class Leaf :public Node
{
public:
	uint32_t _symbol;

	Leaf(uint32_t symbol)
	{
		_symbol = symbol;
	}
};


//node cha, gom 2 nhanh con
class Internal :public Node
{
public:
	std::unique_ptr<Node> _lchild; //khac NULL
	std::unique_ptr<Node> _rchild; //khac NULL

	Internal(std::unique_ptr<Node> lchild, std::unique_ptr<Node> rchild)
		:_lchild(std::move(lchild)), _rchild(std::move(rchild)) {}
};