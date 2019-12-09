#include "HuffmanDecompress.h"

HuffmanDecompress::HuffmanDecompress() {}

HuffmanDecompress::HuffmanDecompress(std::string linkInFile, std::string dirOut)
{
	_inFile.open(linkInFile, std::ios::binary);
	if (_inFile.fail())
		throw std::logic_error("file khong ton tai");
	
	_dirOut = dirOut;
}

int HuffmanDecompress::decompressFile(std::string outFolder)
{
	//đọc file đã được encode
	BitInputStream bIn(_inFile);
	
	//đọc header (link file doi voi folder, hoặc tên file)
	std::string name;
	std::getline(_inFile, name, '\n');
	std::string linkFileOut = outFolder + name;

	//xây dựng lại cây huffman
	std::ofstream outFile(linkFileOut, std::ios::binary);
	HuffDecoder decode(bIn);
	CodeTree codeTree = decode.toCodeTree();
	
	//đọc và decode từng ký tự
	while (true)
	{
		int symbol = decode.symDec(codeTree);

		if (symbol == DEF_EOF)
			break;

		//ép từ int 4 byte về 1 byte char
		//vì từ 0-255 nên ko mất dữ liệu
		//char từ -127 tới 127 nên cần kiểm tra số trong int chuyển sang char có dấu ko
		if (std::numeric_limits<char>::is_signed)
			symbol -= (symbol >> 7) << 8;
		outFile.put(char(symbol));
	}
}

int HuffmanDecompress::decompressFiles()
{

}