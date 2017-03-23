#ifndef __CSYSTEMSERVICE_H__
#define __CSYSTEMSERVICE_H__

#include "tv_common.h"

class CSystemService
{
public:
	CSystemService();
	~CSystemService();

	static SKYTV_INPUT_SOURCE_TYPE getCurInputSoruce(void);
	static bool setInputSoruce(SKYTV_INPUT_SOURCE_TYPE input);
	static unsigned long getClock(void);
	static bool getLocalTime(struct tm& time);
	static bool setCountry(SKYTV_COUNTRY_E country);
	static bool setTimeZone(SKYTV_TIMEZONE_E tz);
};


#endif // __CSYSTEMSERVICE_H__
