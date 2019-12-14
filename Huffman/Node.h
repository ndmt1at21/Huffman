/***********************************************************
* Author: Nguyễn Đức Minh Trí							   *
* Function: định nghĩa và 1 vài phương thức node, leaf     *
* Date: 22/11/2019										   *
***********************************************************/

#pragma once
#include <iostream>
#include <memory>

//node goi chung
class Node
{
public:
	virtual ~Node();
};


//node chỉ có dữ liệu là ký tự
class Leaf :public Node
{
public:
	uint32_t _symbol;
	Leaf(uint32_t symbol);
};


//node cha, gồm 2 nhánh con
class Internal :public Node
{
public:
	std::unique_ptr<Node> _lchild; //khac NULL
	std::unique_ptr<Node> _rchild; //khac NULL

	Internal(std::unique_ptr<Node>&& lchild, std::unique_ptr<Node>&& rchild);
	Internal(Node* lchild, Node* rchild);
};


class NodeWithFreq
{
public:
	std::unique_ptr<Node> _node;
	uint32_t _symbol;
	uint64_t _freq;

public:
	NodeWithFreq();

	//khởi tạo smart pointer _node bằng một con trỏ bình thường
	//con trỏ này vẫn giữ nguyên (nếu nó được 1 biến quản lý)
	NodeWithFreq(Node* node, uint32_t symbol, uint64_t freq);

	//cố tính làm ngược lại để áp dụng cho priority queue
	//vì pri queue dùng toán tử để xem nào lớn nhất ra trước
	//nhưng mình cần nhỏ nhất nên làm ngược lại
	bool operator<(const NodeWithFreq& other) const;
};