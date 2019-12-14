#include <iostream>
#include "BitIOStream.h"
#include "CodeTree.h"
#include "Endian.h"
#include "FrequencyTable.h"
#include "Directory.h"
#include "HuffmanCompress.h"
#include "HuffmanDecompress.h"
#include <fstream>
#include "FastFstream.h"
#include <time.h>
#include <ctime>


using namespace std;

int main()
{
	int a;
	cin >> a;

	clock_t start = clock();
	if (a == 0)
	{
		HuffmanCompress zip("D:/C++/test/corpus-title.txt", "D:/C++/test/test.jav");
		zip.compress();
	}
	else
	{
		HuffmanDecompress dezip("D:/C++/test/test.jav", "D:/C++/test/new");
		dezip.decompress();
	}
	clock_t end = clock();
	cout << "Time: " << double(end - start) / CLOCKS_PER_SEC;
}