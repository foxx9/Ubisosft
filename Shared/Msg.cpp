//**********************************************************************************************************************
#include "Msg.h"

namespace Shared
{

	Msg::Msg() 
	{
		m_buffer_capacity = CAPACITY;
		m_buffer_size = 0 ; 
	}


	char* Msg::GetBuffer() const
	{
		return (char *) m_static_buffer;
	}

	size_t Msg::GetBufferSize() const
	{
		return m_buffer_size;
	}

	void Msg::SetBufferSize(size_t size)
	{
		m_buffer_size = size;
	}

} //namespace Shared
