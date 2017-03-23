#include "CTime.h"
#include <stdio.h>
#include "CSystemService.h"

const static unsigned char  SleepTimeCoef[11] = {0, 1, 2, 3, 6, 9, 12, 18, 24, 36, 48};
const static unsigned char  SolarCal[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const static unsigned short SolarDays[28] = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365, 396, 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366, 397};

#define SECONDS_PER_HALF_MIN    30L
/// Seconds per minute
#define SECONDS_PER_MIN         60L
/// Second per quarter
#define SECONDS_PER_QUARTER     900L
/// Seconds per half hour
#define SECONDS_PER_HALF_HOUR   1800L
/// Seconds per hour
#define SECONDS_PER_HOUR        3600L
/// Seconds per day
#define SECONDS_PER_DAY         86400L
/// Second per week
#define SECONDS_PER_WEEK        604800L
/// Minutes per hour
#define MINS_PER_HOUR           60
/// Hours per day
#define HOURS_PER_DAY           24
/// Days per week
#define DAYS_PER_WEEK           7
/// Milliseconds per minute
#define MINUTE_TO_MS            60000
/// Milliseconds per second
#define SECOND_TO_MS            1000
/// Microseconds per second
#define SECOND_TO_US            1000000
/// Nanoseconds per second
#define SECOND_TO_NS            1000000000
/// UTC base year
#define UTC_BASE_YEAR 1970
/// GPS base year
#define GPS_BASE_YEAR 1980
/// GPS base day
#define GPS_BASE_DAY 6
/// Default ST_time setting
#define DEFAULT_BASE_YEAR                       1970
/// the default month
#define DEFAULT_MONTH                           1
/// the default day
#define DEFAULT_DAY                             1
/// the default hour
#define DEFAULT_HOUR                            0
/// the default minute
#define DEFAULT_MIN                             0
/// the default second
#define DEFAULT_SEC                             0

unsigned short CTime::getDaysOfYear(unsigned short u16year) {
	return (getLeap(u16year) != 0) ? 366 : 365;
}

unsigned char CTime::getLeap(unsigned short u16year) {
	if ((u16year % 400) == 0)
	{
		return 1;
	}
	else if ((u16year % 100) == 0)
	{
		return 0;
	}
	else if ((u16year % 4) == 0)
	{
		return 1;
	}

	return 0;
}

unsigned char CTime::getDaysOfMonth(unsigned short u16Year, unsigned char u8Month) {
	if ((u8Month >= 1) && (u8Month <= 12))
	{
		return ((getLeap(u16Year) && (u8Month == 2)) ? 29 : SolarCal[u8Month - 1]);
	} else {
		return 0;
	}
}

unsigned char CTime::getDayOfWeek(unsigned short u16Year, unsigned char u8Month, unsigned char u8Day) {
	unsigned char i = 0;
	unsigned short u16days = 0;
	unsigned int u32sum = 0;

	for (i = 1; i <= (u8Month - 1); i++)
	{
		u16days += SolarCal[i - 1];
	}

	if (getLeap(u16Year) && (u8Month > 2))
		u16days += 1;

	u16days += u8Day;

	u32sum = u16Year - 1 + ((u16Year - 1) / 4) - ((u16Year - 1) / 100) + ((u16Year - 1) / 400) + u16days;

	return (unsigned char)(u32sum % 7);
}


bool CTime::seconds2Time(unsigned int u32Seconds, SkyTvTime& time) {
	unsigned short u16TotalDays = 0, u16Days = 0;

	time.u16Year = 1970;
	time.u8Month = 1;
	time.u8Day = 1;
	time.u8Hour = 0;
	time.u8Minute = 0;
	time.u8Second = 0;

	if (u32Seconds > 0) {
		/* sec */
		time.u8Second = u32Seconds % SECONDS_PER_MIN;
		u32Seconds -= time.u8Second;

		/* min */
		time.u8Minute = (u32Seconds / SECONDS_PER_MIN) % MINS_PER_HOUR;
		u32Seconds -= time.u8Minute * SECONDS_PER_MIN;

		/* hour */
		time.u8Hour = (u32Seconds / SECONDS_PER_HOUR) % HOURS_PER_DAY;
		u32Seconds -= time.u8Hour * SECONDS_PER_HOUR;

		/* days */
		u16TotalDays = u32Seconds / SECONDS_PER_DAY;

		/* year */
		u16Days = getDaysOfYear(time.u16Year);
		while (u16TotalDays >= u16Days)
		{
			u16TotalDays -= u16Days;
			time.u16Year++;
			u16Days = getDaysOfYear(time.u16Year);
		}
		/* month */
		u16Days = getDaysOfMonth(time.u16Year, time.u8Month);
		while (u16TotalDays >= u16Days)
		{
			u16TotalDays -= u16Days;
			time.u8Month++;
			u16Days = getDaysOfMonth(time.u16Year, time.u8Month);
		}

		/* day */
		time.u8Day += (unsigned char) u16TotalDays;
	}
	return true;
}

