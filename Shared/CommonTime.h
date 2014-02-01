//**********************************************************************************************************************
#pragma once
//**********************************************************************************************************************

#include <ctime>
#include <time.h>

namespace Shared
{

//**********************************************************************************************************************
class Time
{
public:

	//Return the time as seconds elapsed since midnight, January 1, 1970
	static time_t GetEpochUtcSecs();

	//Retrieves the number of milliseconds that have elapsed since the system was started, up to 49.7 days.
	static unsigned long GetTimeMs();
	static unsigned long GetTimeSecs();

protected:

};

} //namespace Shared
