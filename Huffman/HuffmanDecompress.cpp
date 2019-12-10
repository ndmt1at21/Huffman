#include "HuffmanDecompress.h"

HuffmanDecompress::HuffmanDecompress() {}

HuffmanDecompress::HuffmanDecompress(std::string linkInFile, std::string dirOut)
{
	_inFile.open(linkInFile, std::ios::binary);
	if (_inFile.fail())
		throw std::logic_error("file nen khong ton tai");
	
	_dirOut = dirOut;
}

int HuffmanDecompress::decompressFile()
{
	//đọc file đã được encode
	BitInputStream bIn(_inFile);
	HuffDecoder decode(bIn);

	//đọc header (link file doi voi folder, hoặc tên file)
	std::string shortLink;
	std::getline(_inFile, shortLink, '\n');
	std::string linkFileOut = _dirOut + shortLink;
	Directory::makeDir(linkFileOut); //tạo đường dẫn nếu chưa có

	//xây dựng lại cây huffman
	std::ofstream outFile(linkFileOut, std::ios::binary);
	if (outFile.fail())
		return 0;

	//đọc bảng code len
	std::vector<uint32_t> codeLens;
	for (size_t i = 0; i < NUMBER_CHARACTER; i++)
		codeLens.push_back(bIn.getByte());

	CanonicalCode canno(codeLens);
	CodeTree codeTree = canno.toCodeTree();
	
	//đọc và decode từng ký tự
	while (true)
	{
		int symbol = decode.symDec(codeTree);

		if (symbol == EOF)
			return EOF;

		if (symbol == DEF_EOF)
			break;

		//ép từ int 4 byte về 1 byte char
		//vì từ 0-255 nên ko mất dữ liệu
		//char từ -127 tới 127 nên cần kiểm tra số trong int chuyển sang char có dấu ko
		if (std::numeric_limits<char>::is_signed)
			symbol -= (symbol >> 7) << 8;
		outFile.put(char(symbol));
	}

	return 1;
}

bool HuffmanDecompress::decompress()
{
	while (true)
	{
		int tmp = decompressFile();
		if (tmp == EOF) //het file nen
			break;
		if (tmp == 0) //thất bại
			return 0;
	}

	return 1;
}