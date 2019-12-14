#include <iostream>
#include "Directory.h"
#include "HuffmanCompress.h"
#include "HuffmanDecompress.h"
#include <time.h>
#include <ctime>
#include <string>
#include "MyUltility.h"
using namespace std;

int main()
{
	cout << "Nhap help() xem cu phap, exit() de thoat, credit() de xem thong tin nhom\n";
	while (true)
	{
		cout << "\n>> ";
		string express;
		getline(cin, express, '\n');

		erase_space(express);

		if (express.length() == 0)
			continue;
		if (express.compare("help()") == 0)
		{
			help();
			continue;
		}
		else if (express.compare("exit()") == 0)
			break;
		else if (express.compare("credit()") == 0)
		{
			credit();
			continue;
		}
		
		if (express.substr(0, 5).compare("ttzip") != 0)
			continue;

		if (express.substr(5, 2).compare("-c") == 0 || express.substr(5, 2).compare("-d") == 0)
		{
			size_t where_begin_c = express.find('\"');
			size_t where_end_c = express.find('\"', where_begin_c + 1);
			size_t len_c = where_end_c - where_begin_c - 1;

			size_t where_begin_d = express.find('\"', where_end_c + 1);
			size_t where_end_d = express.find('\"', where_begin_d + 1);
			size_t len_d = where_end_d - where_begin_d - 1;

			string linkIn = express.substr(where_begin_c + 1, len_c);
			string linkOut = express.substr(where_begin_d + 1, len_d);

			clock_t start = clock();

			
			if ( express.substr(5, 2).compare("-c") == 0)
			{
				HuffmanCompress zip(linkIn, linkOut);
				if (zip.compress())
					cout << "Ratio: " << 1 - Directory::getFileSize(linkOut) * 1.0 / Directory::getFolderSize(linkIn) << std::endl;
				else
					cout << "Nen khong thanh cong.\n";
			}
			else if (express.substr(5, 2).compare("-d") == 0)
			{
				HuffmanDecompress dezip(linkIn, linkOut);
				if (!dezip.decompress())
					cout << "Giai nen khong thanh cong.\n";
			}

			cout << "Time: " << double(clock() - start) / CLOCKS_PER_SEC << " (s).";
		}
		else
			cout << "Sai cu phap\n";
	}
}