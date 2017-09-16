/*
 * memfile.h
 *
 *  Created on: 2017年9月10日
 *      Author: micheal
 */

#ifndef CMEMFILE_H_
#define CMEMFILE_H_


#include "CMemFileBase.h"


template<typename T_>
class CMemFile:
        public BSL::CMemFileBase
{
	typedef T_ value_type;
	typedef value_type* pointer_type;

public:
	CMemFile(const std::string& filename, uint8_t mode = READ_ONLY);
	~CMemFile();

	struct iterator
	{
	    typedef CMemFile<T_>::value_type _value_type;
	    typedef CMemFile<T_>::pointer_type _point_type;
	    iterator(_value_type* begin):
	        m_begin(begin)
	    {

	    }
	    _value_type& operator*(void) const
	    {
	        return *m_begin;
	    }
	    _value_type* operator->(void) const
	    {
	        return m_begin;
	    }
	    iterator& operator++(void)
		{
	        ++m_begin;
			return *this;
		}

		bool operator!=(const iterator& tmp) const
		{
		    return m_begin != tmp.m_begin;
		}
		 _point_type m_begin;
	};
	typedef const iterator const_iterator;
public:
	iterator begin()
	{
	    return iterator(GetBeginAddress());
	}
	iterator end()
	{
	    return iterator(GetEndAddress());
	}
	const_iterator begin() const
	{
	    return const_iterator(GetBeginAddress());
	}
	const_iterator end() const
	{
	    return const_iterator(GetEndAddress());
	}
public:
	 pointer_type GetBeginAddress() const
	 {
	     return reinterpret_cast<pointer_type>(CMemFileBase::GetBeginAddress());
	 }
	 pointer_type GetEndAddress() const
	 {
	     return reinterpret_cast<pointer_type>(CMemFileBase::GetEndAddress());
	 }
    };

template<typename T_>
    inline
    CMemFile<T_>::CMemFile (const std::string& filename, uint8_t mode):
        CMemFileBase(filename, mode)
    {
    }

template<typename T_>
    inline
    CMemFile<T_>::~CMemFile ()
    {
    }

#endif /* CMEMFILE_H_ */
