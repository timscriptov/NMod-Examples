#pragma once

#include <string>

namespace mca
{
template <typename Type>
class Tag
{
protected:
	Type typeSelf;
	std::string key;
public:
	Tag()=default;
	~Tag()=default;
	Tag(std::string const&ke,Type t)
	{
		key=ke;
		typeSelf=t;
	}
	Tag(std::string const&ke)
	{
		key=ke;
	}
public:
	void reset(std::string const&ke,Type t)
	{
		key=ke;
		typeSelf=t;
	}
	void resetKey(std::string const& t)
	{
		key=t;
	}
	Type get()const
	{
		return typeSelf;
	}
	void set(Type t)
	{
		typeSelf=t;
	}
	std::string getKey()const
	{
		return key;
	}
};
}
