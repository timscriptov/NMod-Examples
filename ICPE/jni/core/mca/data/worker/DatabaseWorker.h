#pragma once

#include "./mca/data/tag/Tag.h"
#include "./mca/data/tag/ListTag.h"
#include "./mca/data/tag/CompoundTag.h"

#include <string>
#include <vector>
#include <sstream>
#include <fstream>

namespace mca
{
class DatabaseWorker
{
	friend class Batabase;
public:
	static char const cutLine='\n';
	//You can change the cut line here.
protected:
	std::string filePath;
	std::string fileKey;
	int decodeKey;
protected:
	DatabaseWorker(std::string const&path,std::string const&key,int codeKey)
	{
		filePath=path;
		fileKey=key;
		decodeKey=codeKey;
	}
	~DatabaseWorker()=default;
protected:
	std::string encode(std::string const&str)
	{
		if(decodeKey==0)
			return str;
		std::string encodedString="";
		unsigned int pos=0;
		for(char letter:str)
			encodedString+=(((char)(((int)letter)^decodeKey)));
		return encodedString;
	}
	char encode(char letter)const
	{
		if(decodeKey==0)
			return letter;
		return letter^decodeKey;
	}
	std::string decode(std::string const&str)
	{
		if(decodeKey==0)
			return str;
		std::string encodedString="";
		unsigned int pos=0;
		for(char letter:str)
			encodedString+=(((char)(((int)letter)^decodeKey)));
		return encodedString;
	}
	char decode(char letter)const
	{
		if(decodeKey==0)
			return letter;
		return letter^decodeKey;
	}
};
}
