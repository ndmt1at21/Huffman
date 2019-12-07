/*************************************************************
* Author: Nguyễn Đức Minh Trí							     *
* Function: Kiểm tra hệ thống sử dụng LITTLE hay BIG ENDIAN  *
* Date: 21/11/2019										     *
*************************************************************/

#pragma once
#define LITTE_ENDIAN 1
#define BIG_ENDIAN 2
#define UNKNOWN_ENDIAN 3

class Endian
{
private:
	//kiểm tra little endian
	static bool isLittle();

	//kiểm tra big endian
	static bool isBig();

public:
	//trả về endian sử dụng của hệ thống
	static int endianOfSys();
};
