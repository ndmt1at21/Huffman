#include "Directory.h"
#include <sys/types.h>


std::vector<std::string> Directory::getLinkFiles(std::string linkDir)
{
	//tách folder cuối làm current link
	std::string currentLink;
	std::vector<std::string> linkFiles;
	
	list(linkDir.c_str(), currentLink, linkFiles);
	return linkFiles;
}

std::string Directory::getFileName(std::string linkFile)
{
	size_t last_slash = linkFile.find_last_of('/');
	std::string fileName(linkFile, last_slash, std::string::npos);
	return fileName;
}

void Directory::list(const char* dir, std::string currentLink, std::vector<std::string>& linkFiles)
{
	//kiểm tra nếu đường dẫn là file thì return luôn
	std::ifstream isFile(dir);
	if (!isFile.fail())
	{
		linkFiles.push_back("");
		return;
	}

	char originalDirectory[_MAX_PATH];

	//Lấy địa chỉ hiện tại trong windows 
	_getcwd(originalDirectory, _MAX_PATH);

	//Thay đổi địa chỉ làm việc
	int i = _chdir(dir);
	_finddata_t fileinfo;

	intptr_t handle = _findfirst("*", &fileinfo);

	//không thấy file hoặc folder
	if (handle == -1)
		throw std::logic_error("Khong the tim thay file hay folder");

	do
	{
		if (strcmp(fileinfo.name, ".") == 0 || strcmp(fileinfo.name, "..") == 0)
			continue;

		//nếu là folder thì đệ quy hàm
		if (fileinfo.attrib & _A_SUBDIR) // Use bitmask to see if this is a directory
			list(fileinfo.name, currentLink + '/' + fileinfo.name, linkFiles);
		//nếu là tệp thì xuất ra
		else
			linkFiles.push_back(currentLink + '/' + fileinfo.name);
	} while (_findnext(handle, &fileinfo) == 0);

	_findclose(handle); // Close the stream
	_chdir(originalDirectory);
}

void Directory::makeDir(std::string linkFile)
{
	size_t last_slash = linkFile.find_last_of('/');
	size_t currentPos = 0;

	while (true)
	{
		size_t next_slash = linkFile.find('/', currentPos);
		currentPos = next_slash + 1;
		std::string currentLink(linkFile, 0, currentPos);

		//_mkdir mỗi lần chỉ tạo được 1 thư mục nên phải đi từ từ
		//ex: D:/C++/Huffman/a.txt -> C++ trước -> Huffman -> dừng
		_mkdir(currentLink.c_str());

		if (next_slash > last_slash)
			break;
	}
}