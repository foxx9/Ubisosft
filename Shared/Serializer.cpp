//**********************************************************************************************************************
#include "Serializer.h"

namespace Shared
{
		/*
		// Pre-allocate a dynamic buffer
		Serializer::Serializer(size_t buffer_size_in)
		{

		}

		// Passing pbuffer_in  will cause a dynamic allocation strategy
		Serializer::Serializer(const char* pbuffer_in = 0, size_t buffer_size_in = 0)
		{

		}
		*/
		bool Serializer::isBigIndian()
		{
			short int number = 0x1;
			char *numPtr = (char*)&number;
			return (numPtr[0] == 1);
		}

} // namespace Shared
