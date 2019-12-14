#include "MyUltility.h"

void erase_space(std::string& str)
{
	str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
}

void help()
{
	std::cout << "Cu phap: ttzip <chuc nang> <link file/folder input> <link file/folder output>\n";
	std::cout << "<chuc nang>: -c (compress), -d (decompress)\n";
	std::cout << "Vi du cu phap nen: ttzip -c \"D:/C++/test.txt\" \"D:/C++/test.ttzip\"\n";
}

void credit()
{
	std::cout << "HCMUS - 18CTT5B - Cau truc du lieu & giai thuat\n";
	std::cout << "GVHD: Nguyen Thanh An\n";
	std::cout << "Thanh vien:\n";
	std::cout << "Nguyen Duc Minh Tri\t18120612\n";
	std::cout << "Trieu Trang Tong\t18120602\n";
	std::cout << "Cap nhat lan cuoi:\t14/12/2019\n";
}