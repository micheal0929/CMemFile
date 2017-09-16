/*
 * CMemFileBase.h
 *
 *  Created on: 2017年9月16日
 *      Author: micheal
 */

#ifndef CMEMFILEBASE_H_
#define CMEMFILEBASE_H_

#include <string>

enum Operate{
    READ_ONLY,
    READ_WRITE
};

namespace BSL{
    class CMemFileBase{
    public:
        CMemFileBase(const std::string& filename, uint8_t mode = READ_ONLY);
        ~CMemFileBase();

    public:
        void Open();
        void Open(const std::string& sFileName);
        void Close();

    protected:
        void* GetBeginAddress() const;
        void* GetEndAddress() const;
        bool Exist(const std::string& filename);
        size_t GetFileSize(const char* filename);

    private:
        std::string m_sFileName;
        uint8_t nMode;
        void* pBeginAddress;
        void* pEndAddress;

        long m_nSize;

        int m_nFd;
    };

}//namespace BSL



#endif /* CMEMFILEBASE_H_ */
