//**********************************************************************************************************************
#include "Msg.h"

namespace Shared
{

	Msg::Msg() : Serializer(50)
	{
		
	}


	char* Msg::GetBuffer() const
	{
		return (char *) _buffer;
	}

	size_t Msg::GetBufferSize() const
	{
		return _cursor;
	}

} //namespace Shared
