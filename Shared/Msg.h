//**********************************************************************************************************************
#pragma once
#include "Serializer.h"
namespace Shared
{
	//**********************************************************************************************************************
	class Msg : public Serializer
	{
	public:

		Msg();

		char* GetBuffer() const;
		size_t GetBufferSize() const;

	protected:
		/*
		char	m_static_buffer[1300];
		size_t	m_buffer_size;
		size_t	m_buffer_capacity;
		*/
	};

} //namespace Shared
