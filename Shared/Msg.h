//**********************************************************************************************************************
#pragma once
#include "Serializer.h"
namespace Shared
{
	//**********************************************************************************************************************
	class Msg
	{
	public:

		static const size_t CAPACITY = 1300;

		Msg();

		char* GetBuffer() const;
		size_t GetBufferSize() const;
		void SetBufferSize(size_t size);

	protected:
		
		char	m_static_buffer[CAPACITY];
		size_t	m_buffer_size;
		size_t	m_buffer_capacity;
		
	};

} //namespace Shared
