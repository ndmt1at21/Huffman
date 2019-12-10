#include <iostream>
#include "BitIOStream.h"
#include "CodeTree.h"
#include "Endian.h"
#include "FrequencyTable.h"
#include "Directory.h"
#include "HuffmanCompress.h"
#include "HuffmanDecompress.h"
#include <fstream>

using namespace std;

int main()
{
	//HuffmanCompress zip("D:/C++/test/test.txt", "D:/C++/test/test.jav");
	//zip.compress();

	HuffmanDecompress dezip("D:/C++/test/test.jav", "D:/C++/test/a");
	dezip.decompress();
}