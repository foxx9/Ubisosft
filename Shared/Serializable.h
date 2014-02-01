//**********************************************************************************************************************
#pragma once

#include "Serializer.h"

namespace Shared
{
	//**********************************************************************************************************************
	class  Serializable
	{
	public:

		virtual bool Serialize(Serializer& serializer) = 0;
		virtual bool Unserialize(Serializer& serializer) = 0;

	protected:

	};

} //namespace Shared