bool CTime::seconds2TimeString(unsigned int u32Seconds, SkyTvTimeString& timeString) {
	SkyTvTime tmpTime;
	if (seconds2Time(u32Seconds, tmpTime)) {
		// printf("[%s] y:%d,m:%d,d:%d,h:%d,m:%d,s:%d\n", __FUNCTION__, tmpTime.u16Year, tmpTime.u8Month, tmpTime.u8Day, tmpTime.u8Hour, tmpTime.u8Minute, tmpTime.u8Second);

		char tmpChars[8] = {0};
		sprintf(tmpChars, "%04d", tmpTime.u16Year);
		timeString.strYear = tmpChars;
		sprintf(tmpChars, "%02d", tmpTime.u8Month);
		timeString.strMonth = tmpChars;
		sprintf(tmpChars, "%02d", tmpTime.u8Day);
		timeString.strDay = tmpChars;
		sprintf(tmpChars, "%02d", tmpTime.u8Hour);
		timeString.strHour = tmpChars;
		sprintf(tmpChars, "%02d", tmpTime.u8Minute);
		timeString.strMinute = tmpChars;
		sprintf(tmpChars, "%02d", tmpTime.u8Second);
		timeString.strSecond = tmpChars;
		timeString.strWeek = "";

		// printf("[%s]ssss y:%s,m:%s,d:%s,h:%s,m:%s,s:%s\n", __FUNCTION__, timeString.strYear.c_str(), timeString.strMonth.c_str(), timeString.strDay.c_str(), timeString.strHour.c_str(), timeString.strMinute.c_str(), timeString.strSecond.c_str());
		return true;
	}
	return false;
}

bool CTime::seconds2TimeString(unsigned int u32Seconds, std::string& timeString) {
	SkyTvTime tmpTime;
	std::string tmpString = "";
	if (seconds2Time(u32Seconds, tmpTime)) {
		char tmpChars[8] = {0};
		sprintf(tmpChars, "%04d", tmpTime.u16Year);
		timeString += tmpChars;
		timeString += "/";
		sprintf(tmpChars, "%02d", tmpTime.u8Month);
		timeString += tmpChars;
		timeString += "/";
		sprintf(tmpChars, "%02d", tmpTime.u8Day);
		timeString += tmpChars;
		timeString += " ";
		sprintf(tmpChars, "%02d", tmpTime.u8Hour);
		timeString += tmpChars;
		timeString += ":";
		sprintf(tmpChars, "%02d", tmpTime.u8Minute);
		timeString += tmpChars;
		timeString += ":";
		sprintf(tmpChars, "%02d", tmpTime.u8Second);
		timeString += tmpChars;
		return true;
	}
	return false;
}

bool CTime::getLocalTime(SkyTvTime& time) {
	struct tm tmpTime = {0};
	CSystemService::getLocalTime(tmpTime);
	time.u16Year = tmpTime.tm_year + 1990;
	time.u8Month = tmpTime.tm_mon + 1;
	time.u8Day = tmpTime.tm_mday;
	time.u8Hour = tmpTime.tm_hour;
	time.u8Minute = tmpTime.tm_min;
	time.u8Second = tmpTime.tm_sec;
	time.u8Week = tmpTime.tm_wday;
	return true;
}

bool CTime::getLocalTime(SkyTvTimeString& timeString) {
	struct tm tmpTime = {0};
	CSystemService::getLocalTime(tmpTime);

	char tmpChars[8] = {0};
	sprintf(tmpChars, "%04d", tmpTime.tm_year + 1990);
	timeString.strYear = tmpChars;
	sprintf(tmpChars, "%02d", tmpTime.tm_mon + 1);
	timeString.strMonth = tmpChars;
	sprintf(tmpChars, "%02d", tmpTime.tm_mday);
	timeString.strDay = tmpChars;
	sprintf(tmpChars, "%02d", tmpTime.tm_hour);
	timeString.strHour = tmpChars;
	sprintf(tmpChars, "%02d", tmpTime.tm_min);
	timeString.strMinute = tmpChars;
	sprintf(tmpChars, "%02d", tmpTime.tm_sec);
	timeString.strSecond = tmpChars;
	switch (tmpTime.tm_wday) {
	case 0:
		timeString.strWeek = "Sunday";
		break;
	case 1:
		timeString.strWeek = "Monday";
		break;
	case 2:
		timeString.strWeek = "Tuesday";
		break;
	case 3:
		timeString.strWeek = "Wednesday";
		break;
	case 4:
		timeString.strWeek = "Thursday";
		break;
	case 5:
		timeString.strWeek = "Friday";
		break;
	case 6:
		timeString.strWeek = "Saturday";
		break;
	default:
		break;
	}
	return true;
}

unsigned long CTime::getClock(void) {
	return CSystemService::getClock();
}
