//**********************************************************************************************************************
#include <stdlib.h>
#include <cassert>

extern unsigned long crc32(const void *buf, size_t size);

#include "StringId.h"
//**********************************************************************************************************************
namespace Shared
{
	//**********************************************************************************************************************
	StringId::StringId():
		m_uId(0)
	{

	}
	//**********************************************************************************************************************
	StringId::~StringId()
	{
		m_strContent.clear();
	}

	//**********************************************************************************************************************
	StringId::StringId(const std::string& string_in):
		m_uId(0)
	{
		const char* c_string = string_in.c_str();

		_SetContent(c_string);
	}

	//**********************************************************************************************************************
	StringId::StringId(const char* string_in):
		m_uId(0)
	{
		_SetContent(string_in);
	}

	//**********************************************************************************************************************
	StringId::StringId(const StringId& other):
		m_uId(0)
	{
		const char* c_string = other.m_strContent.c_str();

		_SetContent(c_string);
	}

	//**********************************************************************************************************************
	StringId& StringId::operator=(const std::string& string_in)
	{
		const char* c_string = string_in.c_str();

		_SetContent(c_string);

		return *this;
	}

	//**********************************************************************************************************************
	StringId& StringId::operator=(const char* string_in)
	{
		_SetContent(string_in);

		return *this;
	}

	//**********************************************************************************************************************
	StringId& StringId::operator=(const StringId& other)
	{
		const char* c_string = other.m_strContent.c_str();

		_SetContent(c_string);

		return *this;
	}

	//**********************************************************************************************************************
	void StringId::_SetContent(const char* string_in)
	{
		if (string_in == NULL)
		{
			m_strContent.clear();
			m_uId = 0;
		}
		else
		{
			size_t len = strlen(string_in);
			m_uId = crc32(string_in, len);

			m_strContent = string_in;
		}
	}

	//**********************************************************************************************************************
	bool StringId::operator==(const StringId& other)
	{
		return (m_uId == other.m_uId);
	}

	//**********************************************************************************************************************
	bool StringId::operator!=(const StringId& other)
	{
		return (m_uId != other.m_uId);
	}

	//**********************************************************************************************************************
	bool StringId::IsValid() const
	{
		return m_uId != 0;
	}

	//**********************************************************************************************************************
	unsigned long StringId::GetId() const
	{
		return m_uId;
	}

	//**********************************************************************************************************************
	const char* StringId::GetContent() const
	{
		return m_strContent.c_str();
	}

} //namespace Shared
