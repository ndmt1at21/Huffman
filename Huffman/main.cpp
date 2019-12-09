#include <iostream>
#include "BitIOStream.h"
#include "CodeTree.h"
#include "Endian.h"
#include "FrequencyTable.h"
#include <fstream>

using namespace std;

int main()
{
	ifstream in("D:/C++/test/test.txt");
	BitInputStream bin(in);

	cout << bin.getBit();
}