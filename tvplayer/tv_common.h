#ifndef __SKYTV_COMMON_H__
#define __SKYTV_COMMON_H__

#include "tv_types.h"
#include "TvPlayer.h"

class skyTvMw
{
public:
	static skyTvMw* getInstance(void);
	static void destoryInstance(void);

	bool setInputSoruce(SKYTV_INPUT_SOURCE_TYPE input);
	SKYTV_INPUT_SOURCE_TYPE getInputSource(void);
	bool isDtvSource(void);
	bool isAtvSource(void);
	bool isTvSource(void);
	TvPlayer* getPlayer(void);
	bool destoryPlayer(void);
	bool setCountry(SKYTV_COUNTRY_E country);
	bool setTimeZone(SKYTV_TIMEZONE_E tz);
};

#endif //__SKYTV_COMMON_H__
