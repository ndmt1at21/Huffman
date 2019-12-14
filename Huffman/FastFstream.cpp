#include "FastFstream.h"
#include <iostream>

f_ifstream::f_ifstream(std::string linkFile)
{
	_inFile.open(linkFile, std::ios::binary);
	_currentIdx = 0;
	_buffer = new char[SIZE_READ];
	_realSize = 0;
}

f_ifstream::~f_ifstream()
{
	delete[] _buffer;
}

//hỗ trợ 0-255
int f_ifstream::get()
{
	if (_currentIdx == _realSize)
	{
		_inFile.read(_buffer, SIZE_READ);
		_realSize = uint32_t(_inFile.gcount());
		_currentIdx = 0;

		if (_realSize == 0)
			return EOF;
	}
	int tmp = int(_buffer[_currentIdx]);
	_currentIdx++;
	
	//chuyển char về int 0..255
	if (std::numeric_limits<char>::is_signed)
		tmp -= (tmp >> 7) << 8;

	return tmp;
}

std::string f_ifstream::getline(const char delim)
{
	std::string str;
	while (true)
	{
		int tmp = get(); //0-255 nên ép kiểu k sao
		if (tmp == EOF)
			break;

		char ch = char(tmp);
		if (ch == delim)
			break;

		
		str += ch;
	}

	return str;
}

void f_ifstream::clear()
{
	_inFile.clear();
}

void f_ifstream::seek(std::streamoff off)
{
	_inFile.seekg(off);
}

bool f_ifstream::fail()
{
	return _inFile.fail();
}

f_ofstream::f_ofstream(std::string linkFile)
{
	_outFile.open(linkFile, std::ios::binary);
	_buffer = new char[SIZE_READ];
	_realSize = 0;
}

f_ofstream::~f_ofstream()
{
	delete[] _buffer;
}

void f_ofstream::write(char ch)
{
	if (_realSize == SIZE_WRITE)
	{
		_outFile.write(_buffer, _realSize);
		_realSize = 0;
	}

	_buffer[_realSize] = ch;
	_realSize++;
}

void f_ofstream::write()
{
	_outFile.write(_buffer, _realSize);
	_realSize = 0;
}

void f_ofstream::write(std::string str)
{
	for (size_t i = 0; i < str.size(); i++)
		write(str[i]);
}

bool f_ofstream::fail()
{
	return _outFile.fail();
}