#include "BitIoStream.h"

BitInputStream::BitInputStream(f_ifstream& inFile) : _inFile(inFile)
{
	_inforEndian = Endian::endianOfSys();
	_currentByte = 0;
	_numBitsRemaining = 0;
}

BitInputStream::~BitInputStream() {}

//trả về bit hiện tại trong currentByte
int BitInputStream::getBit()
{
	//số bit trong bộ đệm không còn thì đọc tiếp trong file
	if (_numBitsRemaining == 0)
	{
		_currentByte = _inFile.get();
		if (_currentByte == EOF)
			return EOF;
		_numBitsRemaining = 8;
	}

	_numBitsRemaining--;
	return (_currentByte >> _numBitsRemaining) & 1;
}

int BitInputStream::getByte()
{
	int sym = 0;
	for (int i = 0; i < 8; i++)
	{
		int state = getBit();
		if (state == EOF) //EOF
			return EOF;

		sym = (sym << 1) | state;
	}

	return sym;
}

BitOutputStream::BitOutputStream(f_ofstream& outFile) :_outFile(outFile)
{
	_inforEndian = Endian::endianOfSys();
	_currentByte = 0;
	_numBitsFilled = 0;
}

BitOutputStream::~BitOutputStream() {}

void BitOutputStream::setBit(int state)
{
	if (state != 1 && state != 0)
		throw std::logic_error("bit chi ton tai 0 va 1");

	//ex: currentByte = 2 (010) -> 001 << 1 | 1 -> (100 | 001) = 101
	_currentByte = (_currentByte << 1) | state;
	_numBitsFilled++;

	if (_numBitsFilled == 8)
	{
		//vì ascii luôn nằm trong [0..255] nên ép kiểu đc, ko lỗi logic
		_outFile.write(char(_currentByte));

		//reset
		_numBitsFilled = 0;
		_currentByte = 0;
	}
}

void BitOutputStream::setByte(uint32_t symbol)
{
	for (int i = 7; i >= 0; i--)
		setBit((symbol >> i) & 1);
}

void BitOutputStream::alignByte()
{
	while (_numBitsFilled != 0)
		setBit(0);

	_outFile.write();
}