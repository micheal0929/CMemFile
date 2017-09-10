/*
 * memfile.h
 *
 *  Created on: 2017年9月10日
 *      Author: micheal
 */

#ifndef MEMFILE_H_
#define MEMFILE_H_

#include <string>
#include <stdint.h>
#include <unistd.h>
#include <iostream>
#include <sys/stat.h>


enum Operate{
	READ_ONLY,
	READ_WRITE
};


template<typename T_>
class CMemFile
{
	typedef T_ value_type;
	typedef T_* pointer_type;

public:
	CMemFile(const std::string& filename, uint8_t mode = READ_ONLY);
	~CMemFile();

	void* GetBeginAddress();
	void* GetEndAddress();


	struct iterator{
		char* ptr;
	};

private:
	void Open(void);
	bool Exist(const std::string& filename);
private:
	std::string sFileName;
	uint8_t nMode;
	T_* pBeginAddress;
	T_* pEndAddress;
};

template<typename T_>
inline CMemFile<T_>::CMemFile(const std::string& filename, uint8_t mode):
	sFileName(filename)
	,nMode(mode)
{
	Open();
}

template<typename T_>
inline CMemFile<T_>::~CMemFile()
{
}

template<typename T_>
inline void* CMemFile<T_>::GetBeginAddress()
{
}

template<typename T_>
inline void* CMemFile<T_>::GetEndAddress()
{
}

template<typename T_>
inline void CMemFile<T_>::Open(void)
{
	if(Exist(sFileName))//文件存在且不为目录
	{

	}

}

template<typename T_>
inline bool CMemFile<T_>::Exist(const std::string& filename)
{
	if(access(filename.c_str(), F_OK) == -1)
	{
		std::cerr << "file not exist!\n";
		return false;
	}
	struct stat buf;
	stat(filename.c_str(), &buf);
	if(S_ISDIR(buf.st_mode))
	{
		std::cerr << "dir exist!\n";
		return false;
	}
	return true;
}

#endif /* MEMFILE_H_ */
