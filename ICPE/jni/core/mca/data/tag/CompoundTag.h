#pragma once

#include <string>

#include "ListTag.h"

namespace mca
{
class CompoundTag
{
public:
	friend class DatabaseWriter;
	friend class DatabaseReader;
protected:
	mca::ListTag<float> floatList;
	mca::ListTag<int> intList;
	mca::ListTag<std::string> strList;
	mca::ListTag<bool> boolList;
	mca::ListTag<double> doubleList;
	mca::ListTag<char> charList;
	mca::ListTag<long> longList;
	mca::ListTag<unsigned char> ucharList;
	mca::ListTag<short> shortList;
	mca::ListTag<unsigned int> uintList;
	mca::ListTag<unsigned short> ushortList;
	mca::ListTag<unsigned long> ulongList;
	std::string key;
public:
	CompoundTag()=default;
	CompoundTag(std::string const&le)
	{
		key=le;
	}
	~CompoundTag()
	{
		floatList.clear();
		intList.clear();
		strList.clear();
		boolList.clear();
		doubleList.clear();
		charList.clear();
		longList.clear();
		ucharList.clear();
		shortList.clear();
		uintList.clear();
		ushortList.clear();
		ulongList.clear();
	}
public:
	void setKey(std::string const& le)
	{
		key=le;
	}
	std::string const getKey()const
	{
		return key;
	}
public:
	void putInt(std::string const&key,int t)
	{
		intList.setElement({key,t});
	}
	void putFloat(std::string const&key,float t)
	{
		floatList.setElement({key,t});
	}
	void putUint(std::string const&key,unsigned int t)
	{
		uintList.setElement({key,t});
	}
	void putChar(std::string const&key,char t)
	{
		charList.setElement({key,t});
	}
	void putUchar(std::string const&key,unsigned char t)
	{
		ucharList.setElement({key,t});
	}
	void putShort(std::string const&key,short t)
	{
		shortList.setElement({key,t});
	}
	void putUshort(std::string const&key,unsigned short t)
	{
		ushortList.setElement({key,t});
	}
	void putLong(std::string const&key,long t)
	{
		longList.setElement({key,t});
	}
	void putUlong(std::string const&key,unsigned long t)
	{
		ulongList.setElement({key,t});
	}
	void putBool(std::string const&key,bool t)
	{
		boolList.setElement({key,t});
	}
	void putString(std::string const&key,std::string t)
	{
		strList.setElement({key,castToInFileString(t)});
	}
	void putDouble(std::string const&key,double t)
	{
		doubleList.setElement({key,t});
	}
public:
	float getFloat(std::string const&key,float defaultRet=0.0F)const
	{
		if(floatList.hasElement(key))
			return floatList.getElement(key).get();
		return defaultRet;
	}
	double getDouble(std::string const&key,double defaultRet=0.0D)const
	{
		if(doubleList.hasElement(key))
			return doubleList.getElement(key).get();
		return defaultRet;
	}
	int getInt(std::string const&key,int defaultRet=0)const
	{
		if(intList.hasElement(key))
			return intList.getElement(key).get();
		return defaultRet;
	}
	unsigned int getUint(std::string const&key,unsigned int defaultRet=0)const
	{
		if(uintList.hasElement(key))
			return uintList.getElement(key).get();
		return defaultRet;
	}
	short getShort(std::string const&key,short defaultRet=0)const
	{
		if(shortList.hasElement(key))
			return shortList.getElement(key).get();
		return defaultRet;
	}
	unsigned short getUshort(std::string const&key,unsigned short defaultRet=0)const
	{
		if(ushortList.hasElement(key))
			return ushortList.getElement(key).get();
		return defaultRet;
	}
	long getLong(std::string const&key,long defaultRet=0)const
	{
		if(longList.hasElement(key))
			return longList.getElement(key).get();
		return defaultRet;
	}
	unsigned long getUlong(std::string const&key,unsigned long defaultRet=0)const
	{
		if(ulongList.hasElement(key))
			return ulongList.getElement(key).get();
		return defaultRet;
	}
	char getChar(std::string const&key,char defaultRet=0)const
	{
		if(charList.hasElement(key))
			return charList.getElement(key).get();
		return defaultRet;
	}
	unsigned char getUchar(std::string const&key,unsigned char defaultRet=0)const
	{
		if(ucharList.hasElement(key))
			return ucharList.getElement(key).get();
		return defaultRet;
	}
	bool getBool(std::string const&key,bool defaultRet=false)const
	{
		if(boolList.hasElement(key))
			return boolList.getElement(key).get();
		return defaultRet;
	}
	std::string getString(std::string const&key,std::string const& defaultRet="")const
	{
		if(strList.hasElement(key))
			return castToInCodeString(strList.getElement(key).get());
		return defaultRet;
	}
public:
	bool isEmpty()const
	{
		return strList.empty()&&intList.empty()&&uintList.empty()&&charList.empty()&&ucharList.empty()&&floatList.empty()&&doubleList.empty()&&boolList.empty()&&shortList.empty()&&ushortList.empty()&&longList.empty()&&ulongList.empty();
	}
private:
	static std::string castToInFileString(std::string const&str_)
	{
		std::string str=str_;
		for(size_t i=0;i<str.length();++i)
		{
			if(str[i]=='\n')
				str.replace(i,1,"\\n");
		}
		return str;
	}
	static std::string castToInCodeString(std::string const&str_)
	{
		std::string str=str_;
		for(size_t i=0;i<str.length();++i)
		{
			if(i+1<str.length()&&str[i]=='\\'&&str[i+1]=='n')
				str.replace(i,2,"\n");
		}
		return str;
	}
};
}
