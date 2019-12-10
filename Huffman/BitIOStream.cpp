#include "BitIoStream.h"

BitInputStream::BitInputStream(std::ifstream& inFile) : _inFile(inFile)
{
	_inforEndian = Endian::endianOfSys();
	_currentByte = 0;
	_numBitsRemaining = 0;
}

//trả về bit hiện tại trong currentByte
int BitInputStream::getBit()
{
	//một số thường hợp gây lỗi
	if (_currentByte == -1)
		return -1;

	if (_numBitsRemaining < 0)
		return -1;

	//số bit trong bộ đệm không còn thì đọc tiếp trong file
	if (_numBitsRemaining == 0)
	{
		_currentByte = _inFile.get();

		if (_currentByte == EOF)
			return EOF;

		if (_currentByte == DEF_EOF)
			return DEF_EOF;

		//kí tự nằm trong bảng ASCII
		if (_currentByte < 0 || _currentByte > 255)
			return -1;

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
		if (state == -1) //EOF
			return DEF_EOF;
		else
			sym = (sym << 1) | state;
	}

	return sym;
}

BitOutputStream::BitOutputStream(std::ofstream& outFile) :_outFile(outFile)
{
	_inforEndian = Endian::endianOfSys();
	_currentByte = 0;
	_numBitsFilled = 0;
}

void BitOutputStream::setBit(int state)
{
	if (state != 1 && state != 0)
		return;

	//ex: currentByte = 2 (010) -> 001 << 1 | 1 -> (100 | 001) = 101
	_currentByte = (_currentByte << 1) | state;
	_numBitsFilled++;

	if (_numBitsFilled == 8)
	{
		//ghi vào file
		//lưu ý: put chỉ nhận đối số là char [-127..127]
		//chuyển từ uint32 về char
		//VD: uint32: 255 -> char: -1
		if (std::numeric_limits<char>::is_signed)
			_currentByte -= (_currentByte >> 7) << 8;

		_outFile.put((char)_currentByte);

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
}