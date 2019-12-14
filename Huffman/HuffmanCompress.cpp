#include "HuffmanCompress.h"

HuffmanCompress::HuffmanCompress(std::string dirIn, std::string linkFileCompress)
	:_fileCompress(linkFileCompress)
{
	_dirIn = dirIn;
}

HuffmanCompress::~HuffmanCompress() {}

int HuffmanCompress::compressFile(std::string shortLink)
{
	f_ifstream inFile(_dirIn + shortLink);
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
	freqTab.increase(DEF_EOF); //eof định nghĩa
	
	//trở lại đầu file
	inFile.clear();
	inFile.seek(0);

	//đọc lại file để encode
	//ghi linkFile vào outFile
	if (shortLink == "") //chỉ có 1 file đầu vào
		shortLink = Directory::getFileName(_dirIn);
	else
		shortLink = Directory::getFileName(_dirIn) + shortLink;
	shortLink.push_back('\n');
	_fileCompress.write(shortLink);

	BitOutputStream bOut(_fileCompress);
	CodeTree codeTree = freqTab.buildHuffTree();
	
	std::vector<uint32_t> codeLens = codeTree.getCodeLens();
	CanonicalCode canno(codeLens);
	codeTree = canno.toCodeTree();
	HuffEncoder encode(bOut, codeTree); //chứa các hàm hỗ trợ

	//ghi bảng codelen vào file
	for (size_t i = 0; i < NUMBER_CHARACTER; i++)
		bOut.setByte(codeLens[i]);

	//encode nội dung
	int i = 0;
	while (true)
	{
		//tmp 0..255
		int sym = inFile.get();
		if (sym == EOF)
			break;
		i++;
		encode.symEnc(static_cast<uint32_t>(sym));
	}
	encode.symEnc(256);
	bOut.alignByte();

	return 1;
}

bool HuffmanCompress::compress()
{
	std::vector<std::string> shortLinkFiles = Directory::getLinkFiles(_dirIn);

	_fileCompress.write(uint32_t(MAGIC_NUMBER));

	for (size_t i = 0; i < shortLinkFiles.size(); i++)
	{
		if (compressFile(shortLinkFiles[i]) == 0) //fail
			return 0;
	}

	//encode xong tính crc, seek lại đầu file và ghi 

	return 1;
}