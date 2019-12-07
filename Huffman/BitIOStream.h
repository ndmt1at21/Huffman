/********************************************************
* Author: Nguyễn Đức Minh Trí							*
* Function: Thao tác với bit ghi đọc từ stream buffer   *
* Date: 21/11/2019										*
********************************************************/

#pragma once

#include <iostream>
#include "Endian.h"
#include <fstream>

#define ERROR_IO_BIT -1
#define DEF_EOF 256

//thao tác với bit, đọc bit từ file input 
class BitInputStream
{
private:
	//Con trỏ đến file
	std::ifstream& _inFile;

	//byte đọc được hiện tại từ file, các kí tự ASCII, nằm trong [0...255]
	//-1 nếu không đọc được
	int _currentByte;

	//số bit còn lại chưa đọc trong currentByte, nằm trong [0...7]
	unsigned char _numBitsRemaining;

	//chứa thông tin cách đọc ghi dữ liệu bit trên hệ thống hiện tại
	int _inforEndian;

public:
	//phương thức khởi tạo truyền vào stream
	BitInputStream(std::ifstream& inFile);

	//trả về bit hiện tại trong currentByte
	int getBit();

	int getChar();
};


class BitOutputStream
{
private:
	//Con trỏ đến file
	std::ofstream& _outFile;

	//byte đọc được hiện tại từ file, các kí tự ASCII, nằm trong [0...255]
	//-1 nếu không đọc được
	int _currentByte;

	//số bit đã điền currentByte, nằm trong [0...7]
	unsigned char _numBitsFilled;

	//chứa thông tin cách đọc ghi dữ liệu bit trên hệ thống hiện tại
	int _inforEndian;

public:
	//phương thức khởi tạo truyền vào stream
	BitOutputStream(std::ofstream& outFile);

	//set bit tiếp theo trong current byte
	//state: trạng thái 1 bit (0 hay 1) cần set vào currentByte
	//nếu đủ 8 bit ghi vào file
	void setBit(int state);

	//ghi kí tự bình thường vào file
	void charToStream(uint32_t symbol);

	//đến cuối file mà byte vẫn chưa điền bit đủ 8 -> thêm 0 vào sau
	//cho đủ 8 bit -> trọn 1 byte rồi ghi vào file
	void alignByte();
};
