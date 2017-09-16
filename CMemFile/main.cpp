/*
 * main.cpp
 *
 *  Created on: 2017年9月10日
 *      Author: micheal
 */



#include <vector>
#include <iostream>
#include <fstream>

#include "CMemFile.h"
struct My{
	int a;
	int b;
	My():
	    a(10),b(20)
	{

	}
};
typedef CMemFile<My> FileType;


int main()
{
    std::ofstream write("mylog.log");
    My test;
    std::cerr << test.a << "," << test.b << std::endl;
    for(int i=0;i<10;i++)
    {
        write.write((char*)&test, sizeof(test));

    }
    write.flush();
    write.close();
	FileType testlog("mylog.log");

	for(auto iter = testlog.GetBeginAddress(); iter != testlog.GetEndAddress();++iter)
	{
		std::cout << iter->a << "," << iter->b << std::endl;
	}
}
