#include "FrequencyTable.h"

FrequencyTable::FrequencyTable()
{
	_freqs = std::vector<uint32_t>(NUMBER_CHARACTER);
}

FrequencyTable::FrequencyTable(std::vector<uint32_t> freqs)
{
	_freqs = freqs;
}

void FrequencyTable::increase(uint32_t symbol)
{
	if (symbol < 0 || symbol > NUMBER_CHARACTER)
		throw std::logic_error("Ki tu khong duoc ho tro");

	if (_freqs[symbol] >= UINT32_MAX)
		throw std::logic_error("Kich thuoc file vuot gioi han ho tro");
	_freqs[symbol]++;
}

CodeTree FrequencyTable::buildHuffTree() const 
{
	//sử dụng min heap hay sử dụng priority_queue để tạo cây Huffman
	//tham khảo: https://www.geeksforgeeks.org/huffman-coding-greedy-algo-3/
	std::priority_queue<NodeWithFreq> priQueue;

	//tạo các node lá (các ký tự có tần suất > 0)
	for (uint32_t i = 0; i < _freqs.size(); i++)
		if (_freqs[i] > 0)
			priQueue.push(NodeWithFreq(new Leaf(i), i, _freqs[i]));

	//xử lí cây trống
	uint32_t i = 0;
	while (priQueue.size() < 2)
	{
		priQueue.push(NodeWithFreq(new Leaf(i), i, 0));
		i++;
	}

	//tạo cây
	while (priQueue.size() > 1)
	{
		NodeWithFreq left = popQueue(priQueue); //be nhat ben trai
		NodeWithFreq right = popQueue(priQueue);

		//push lại node inter vừa mới tạo vào priQueue
		priQueue.push(NodeWithFreq(new Internal(std::move(left._node), std::move(right._node)),
			std::min(left._symbol, right._symbol), uint64_t(left._freq + right._freq)));
	}

	//đến bước này thì trong queue phải còn 1 phần tử duy nhất
	//đó là node cha (root), là internal node
	if (priQueue.size() != 1)
		throw std::logic_error("ton tai tren mot node root");

	NodeWithFreq nodeRoot = popQueue(priQueue);
	Internal* root = dynamic_cast<Internal*>(nodeRoot._node.release());
	CodeTree codeTree(std::move(*root));

	return codeTree;
}

NodeWithFreq popQueue(std::priority_queue<NodeWithFreq>& q)
{
	if (q.empty())
		throw std::logic_error("pop queue rong");

	NodeWithFreq node = std::move(const_cast<NodeWithFreq&&>(q.top()));
	q.pop();

	return node;
}
