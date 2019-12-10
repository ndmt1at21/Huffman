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
	std::ifstream inFile(_dirIn + shortLink, std::ios::binary);
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
	freqTab.increase(DEF_EOF);
	CodeTree codeTree = freqTab.buildHuffTree();
	
	//trở lại đầu file
	inFile.clear();
	inFile.seekg(0);

	//đọc lại file để encode
	//ghi linkFile vao outFile
	if (shortLink == "") //chỉ có 1 file đầu vào
		shortLink = Directory::getFileName(_dirIn);
	shortLink.push_back('\n');
	_outFile << shortLink;

	BitOutputStream bOut(_outFile);

	std::vector<uint32_t> codeLens = codeTree.getCodeLens();
	CanonicalCode canno(codeLens);
	codeTree = canno.toCodeTree();
	
	//chứa các hàm hỗ trợ 
	HuffEncoder encode(bOut, codeTree);

	//ghi bảng codelen vào file
	for (size_t i = 0; i < NUMBER_CHARACTER; i++)
		bOut.setByte(codeLens[i]);

	//encode nội dung
	while (true)
	{
		int symbol = inFile.get();
		if (symbol == EOF)
			break;

		if (symbol < 0 || symbol > 255)
			throw std::logic_error("Ky tu khong ho tro");

		encode.symEnc(static_cast<uint32_t>(symbol));
	}
	encode.symEnc(256);
	bOut.alignByte();
	inFile.close();

	return 1;
}

bool HuffmanCompress::compress()
{
	std::vector<std::string> shortLinkFiles = Directory::getLinkFiles(_dirIn);
	for (size_t i = 0; i < shortLinkFiles.size(); i++)
	{
		if (compressFile(shortLinkFiles[i]) == 0) //fail
			return 0;
	}

	return 1;
}