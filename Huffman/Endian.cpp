#include "Endian.h"

//kiểm tra little endian
bool Endian::isLittle()
{
	int x = 1;

	//trỏ đến địa chỉ của x
	int* ptr = &x;

	//trỏ đến byte đầu tiên của x
	char* ptrCh = (char*)ptr;

	//nếu little endian thì bit được viết từ 
	//địa chỉ cao xuống thấp, do đó dữ liệu byte đầu sẽ = 1
	if (*ptrCh == 1)
		return true;

	return false;
}

//kiểm tra big endian
bool Endian::isBig()
{
	int x = 1;
	int* ptr = &x;

	//trỏ đến byte cuối của x
	char* ptrCh = (char*)ptr + sizeof(int);

	if (*ptrCh == 0)
		return false;

	return true;
}

int Endian::endianOfSys()
{
	if (isLittle())
		return LITTE_ENDIAN;
	else if (isBig())
		return BIG_ENDIAN;

	return UNKNOWN_ENDIAN;
}