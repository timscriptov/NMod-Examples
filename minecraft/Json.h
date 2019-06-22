#pragma once
#include <string>
#include <memory>
#include <map>

namespace Json
{
class ValueType {
	//public:
	//char filler_ValueType[UNKNOW_SIZE];
};
class StaticString {
	//public:
	//char filler_StaticString[UNKNOW_SIZE];
};
class CommentPlacement {
	//public:
	//char filler_CommentPlacement[UNKNOW_SIZE];
};
class Value {
	//public:
	//char filler_Value[UNKNOW_SIZE];
public:
	Value(Json::ValueType);
	Value(Json::Value const&);
	Value(std::string const&);
	Value(char const*);
	Value(bool);
	Value(int);
	Value(double);
	Value(unsigned long long);
	Value(unsigned int);
	Value(long long);
	Value(char const*, char const*);
	Value(Json::StaticString const&);
	~Value();
	void operator=(Json::Value const&);
	void operator[](std::string const&);
	void operator[](char const*);
	void asString(std::string const&) const;
	void asBool(bool) const;
	void isBool() const;
	void isNull() const;
	void isObject() const;
	void operator[](char const*) const;
	void operator[](int);
	void get(char const*, Json::Value const&) const;
	void size() const;
	void isArray() const;
	void isString() const;
	void append(Json::Value const&);
	void end();
	void begin();
	void operator<(Json::Value const&) const;
	void asInt(int) const;
	void isInt() const;
	void isUInt() const;
	void asFloat(float) const;
	void isNumeric() const;
	void clear();
	void getMemberNames() const;
	void end() const;
	void begin() const;
	void isMember(char const*) const;
	void operator[](int) const;
	void isIntegral() const;
	void get(unsigned int, Json::Value const&) const;
	void empty() const;
	void asDouble(double) const;
	void operator[](std::string const&) const;
	void operator!=(Json::Value const&) const;
	void operator==(Json::Value const&) const;
	void removeMember(char const*);
	void removeMember(std::string const&);
	void swap(Json::Value&);
	void resize(unsigned int);
	void operator[](unsigned int);
	void type() const;
	void asCString() const;
	void operator[](unsigned int) const;
	void isMember(std::string const&) const;
	void toStyledString() const;
	void isDouble() const;
	void asUInt64(unsigned long long) const;
	void asUInt(unsigned int) const;
	void asInt64(long long) const;
	void get(std::string const&, Json::Value const&) const;
	void asLargestInt() const;
	void asLargestUInt() const;
	void compare(Json::Value const&) const;
	void isConvertibleTo(Json::ValueType) const;
	void setComment(std::string const&, Json::CommentPlacement);
	void setComment(char const*, Json::CommentPlacement);
	void resolveReference(char const*, bool);
	void operator[](Json::StaticString const&);
	void getComment(Json::CommentPlacement) const;
	void hasComment(Json::CommentPlacement) const;
	void isValidIndex(unsigned int) const;
	void operator>=(Json::Value const&) const;
	void operator>(Json::Value const&) const;
	void operator<=(Json::Value const&) const;
	void operator!() const;
public:
	static Json::Value * null;
	static Json::Value * minLargestInt;
	static Json::Value * maxLargestUInt;
	static Json::Value * maxInt;
	static Json::Value * maxLargestInt;
	static Json::Value * minInt;
	static Json::Value * maxUInt;
	static Json::Value * maxInt64;
	static Json::Value * minInt64;
	static Json::Value * maxUInt64;
};
}
