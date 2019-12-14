#include "HuffmanDecompress.h"

HuffmanDecompress::HuffmanDecompress(std::string linkFileCompressed, std::string dirOut)
	:_fileCompressed(linkFileCompressed)
{
	_dirOut = dirOut;
}

HuffmanDecompress::~HuffmanDecompress() {}

int HuffmanDecompress::decompressFile()
{
	//đọc file đã được encode
	BitInputStream bIn(_fileCompressed);
	HuffDecoder decode(bIn);

	//đọc header (link file doi voi folder, hoặc tên file)
	std::string shortLink = _fileCompressed.getline('\n');
	std::string linkFileOut = _dirOut + shortLink;
	Directory::makeDir(linkFileOut); //tạo đường dẫn nếu chưa có

	f_ofstream fileDecompress(linkFileOut);
	if (fileDecompress.fail())
		return 0;

	//xây dựng lại cây huffman
	//đọc bảng code len
	std::vector<uint32_t> codeLens(NUMBER_CHARACTER);
	for (size_t i = 0; i < NUMBER_CHARACTER; i++)
		codeLens[i] = bIn.getByte();

	CanonicalCode canno(codeLens);
	CodeTree codeTree = canno.toCodeTree();
	
	//đọc từng bit và decode từng ký tự
	while (true)
	{
		int symbol = decode.symDec(codeTree);
		if (symbol == EOF)
		{
			fileDecompress.write();
			return EOF;
		}

		if (symbol == DEF_EOF)
		{
			fileDecompress.write();
			return DEF_EOF;
		}

		//symbol 0..255 -> ép kiểu k lỗi logic
		fileDecompress.write(char(symbol));
	}

	return 1;
}

bool HuffmanDecompress::decompress()
{
	while (true)
	{
		int tmp = decompressFile();
		if (tmp == EOF || tmp == 0) //het file nen
			break;
	}

	return 1;
}