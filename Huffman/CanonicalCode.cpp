#include "CanonicalCode.h"
#include <algorithm>
#include <memory>

CanonicalCode::CanonicalCode(std::vector<uint32_t>& codeLens)
{
	_codeLens = codeLens;
}

//đọc code length và xây dựng lại cây
CodeTree CanonicalCode::toCodeTree()
{
	//duyệt từ cuối về đầu (để sắp xếp theo thứ tự chữ cái giảm dần)
	//và duyệt từ code length dài nhất (ít xuất hiện nhất) đầu tiên
	//code len max là 256 nên uint32 là đủ
	uint32_t maxCodeLen = *std::max_element(_codeLens.begin(), _codeLens.end());

	std::vector<std::unique_ptr<Node>> node;
	for (uint32_t i = maxCodeLen; i >= 0; i--)
	{
		std::vector<std::unique_ptr<Node>> nodeTmp;

		if (i > 0)
		{
			//duyệt tìm kiếm tất cả các code có cùng lenght (cùng độ cao trong cây huff)
			for (uint32_t j = 0; j < _codeLens.size(); j++)
			{
				//vì 1 mã tương ứng 1 kí tự nên đều là leaf
				if (i == _codeLens[j])
					nodeTmp.push_back(std::unique_ptr<Node>(new Leaf(j)));
			}
		}

		//mỗi tầng đều có lá & cha hoặc lá & lá hoặc lá & cha
		//đều ít nhất là 2 node
		//nên bắt cặp các node trong mảng node
		//các node cha được sinh ra đều nằm sau node con
		//để cho con bắt cặp trước (vẽ ra sẽ rõ hơn)
		for (int j = 0; j < node.size(); j += 2)
		{
			nodeTmp.push_back(std::unique_ptr<Node>(
				new Internal(std::move(node[j]), std::move(node[j + 1]))));
		}
		node = std::move(nodeTmp);

		//vì khai báo kiểu uint nên ko âm đc
		if (i == 0)
			break;
	}

	if (node.size() != 1)
		throw std::logic_error("ton tai 2 node root");

	Internal* root = dynamic_cast<Internal*>(node[0].release());
	CodeTree codeTree(std::move(*root));

	return codeTree;
}

uint32_t CanonicalCode::getCodeLength(uint32_t symbol)
{
	return (_codeLens[symbol]);
}