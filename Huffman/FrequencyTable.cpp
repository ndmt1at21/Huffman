#include "FrequencyTable.h"

#include "FrequencyTable.h"

FrequencyTable::FrequencyTable()
{
	_freqs = std::vector<uint32_t>(NUMBER_CHARACTER);
}

FrequencyTable::FrequencyTable(const FrequencyTable& freqs)
{
	_freqs = freqs._freqs;
}

void FrequencyTable::increase(uint32_t symbol)
{
	if (symbol < 0 || symbol > NUMBER_CHARACTER)
		throw std::logic_error("Ki tu khong duoc ho tro");

	_freqs[symbol]++;
}

CodeTree FrequencyTable::buildHuffTree()
{
	//sử dụng min heap hay sử dụng priority_queue để tạo cây Huffman
	//tham khảo: https://www.geeksforgeeks.org/huffman-coding-greedy-algo-3/
	std::priority_queue<NodeWithFreq> priQueue;

	//tạo các node lá (các ký tự có tần suất > 0)
	for (size_t i = 0; i < _freqs.size(); i++)
		priQueue.push(NodeWithFreq(new Leaf(i), i, _freqs[i]));


	
}

//các hàm hỗ trợ nhẹ =))
//tim kiếm node nhỏ nhất giữa 2 queue
NodeWithFreq findMin(std::queue<NodeWithFreq> q1, std::queue<NodeWithFreq> q2)
{
	NodeWithFreq min;

	if (q1.empty())
		min = popQueue(q2);

	if (q2.empty())
		min = popQueue(q1);

	//nếu cả 2 queue đều có phần tử
	NodeWithFreq front1(q1.front());
	NodeWithFreq front2(q2.front());

	//lấy ký tự có tần suất bé hơn
	if (front1._freq < front2._freq)
		min = popQueue(q1);
	else if (front1._freq > front2._freq)
		min = popQueue(q2);
	//nếu 2 ký tự có cùng tần suất thì ưu tiên ký tự có mã bé hơn
	else
	{
		if (front1._symbol < front2._symbol)
			min = popQueue(q1);
		else
			min = popQueue(q2);
	}

	return min;
}

NodeWithFreq popQueue(std::priority_queue<NodeWithFreq> q)
{
	if (q.empty())
		throw std::logic_error("pop queue rong");

	NodeWithFreq node = std::move(const_cast<NodeWithFreq&&>(q.top()));
	q.pop();

	return node;
}
