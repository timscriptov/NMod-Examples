#pragma once

#include <vector>

#include "Tag.h"
#include <fstream>
namespace mca
{
template <typename Type>
class ListTag
{
protected:
	std::vector<mca::Tag<Type>> tagList;
public:
	ListTag()=default;
	~ListTag()
	{
		tagList.clear();
	}
public:
	void setElement(mca::Tag<Type> t)
	{
		for(mca::Tag<Type>& tt : tagList)
		{
			if(tt.getKey()==t.getKey())
			{
				tt.set(t.get());
				return;
			}
		}
		tagList.push_back(t);
	}
	mca::Tag<Type> getElement(std::string const&key)const
	{
		for(mca::Tag<Type> t : tagList)
			if(t.getKey()==key)
				return t;
		static mca::Tag<Type> fackRet;
		fackRet=mca::Tag<Type>(key);
		return fackRet;
	}
	bool hasElement(std::string const&key)const
	{
		for(mca::Tag<Type> t : tagList)
			if(t.getKey()==key)
				return true;
		return false;
	}
	std::vector<mca::Tag<Type>> readAll()const
	{
		return tagList;
	}
	void clear()
	{
		tagList.clear();
	}
	bool empty()const
	{
		return tagList.empty();
	}
};
}
