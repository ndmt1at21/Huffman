#include "HuffmanCompress.h"

HuffmanCompress::HuffmanCompress(std::string dirIn, std::string linkOutFile)
{
	_dirIn = dirIn;
	_outFile.open(linkOutFile, std::ios::binary);

	if (_outFile.fail())
		throw std::logic_error("duong dan khong ton tai");
}

HuffmanCompress::~HuffmanCompress() 
{
	_outFile.close();
}

int HuffmanCompress::compressFile(std::string shortLink)
{
	std::ifstream inFile(_dirIn + shortLink);
	if (inFile.fail())
		return 0;

	//đọc 1 lần file để tạo bảng tần suất xuất hiện
	FrequencyTable freqTab;
	while (true)
	{
		int sym = inFile.get();
		if (sym == EOF)
			break;

		freqTab.increase(sym);
	}

	//trở lại đầu file
	inFile.seekg(0);

	BitOutputStream bOut(_outFile);
	CodeTree codeTree = freqTab.buildHuffTree();
	HuffEncoder encode(bOut, codeTree);
	
	//đọc lại file để encode
	//ghi linkFile vao outFile
	shortLink.push_back('\n');
	_outFile << shortLink;

	//encode cây huffman
	encode.treeEnc();

	//encode nội dung
	while (true)
	{
		int symbol = inFile.get();
		if (symbol == EOF)
			break;

		if (symbol < 0 || symbol > 255)
			throw std::logic_error("Ky tu khong ho tro");

		//ký tự luôn không âm nên vẫn cast đc
		encode.symEnc(static_cast<uint32_t>(symbol));
	}
	encode.symEnc(256);
	bOut.alignByte();

	return 1;
}

//int HuffmanCompress::compress()
//{
//	
//}