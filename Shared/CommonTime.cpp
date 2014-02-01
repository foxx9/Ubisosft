#include <Windows.h>

#include "CommonTime.h"

namespace Shared
{

	//**********************************************************************************************************************
	time_t Time::GetEpochUtcSecs()
	{
		return time(NULL);
	}

	//**********************************************************************************************************************
	unsigned long Time::GetTimeMs()
	{
		return ::GetTickCount();
	}

	//**********************************************************************************************************************
	unsigned long Time::GetTimeSecs()
	{
		return (::GetTickCount()/1000);
	}


} //namespace Shared
