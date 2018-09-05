#pragma once

#include "tag/CompoundTag.h"
#include "worker/DatabaseReader.h"
#include "worker/DatabaseWriter.h"
#include <fstream>
#include <sys/stat.h>

namespace mca
{
class Database
{
protected:
	std::vector<mca::CompoundTag> tagList;
	std::string filePath;
	std::string fileKey;
	int codekey;
protected:
	std::string encode(std::string const&str)
	{
		if(codekey==0)
			return str;
		std::string encodedString="";
		unsigned int pos=0;
		for(char letter:str)
			encodedString+=(((char)(((int)letter)^codekey)));
		return encodedString;
	}
	std::string decode(std::string const&str)
	{
		if(codekey==0)
			return str;
		std::string encodedString="";
		unsigned int pos=0;
		for(char letter:str)
			encodedString+=(((char)(((int)letter)^codekey)));
		return encodedString;
	}
	char encode(char letter)const
	{
		if(codekey==0)
			return letter;
		return letter^codekey;
	}
	char decode(char letter)const
	{
		if(codekey==0)
			return letter;
		return letter^codekey;
	}
public:
	Database()
	{
		filePath="";
		fileKey="";
		codekey=0;
		checkAndCreateFile();
	}
	Database(std::string const&path,std::string const&key)
	{
		filePath=path;
		fileKey=key;
		codekey=0;
		checkAndCreateFile();
	}
	Database(std::string const&path,std::string const&key,int encodeKey)
	{
		filePath=path;
		fileKey=key;
		codekey=encodeKey;
		checkAndCreateFile();
	}
	~Database()=default;
protected:
	void checkAndCreateFile()
	{
		if(!hasFile())
		{
			mkdir(filePath.substr(0,filePath.find_last_of("/")).c_str(),0);
			std::ofstream ofs(filePath.c_str());
			ofs.close();
			return;
		}
		else if(!isRightFileKey())
		{
			std::ofstream ofs(filePath.c_str());
			ofs.close();
			return;
		}
		readFile();
	}
	void readFile()
	{
		if(!isRightFileKey())
		{
			writeFile();
			return;
		}
		mca::DatabaseReader reader(filePath,fileKey,codekey);
		tagList=reader.read();
	}
	void writeFile()
	{
		mca::DatabaseWriter writer(filePath,fileKey,codekey);
		writer.write(tagList);
	}
	bool hasFile()
	{
		std::ifstream ifs(filePath.c_str());
		return ifs.is_open();
	}
	bool isRightFileKey()
	{
		std::ifstream ifs(filePath.c_str());
		std::string str;
		getline(ifs,str);
		return decode(str)==fileKey;
	}
public:
	void save()
	{
		writeFile();
	}
	void reread()
	{
		readFile();
	}
	mca::CompoundTag& getTag(std::string const&key)
	{
		for(mca::CompoundTag&tag:tagList)
			if(tag.getKey()==key)
				return tag;
		mca::CompoundTag newTag(key);
		addTag(newTag);
		return getTag(key);
	}
	void addTag(mca::CompoundTag t)
	{
		for(mca::CompoundTag&tag:tagList)
		{
			if(tag.getKey()==t.getKey())
			{
				tag=t;
				return;
			}
		}
		tagList.emplace_back(t);
	}
	void removeTag(std::string const&key)
	{
		std::vector<mca::CompoundTag>::iterator it;
		for(it=tagList.begin();it!=tagList.end();)
		{
			if((*it).getKey()==key)
				it=tagList.erase(it);    
			else
				++it;
		}
	}
	bool hasTag(std::string const&key)const
	{
		for(mca::CompoundTag tag:tagList)
			if(tag.getKey()==key)
				return true;
		return false;
	}
};
}
