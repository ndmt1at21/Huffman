#pragma once
#include <fstream>

#define SIZE_READ 1024*1024*16
#define SIZE_WRITE 1024*16

class f_ifstream
{
private:
	std::ifstream _inFile;
	char* _buffer;
	uint32_t _currentIdx;
	uint32_t _realSize;

public:
	f_ifstream(std::string linkFile);
	~f_ifstream();

	int get();
	std::string  getline(const char delim = '\n');
	void clear();
	void seek(std::streamoff off = 0);
	bool fail();

	//read direct from file
	void read(char* str, uint32_t count);
};


class f_ofstream
{
private:
	std::ofstream _outFile;
	char* _buffer;
	uint32_t _realSize;

public:
	f_ofstream(std::string linkFile);
	~f_ofstream();

	//check file exist 
	bool fail();

	//write char to buffer
	void write(char ch);
	
	//write string to bufffer
	void write(std::string str);

	//write int to FILE
	void write(uint32_t a);

	//write all in bufffer to file
	void write();
};