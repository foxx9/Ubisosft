//**********************************************************************************************************************
#include "Serializer.h"

namespace Shared
{
		bool Serializer::isBigIndian()
		{
			short int number = 0x1;
			char *numPtr = (char*)&number;
			return (numPtr[0] == 1);
		}

} // namespace Shared
