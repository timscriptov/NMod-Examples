#pragma once

namespace Math
{
	template <typename Type>
	Type max(Type t1,Type t2)
	{
		return t1>t2?t1:t2;
	}
	
	template <typename Type>
	static Type min(Type t1,Type t2)
	{
		return t1<t2?t1:t2;
	}
	template <typename Type,typename Type2>
	Type max(Type t1,Type2 t2)
	{
		return t1>t2?t1:t2;
	}
	
	template <typename Type,typename Type2>
	static Type min(Type t1,Type2 t2)
	{
		return t1<t2?t1:t2;
	}
};
