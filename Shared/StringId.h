//**********************************************************************************************************************
#pragma once
#ifndef _STRINGID_INCLUDE_
#define _STRINGID_INCLUDE_
//**********************************************************************************************************************

#include <string>

namespace Shared
{

//**********************************************************************************************************************
class StringId
{
public:

	StringId();
	StringId(const std::string& string_in);
	StringId(const char* string_in);
	StringId(const StringId& other);
	~StringId();

	StringId& operator=(const std::string& string_in);
	StringId& operator=(const char* string_in);
	StringId& operator=(const StringId& other);

	bool operator==(const StringId& other);
	bool operator!=(const StringId& other);

	bool IsValid() const;
	unsigned long GetId() const;
	const char* GetContent() const;

protected:

	unsigned long m_uId;
	std::string m_strContent;

	void _SetContent(const char* string_in);

};

} //namespace Shared

//**********************************************************************************************************************
#endif //_STRINGID_INCLUDE_
