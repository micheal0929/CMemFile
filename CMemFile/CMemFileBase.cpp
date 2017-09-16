
/*
 * CMemFileBase.cpp
 *
 *  Created on: 2017年9月16日
 *      Author: micheal
 */

#include "CMemFileBase.h"
#include <iostream>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
extern int errno;
BSL::CMemFileBase::CMemFileBase (const std::string& filename, uint8_t mode):
m_sFileName(filename)
,m_nSize(-1)
,pBeginAddress(nullptr)
,pEndAddress(nullptr)
,nMode(READ_ONLY)
{
    Open(filename);
}

BSL::CMemFileBase::~CMemFileBase ()
{
    Close();
}

void
BSL::CMemFileBase::Open ()
{
    if (m_sFileName.empty())
    {
        std::cout << "Error ! lack of filename\n";
        return;
    }
    Open(m_sFileName);
}

void
BSL::CMemFileBase::Open (const std::string& sFileName)
{
    m_sFileName.assign(sFileName);

    if(Exist(m_sFileName))
    {
        size_t filesize = GetFileSize(m_sFileName.c_str());
        pBeginAddress = mmap(NULL,filesize,PROT_READ|PROT_WRITE,MAP_SHARED,m_nFd, 0);
        if(pBeginAddress == (void*)-1)
            std::cerr << "error:" << strerror(errno) << std::endl;
        if(pBeginAddress == nullptr)
        {
            std::cerr << "malloc error\n";
            return ;
        }
        pEndAddress = (char*)pBeginAddress + filesize;
    }
}

void*
BSL::CMemFileBase::GetBeginAddress () const
{
    return pBeginAddress;
}

void*
BSL::CMemFileBase::GetEndAddress () const
{
    return pEndAddress;
}

bool
BSL::CMemFileBase::Exist (const std::string& filename)
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

void
BSL::CMemFileBase::Close ()
{
    close(m_nFd);
    munmap(pBeginAddress, m_nSize);
    pBeginAddress = nullptr;
    pEndAddress = nullptr;
}

size_t
BSL::CMemFileBase::GetFileSize (const char* filename)
{
    if(m_nSize != -1)
        return m_nSize;
    FILE* pftr = fopen(filename, "r+");
    m_nFd = fileno(pftr);
    fseek(pftr, 0, SEEK_END);
    size_t size = ftell(pftr);
    m_nSize = size;
    fseek(pftr, SEEK_SET, 0);
    return size;
}


